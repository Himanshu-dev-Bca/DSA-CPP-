#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Patient {
public:
    int id;
    string name;
    int age;
    string disease;

    Patient(int i, string n, int a, string d) {
        id = i;
        name = n;
        age = a;
        disease = d;
    }

    void display() {
        cout << "ID: " << id << ", Name: " << name
             << ", Age: " << age << ", Disease: " << disease << endl;
    }
};

Patient* linearSearch(vector<Patient>& patients, int targetID) {
    for (auto &p : patients) {
        if (p.id == targetID) {
            return &p;
        }
    }
    return nullptr;
}

Patient* binarySearch(vector<Patient>& patients, int targetID) {
    int left = 0, right = patients.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (patients[mid].id == targetID)
            return &patients[mid];
        else if (patients[mid].id < targetID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return nullptr;
}

bool compareByID(Patient a, Patient b) {
    return a.id < b.id;
}

int main() {
    vector<Patient> patients = {
        Patient(103, "Amit", 30, "Fever"),
        Patient(101, "Riya", 25, "Cold"),
        Patient(105, "John", 40, "Diabetes"),
        Patient(102, "Neha", 35, "Flu")
    };

    int choice, targetID;

    cout << "Enter Patient ID to search: ";
    cin >> targetID;

    cout << "\n1. Linear Search\n2. Binary Search\nChoose: ";
    cin >> choice;

    Patient* result = nullptr;

    if (choice == 1) {
        result = linearSearch(patients, targetID);
    }
    else if (choice == 2) {
        sort(patients.begin(), patients.end(), compareByID); 
        result = binarySearch(patients, targetID);
    }
    else {
        cout << "Invalid choice\n";
        return 0;
    }

    if (result != nullptr) {
        cout << "\nPatient Found:\n";
        result->display();
    } else {
        cout << "\nPatient Not Found\n";
    }

    return 0;
}
