#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* root = NULL;

int height(Node* temp) {
    int h = 0;
    if (temp != NULL) {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int diff(Node* temp) {
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    return l_height - r_height;
}

Node* ll(Node* parent) {
    Node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

Node* rr(Node* parent) {
    Node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

Node* lr(Node* parent) {
    Node* temp = parent->left;
    parent->left = rr(temp);
    return ll(parent);
}

Node* rl(Node* parent) {
    Node* temp = parent->right;
    parent->right = ll(temp);
    return rr(parent);
}

Node* balance(Node* temp) {
    int bal_factor = diff(temp);
    if (bal_factor > 1) {
        if (diff(temp->left) > 0)
            temp = ll(temp);
        else
            temp = lr(temp);
    } else if (bal_factor < -1) {
        if (diff(temp->right) > 0)
            temp = rl(temp);
        else
            temp = rr(temp);
    }
    return temp;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        root = new Node;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    } else if (value < root->value) {
        root->left = insert(root->left, value);
        root = balance(root);
    } else if (value >= root->value) {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}

void display(Node* ptr) {
    if (ptr != NULL) {
        display(ptr->left);
        cout << ptr->value << " ";
        display(ptr->right);
    }
}

int main() {
    char ch;
    cout << "AVL Tree Insertion\n";
    do {
        int value;
        cout << "Enter the value: ";
        cin >> value;
        root = insert(root, value);
        cout << "Enter your choice (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    cout << "\nDisplay AVL Tree:\n";
    display(root);
    cout << endl;

    return 0;
}
