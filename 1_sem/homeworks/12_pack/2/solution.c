#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    int count;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    } else {

    }
    {
        root->count++;
    }

    return root;
}

void inOrderTraversal(Node* root, int* sortedArray, int* index)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left, sortedArray, index);

        for (int i = 0; i < root->count; i++)
        {
            sortedArray[(*index)++] = root->data;
        }

        inOrderTraversal(root->right, sortedArray, index);
    }
}

void freeTree(Node* root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void shuffleArray(int* array, int size)
{
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main()
{
    FILE* fin = fopen("input.bin", "rb");
    FILE* fout = fopen("output.bin", "wb");

    int N;
    fread(&N, sizeof(int), 1, fin);

    int* originalArray = (int*)malloc(N * sizeof(int));
    fread(originalArray, sizeof(int), N, fin);

    shuffleArray(originalArray, N);

    Node* root = NULL;

    for (int i = 0; i < N; i++)
    {
        root = insert(root, originalArray[i]);
    }

    int* sortedArray = (int*)malloc(N * sizeof(int));
    int index = 0;

    inOrderTraversal(root, sortedArray, &index);

    fwrite(sortedArray, sizeof(int), N, fout);

    free(originalArray);
    free(sortedArray);
    freeTree(root);

    fclose(fin);
    fclose(fout);

    return 0;
}
