#include <iostream>
using namespace std;

struct Patient {
    int id;
    string name;
    float bill;
};

Patient p[100];
int n = 0;

void display() {
    if (n == 0) {
        cout << "\nNo patient records available.\n";
        return;
    }

    cout << "\nPatient Records:\n";
    for (int i = 0; i < n; i++) {
        cout << "ID: " << p[i].id
             << ", Name: " << p[i].name
             << ", Bill: " << p[i].bill << endl;
    }
}

void addPatients() {
    cout << "\nEnter number of patients to add: ";
    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cout << "\nEnter details for patient " << n + 1 << endl;
        cout << "ID: ";
        cin >> p[n].id;
        cout << "Name: ";
        cin >> p[n].name;
        cout << "Bill Amount: ";
        cin >> p[n].bill;
        n++;
    }
}

void selectionSort() {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (p[j].bill < p[minIndex].bill) {
                minIndex = j;
            }
        }

        Patient temp = p[i];
        p[i] = p[minIndex];
        p[minIndex] = temp;
    }

    cout << "\nData sorted using Selection Sort.\n";
}

int partition(int low, int high) {
    float pivot = p[high].bill;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (p[j].bill < pivot) {
            i++;
            Patient temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
    }

    Patient temp = p[i + 1];
    p[i + 1] = p[high];
    p[high] = temp;

    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}


int main() {
    int choice;

    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Patients\n";
        cout << "2. Display Patients\n";
        cout << "3. Sort using Selection Sort (by Bill)\n";
        cout << "4. Sort using Quick Sort (by Bill)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatients();
                break;

            case 2:
                display();
                break;

            case 3:
                selectionSort();
                display();
                break;

            case 4:
                quickSort(0, n - 1);
                cout << "\nData sorted using Quick Sort.\n";
                display();
                break;

            case 5:
                cout << "\nExiting program...\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
