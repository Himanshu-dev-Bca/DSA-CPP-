#include <iostream>
#include <vector>
using namespace std;

// Patient structure
struct Patient {
    int id;
    string name;
    int priority;
};

// Utility function to print patients
void printPatients(vector<Patient>& patients) {
    for (auto &p : patients) {
        cout << "ID: " << p.id 
             << ", Name: " << p.name 
             << ", Priority: " << p.priority << endl;
    }
    cout << "--------------------------\n";
}

// ?? Selection Sort (Simple but slow)
void selectionSort(vector<Patient>& patients) {
    int n = patients.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (patients[j].priority < patients[minIndex].priority) {
                minIndex = j;
            }
        }
        
        // Swap
        swap(patients[i], patients[minIndex]);
    }
}

// ?? Quick Sort helpers
int partition(vector<Patient>& patients, int low, int high) {
    int pivot = patients[high].priority;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (patients[j].priority < pivot) {
            i++;
            swap(patients[i], patients[j]);
        }
    }
    
    swap(patients[i + 1], patients[high]);
    return i + 1;
}

// ?? Quick Sort (Fast)
void quickSort(vector<Patient>& patients, int low, int high) {
    if (low < high) {
        int pi = partition(patients, low, high);

        quickSort(patients, low, pi - 1);
        quickSort(patients, pi + 1, high);
    }
}

// ?? Main function
int main() {
    vector<Patient> patients = {
        {101, "Rahul", 4},
        {102, "Anita", 1},
        {103, "Karan", 3},
        {104, "Priya", 2}
    };

    cout << "Original Patient List:\n";
    printPatients(patients);

    // ?? Selection Sort
    vector<Patient> selectionSorted = patients;
    selectionSort(selectionSorted);
    
    cout << "After Selection Sort (by priority):\n";
    printPatients(selectionSorted);

    // ?? Quick Sort
    vector<Patient> quickSorted = patients;
    quickSort(quickSorted, 0, quickSorted.size() - 1);

    cout << "After Quick Sort (by priority):\n";
    printPatients(quickSorted);

    return 0;
}

