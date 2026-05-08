#include <iostream>
using namespace std;

struct Node {
    int id;
    string name;
    int priority;
    Node* left;
    Node* right;

    Node(int i, string n, int p) {
        id = i;
        name = n;
        priority = p;
        left = right = NULL;
    }
};

Node* insert(Node* root, int id, string name, int priority) {
    if (root == NULL)
        return new Node(id, name, priority);

    if (priority < root->priority)
        root->left = insert(root->left, id, name, priority);
    else
        root->right = insert(root->right, id, name, priority);

    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int priority) {
    if (root == NULL)
        return root;

    if (priority < root->priority)
        root->left = deleteNode(root->left, priority);
    else if (priority > root->priority)
        root->right = deleteNode(root->right, priority);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->priority = temp->priority;
        root->id = temp->id;
        root->name = temp->name;
        root->right = deleteNode(root->right, temp->priority);
    }
    return root;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->id << " " << root->name << " " << root->priority << endl;
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->id << " " << root->name << " " << root->priority << endl;
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->id << " " << root->name << " " << root->priority << endl;
}

void display(Node* root) {
    if (root == NULL) return;
    display(root->left);
    cout << "[" << root->name << " | Priority: " << root->priority << "] ";
    display(root->right);
}

int main() {
    Node* root = NULL;

    root = insert(root, 101, "Rahul", 4);
    root = insert(root, 102, "Anita", 1);
    root = insert(root, 103, "Karan", 3);
    root = insert(root, 104, "Priya", 2);

    cout << "Inorder:\n";
    inorder(root);

    cout << "\nPreorder:\n";
    preorder(root);

    cout << "\nPostorder:\n";
    postorder(root);

    root = deleteNode(root, 3);

    cout << "\nAfter Deletion:\n";
    display(root);

    return 0;
}
