#include <iostream>
using namespace std;

#define MAX 100

class Queue {
private:
    int arr[MAX];
    int front, rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }
void enqueue(int value) {
        if (rear == MAX - 1) {
            cout << "Queue Overflow\n";
            return;
        }
        if (front == -1) front = 0;

        rear++;
        arr[rear] = value;
        cout << value << " inserted into queue\n";
    }
    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow\n";
            return;
        }

        cout << arr[front] << " removed from queue\n";
        front++;
        if (front > rear) {
            front = rear = -1;
        }
    }
    void display() {
        if (front == -1) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void search(int key) {
        if (front == -1) {
            cout << "Queue is empty\n";
            return;
        }

        for (int i = front; i <= rear; i++) {
            if (arr[i] == key) {
                cout << "Element found at position " << (i - front + 1) << endl;
                return;
            }
        }
        cout << "Element not found\n";
    }
};
int main() {
    Queue q;
    int choice, value;

    do {
        cout << "\n--- Queue Menu ---\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Search\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                q.enqueue(value);
                break;

            case 2:
                q.dequeue();
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                q.search(value);
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}
