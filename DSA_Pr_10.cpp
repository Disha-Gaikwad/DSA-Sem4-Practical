/*A Dictionary stores keywords &amp; its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. 
Provide facility to display whole data sorted in ascending/ Descending order. 
Also find how many maximum comparisons may require for finding any keyword. 
Use Height Balance Tree and fins complexity for finding keyword.*/
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for AVL tree node
struct Node {
    char keyword[100];
    char meaning[500];
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get height of the node
int getHeight(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return n->height;
}

// Function to find maximum of two values
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node *createNode(char *keyword, char *meaning) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(node->keyword, keyword);
    strcpy(node->meaning, meaning);
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Initially, height is 1
    return node;
}

// Function to get the balance factor of a node
int getBalanceFactor(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}
// Right rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}
// Left rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert function
struct Node* insert(struct Node* node, char *keyword, char *meaning) {
    if (node == NULL) {
        return createNode(keyword, meaning);
    }

    if (strcmp(keyword, node->keyword) < 0) {
        node->left = insert(node->left, keyword, meaning);
    } else if (strcmp(keyword, node->keyword) > 0) {
        node->right = insert(node->right, keyword, meaning);
    } else {
        // Keyword already exists, so update the meaning
        strcpy(node->meaning, meaning);
        return node;
    }

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalanceFactor(node);

    // Left Left case
    if (balance > 1 && strcmp(keyword, node->left->keyword) < 0) {
        return rightRotate(node);
    }
    // Right Right case
    if (balance < -1 && strcmp(keyword, node->right->keyword) > 0) {
        return leftRotate(node);
    }
    // Left Right case
    if (balance > 1 && strcmp(keyword, node->left->keyword) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left case
    if (balance < -1 && strcmp(keyword, node->right->keyword) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find a keyword in the tree
struct Node* find(struct Node *root, char *keyword) {
    if (root == NULL || strcmp(root->keyword, keyword) == 0) {
        return root;
    }

    if (strcmp(keyword, root->keyword) < 0) {
        return find(root->left, keyword);
    }

    return find(root->right, keyword);
}

// In-order traversal (ascending order)
void inOrder(struct Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Keyword: %s, Meaning: %s\n", root->keyword, root->meaning);
        inOrder(root->right);
    }
}

// Reverse in-order traversal (descending order)
void reverseInOrder(struct Node *root) {
    if (root != NULL) {
        reverseInOrder(root->right);
        printf("Keyword: %s, Meaning: %s\n", root->keyword, root->meaning);
        reverseInOrder(root->left);
    }
}

// Delete a keyword
struct Node* delete(struct Node* root, char *keyword) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(keyword, root->keyword) < 0) {
        root->left = delete(root->left, keyword);
    } else if (strcmp(keyword, root->keyword) > 0) {
        root->right = delete(root->right, keyword);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node has two children, get the inorder successor (smallest in the right subtree)
        struct Node *temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        strcpy(root->keyword, temp->keyword);
        strcpy(root->meaning, temp->meaning);

        // Delete the inorder successor
        root->right = delete(root->right, temp->keyword);
    }

    // Update height of current node
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Balance the node if needed
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Main function
int main() {
    struct Node *root = NULL;

    // Example usage
    root = insert(root, "apple", "A fruit");
    root = insert(root, "banana", "A yellow fruit");
    root = insert(root, "carrot", "A vegetable");
    root = insert(root, "dog", "A pet animal");

    // Display sorted dictionary in ascending order
    printf("Dictionary in Ascending Order:\n");
    inOrder(root);

    // Search for a keyword
    char keyword[] = "banana";
    struct Node *result = find(root, keyword);
    if (result != NULL) {
        printf("\nFound keyword '%s': %s\n", result->keyword, result->meaning);
    } else {
        printf("\nKeyword '%s' not found.\n", keyword);
    }
    // Update meaning of an existing keyword
    printf("\nUpdating meaning of 'banana'.\n");
    root = insert(root, "banana", "A tropical yellow fruit");
    result = find(root, "banana");
    if (result != NULL) {
        printf("Updated keyword '%s': %s\n", result->keyword, result->meaning);
    }
    // Delete a keyword
    printf("\nDeleting keyword 'dog'.\n");
    root = delete(root, "dog");
    printf("Dictionary in Descending Order:\n");
    reverseInOrder(root);

    return 0;
}

