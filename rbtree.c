#include <stdio.h>
#include <stdlib.h>

// Define structure for RB tree node
struct Node {
    char data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int color; // 0 for red, 1 for black
};

// Create a new RB tree node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 0; // Red by default
    return newNode;
}

// Left Rotation
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right Rotation
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Fix the RB tree after insertion
void fixInsert(struct Node** root, struct Node* z) {
    while (z != *root && z->parent->color == 0) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            if (y != NULL && y->color == 0) {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left;
            if (y != NULL && y->color == 0) {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 1;
}

// Insert a key into the RB tree
void insert(struct Node** root, char key) {
    struct Node* newNode = createNode(key);
    struct Node* y = NULL;
    struct Node* x = *root;

    while (x != NULL) {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == NULL)
        *root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    if (newNode->parent == NULL) {
        newNode->color = 1; // Red-Black tree property: Root is always black
        return;
    }

    if (newNode->parent->parent == NULL)
        return;

    fixInsert(root, newNode);
}

// Helper function to fix the Red-Black Tree after node deletion
void fixDelete(struct Node** root, struct Node* x) {
    while (x != *root && x->color == 1) {
        if (x == x->parent->left) {
            struct Node* w = x->parent->right;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 1 && w->right->color == 1) {
                w->color = 0;
                x = x->parent;
            } else {
                if (w->right->color == 1) {
                    w->left->color = 1;
                    w->color = 0;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->right->color = 1;
                leftRotate(root, x->parent);
                x = *root; // Exit the loop
            }
        } else {
            struct Node* w = x->parent->left;
            if (w->color == 0) {
                w->color = 1;
                x->parent->color = 0;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 1 && w->left->color == 1) {
                w->color = 0;
                x = x->parent;
            } else {
                if (w->left->color == 1) {
                    w->right->color = 1;
                    w->color = 0;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 1;
                w->left->color = 1;
                rightRotate(root, x->parent);
                x = *root; // Exit the loop
            }
        }
    }
    x->color = 1;
}

// Find the minimum node in the tree rooted at a given node
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Helper function to replace one subtree as a child of its parent with another subtree
void transplant(struct Node** root, struct Node* u, struct Node* v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

// Delete a node with a given key from the RB tree
void deleteNode(struct Node** root, char key) {
    // Find the node with the given key to delete
    struct Node* z = *root;
    while (z != NULL) {
        if (key < z->data)
            z = z->left;
        else if (key > z->data)
            z = z->right;
        else
            break;
    }

    if (z == NULL)
        return; // Node with the given key not found

    struct Node* y = z;
    int yOriginalColor = y->color;
    struct Node* x;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == 1)
        fixDelete(root, x);

    free(z);
}


// Inorder traversal of the RB tree
void inorder(struct Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;
    char keys[] = "FSQKCLHTVWMRNPABXYDZE";

    for (int i = 0; i < 21; i++) {
        insert(&root, keys[i]);
    }

    printf("Inorder Traversal of the RB Tree: ");
    inorder(root);
    printf("\n");

    char keyToDelete = 'X';
    deleteNode(&root, keyToDelete);

    // Inorder Traversal after deletion
    printf("Inorder Traversal of the RB Tree after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}

