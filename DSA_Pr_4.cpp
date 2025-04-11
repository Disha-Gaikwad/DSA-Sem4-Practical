#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
};

Node* createNode(string key, string value) {
    Node* newNode = new Node();
    newNode->keyword = key;
    newNode->meaning = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, string key, string value) {
    if (root == NULL)
        return createNode(key, value);
    if (key < root->keyword)
        root->left = insert(root->left, key, value);
    else if (key > root->keyword)
        root->right = insert(root->right, key, value);
    else
        cout << "Keyword already exists. Try updating the value.\n";
    return root;
}

Node* search(Node* root, string key, int& comparisons) {
    while (root != NULL) {
        comparisons++;
        if (key == root->keyword)
            return root;
        else if (key < root->keyword)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, string key) {
    if (root == NULL)
        return root;
    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }
    return root;
}

void update(Node* root, string key, string newMeaning) {
    int comparisons = 0;
    Node* node = search(root, key, comparisons);
    if (node != NULL)
        node->meaning = newMeaning;
    else
        cout << "Keyword not found.\n";
}

void displayAscending(Node* root) {
    if (root != NULL) {
        displayAscending(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node* root) {
    if (root != NULL) {
        displayDescending(root->right);
        cout << root->keyword << ": " << root->meaning << endl;
        displayDescending(root->left);
    }
}

int height(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    Node* root = NULL;
    int choice, comparisons;
    string key, value;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Add keyword\n2. Delete keyword\n3. Update keyword\n4. Display Ascending\n";
        cout << "5. Display Descending\n6. Search keyword\n7. Max comparisons required\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, value);
            root = insert(root, key, value);
            break;

        case 2:
            cout << "Enter keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            break;

        case 3:
            cout << "Enter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, value);
            update(root, key, value);
            break;

        case 4:
            cout << "Dictionary in Ascending order:\n";
            displayAscending(root);
            break;

        case 5:
            cout << "Dictionary in Descending order:\n";
            displayDescending(root);
            break;

        case 6:
            comparisons = 0;
            cout << "Enter keyword to search: ";
            cin >> key;
            if (search(root, key, comparisons))
                cout << "Keyword found with " << comparisons << " comparisons.\n";
            else
                cout << "Keyword not found after " << comparisons << " comparisons.\n";
            break;

        case 7:
            cout << "Maximum comparisons required: " << height(root) << endl;
            break;

        case 8:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}

