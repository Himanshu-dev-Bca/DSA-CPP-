#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};


class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = NULL;
    }

    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Inserted: " << value << endl;
    }

    void deleteElement(int key) {
        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }

        if (head->data == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted: " << key << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != NULL && temp->next->data != key) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            cout << "Element not found\n";
        } else {
            Node* delNode = temp->next;
            temp->next = delNode->next;
            delete delNode;
            cout << "Deleted: " << key << endl;
        }
    }

    void search(int key) {
        Node* temp = head;
        int position = 1;

        while (temp != NULL) {
            if (temp->data == key) {
                cout << "Element found at position " << position << endl;
                return;
            }
            temp = temp->next;
            position++;
        }
        cout << "Element not found\n";
    }

    void countNodes() {
        Node* temp = head;
        int count = 0;

        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        cout << "Total nodes: " << count << endl;
    }

    void display() {
        Node* temp = head;

        if (temp == NULL) {
            cout << "List is empty\n";
            return;
        }

        cout << "List: ";
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main() {
    LinkedList list;
    int choice, value;

    do {
        cout << "\n--- Linked List Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Count Nodes\n5. Display\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                list.insert(value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteElement(value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                list.search(value);
                break;

            case 4:
                list.countNodes();
                break;

            case 5:
                list.display();
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 6);

    return 0;
}
