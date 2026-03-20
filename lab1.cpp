#include <iostream>
#include <string>

using namespace std;

struct Patient {
    int id;
    string name;
    string ailment;
};

struct Node {
    Patient data;
    Node* next;
};

class HospitalStack {
private:
    Node* top;

public:
    HospitalStack() { top = NULL; }
    void push() {
        Node* newNode = new Node();
        cout << "\nEnter Patient ID: ";
        cin >> newNode->data.id;
        cin.ignore();
                cout << "Enter Patient Name: ";
        getline(cin, newNode->data.name);
        cout << "Enter Ailment: ";
        getline(cin, newNode->data.ailment);

        newNode->next = top;
        top = newNode;
        cout << "\nPatient record added successfully!" << endl;
    }
void pop() {
        if (top == NULL) {
            cout << "\nError: No patient records found (Stack Underflow)." << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        
        cout << "\nDischarging Patient:" << endl;
        cout << "ID: " << temp->data.id << " | Name: " << temp->data.name << endl;
        
        delete temp;
    }
    void display() {
        if (top == NULL) {
            cout << "\nNo active patient records to display." << endl;
            return;
        }
        Node* temp = top;
        cout << "\n--- Current Patient Stack (Recent to Oldest) ---" << endl;
        while (temp != NULL) {
            cout << "ID: " << temp->data.id 
                 << " | Name: " << temp->data.name 
                 << " | Ailment: " << temp->data.ailment << endl;
            temp = temp->next;
        }
        cout << "-----------------------------------------------" << endl;
    }
};

int main() {
    HospitalStack hospital;
    int choice;

    do {
        cout << "\n=== Hospital Management System ===" << endl;
        cout << "1. Admit Patient (Push)" << endl;
        cout << "2. Discharge Patient (Pop)" << endl;
        cout << "3. View All Records (Display)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: hospital.push(); break;
            case 2: hospital.pop(); break;
            case 3: hospital.display(); break;
            case 4: cout << "Exiting system..." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
