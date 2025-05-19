#include <stdlib.h>
#include "integerset.h"

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

struct IntegerSet {
    Node* root;
};

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

Node* insertNode(Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    }

    return node;
}

int isInTree(Node* node, int data) {
    if (node == NULL) {
        return 0;
    }

    if (data == node->data) {
        return 1;
    } else if (data < node->data) {
        return isInTree(node->left, data);
    } else {
        return isInTree(node->right, data);
    }
}

IntegerSet* CreateSet(int* numbers, int size) {
    IntegerSet* set = (IntegerSet*)malloc(sizeof(IntegerSet));
    if (set == NULL) {
        return NULL;
    }

    set->root = NULL;

    for (int i = 0; i < size; ++i) {
        if (IsInSet(set, numbers[i])) {
            return NULL;
        }
        set->root = insertNode(set->root, numbers[i]);
    }

    return set;
}

int IsInSet(IntegerSet* set, int number) {
    if (set == NULL) {
        return 0;
    }

    return isInTree(set->root, number);
}
