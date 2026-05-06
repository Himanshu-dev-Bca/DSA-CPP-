#include <iostream>
#include <string>

using namespace std;

struct Node {
    int id;
    string name;
    string ailment;
    Node* next;
    Node* prev;

    Node(int i, string n, string a) : id(i), name(n), ailment(a), next(nullptr), prev(nullptr) {}
};

class HospitalList {
private:
    Node* head;

public:
    HospitalList() : head(nullptr) {}

    void insert(int id, string name, string ailment) {
        Node* newNode = new Node(id, name, ailment);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void remove(int id) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->id != id) {
            temp = temp->next;
        }
        if (!temp) return;
        if (temp == head) {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        delete temp;
    }

    bool search(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Patient: " << temp->name << " found." << endl;
                return true;
            }
            temp = temp->next;
        }
        cout << "Not found." << endl;
        return false;
    }

    int count() {
        int c = 0;
        Node* temp = head;
        while (temp) {
            c++;
            temp = temp->next;
        }
        return c;
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << "[" << temp->id << "|" << temp->name << "] <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    HospitalList h;
    h.insert(101, "Alice", "Flu");
    h.insert(102, "Bob", "Cold");
    h.insert(103, "Eve", "Ache");
    
    h.display();
    cout << "Total: " << h.count() << endl;
    
    h.search(102);
    h.remove(102);
    
    h.display();
    cout << "Total: " << h.count() << endl;
    
    return 0;
}
