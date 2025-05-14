/*Beginning with an empty binary search tree, Construct binary search tree by inserting the
values in the order given. After constructing a binary tree 
i. Insert new node 
ii. Find number of nodes in longest path 
iii. Minimum data value found in the tree 
iv. Change a tree so that the roles of the left and right pointers are swapped at every node 
v. Search a value*/

#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *ln, *rn;
};

class Tree {
public:
    Node* root;

    Tree() {
        root = NULL;
    }

    Node* createTree(int key) {
        root = new Node();
        root->key = key;
        root->ln = NULL;
        root->rn = NULL;
        return root;
    }

    void insertNode(int key, Node* root) {
        Node* node = new Node();
        node->key = key;
        node->ln = NULL;
        node->rn = NULL;

        if (root->key >= key) {
            if (root->ln == NULL) {
                root->ln = node;
            } else {
                insertNode(key, root->ln);
            }
        } else {
            if (root->rn == NULL) {
                root->rn = node;
            } else {
                insertNode(key, root->rn);
            }
        }
    }

    void displayInorder(Node* root) {
        if (root != NULL) {
            displayInorder(root->ln);
            cout << root->key << "\n";
            displayInorder(root->rn);
        }
    }

    void displayFirst(Node* root) {
        while (root->ln != NULL) {
            root = root->ln;
        }
        cout << "\nMinimum number is " << root->key;
    }

    void search(Node* root, int searchKey) {
        if (root == NULL) {
            cout << "\nNumber not found";
            return;
        }

        if (searchKey < root->key) {
            search(root->ln, searchKey);
        } else if (searchKey > root->key) {
            search(root->rn, searchKey);
        } else {
            cout << "\nNumber Found!";
        }
    }

    int longestPath(Node* root) {
        if (root == NULL)
            return 0;
        int Lctr = longestPath(root->ln);
        int Rctr = longestPath(root->rn);
        return max(Lctr, Rctr) + 1;
    }

    Node* swapNodes(Node* root) {
        if (root == NULL)
            return NULL;

        Node* temp = root->ln;
        root->ln = root->rn;
        root->rn = temp;

        swapNodes(root->ln);
        swapNodes(root->rn);

        return root;
    }
};

int main() {
    int choice, order, flag = 0;
    int key, searchKey;
    Tree t1;
    Node* root = NULL;

    do {
        cout << "\n1. Insert or create node \n2. Display \n3. Swap left and right nodes \n4. Search \n5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter the number: ";
            cin >> key;
            if (flag == 0) {
                root = t1.createTree(key);
                flag = 1;
            } else {
                t1.insertNode(key, root);
            }
            break;

        case 2:
            cout << "\n1. Display list \n2. Show minimum number \n3. Show number of nodes in longest path\n";
            cin >> order;
            switch (order) {
            case 1:
                t1.displayInorder(root);
                break;
            case 2:
                t1.displayFirst(root);
                break;
            case 3:
                cout << "The height of the tree or the longest path is: " << t1.longestPath(root);
                break;
            }
            break;

        case 3:
            t1.swapNodes(root);
            cout << "Swapped! The new list is:\n";
            t1.displayInorder(root);
            break;

        case 4:
            cout << "\nEnter the number you want to search: ";
            cin >> searchKey;
            t1.search(root, searchKey);
            break;

        case 5:
            break;

        default:
            cout << "Invalid choice.";
        }

    } while (choice != 5);

    return 0;
}

