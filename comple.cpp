#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <concepts>
#include <memory>
#include <chrono>

// C++20 Concept to ensure the task is callable with no arguments
template<typename F>
concept InvokableTask = std::invocable<F>;

class ThreadPool {
public:
    // Initializes the thread pool with a specific number of worker threads
    explicit ThreadPool(size_t threads = std::thread::hardware_concurrency()) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });

                        if (this->stop && this->tasks.empty()) {
                            return;
                        }

                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task(); // Execute the task
                }
            });
        }
    }

    // Enqueues an arbitrary callable task into the pool
    template<typename F, typename... Args>
    requires InvokableTask<std::decay_t<F>>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result<F, Args...>::type> 
    {
        using return_type = typename std::invoke_result<F, Args...>::type;

        // Package the task with its arguments into a shared pointer to allow copying/moving
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            // Don't allow enqueueing after stopping the pool
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }
        
        condition.notify_one();
        return res;
    }

    // Destructor joins all threads
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop{false};
};

// --- Demonstration / Benchmark ---

int multiply(int a, int b) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    return a * b;
}

int main() {
    try {
        ThreadPool pool(4); // Create a pool with 4 worker threads
        std::vector<std::future<int>> results;

        std::cout << "[Main] Enqueueing parallel multiplication tasks...\n";

        for (int i = 0; i < 8; ++i) {
            results.emplace_back(
                pool.enqueue(multiply, i, i * 2)
            );
        }

        // Enqueue a lambda with a distinct return type
        auto string_task = pool.enqueue([](const std::string& name) {
            return "Hello, " + name + " from thread " + 
                   std::to_string(hash<std::thread::id>{}(std::this_thread::get_id()) % 100);
        }, "C++ Developer");

        // Gather and print numeric results
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "Task " << i << " Result: " << results[i].get() << "\n";
        }

        // Print the string result
        std::cout << "[Main] Lambda task response: " << string_task.get() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
