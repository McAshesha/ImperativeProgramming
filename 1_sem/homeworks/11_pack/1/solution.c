#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 100000

typedef struct Node
{
    int value;
    struct Node *next;
} HashNode;

HashNode *hashTable[HASH_SIZE] = { NULL };

unsigned int jenkinsHash(int value)
{
    unsigned int hash = value;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void insert(int value, int index)
{
    HashNode *newNode = (HashNode*) malloc(sizeof(HashNode));
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int isDuplicate(int value, int index)
{
    HashNode *currentNode = hashTable[index];
    while (currentNode != NULL)
    {
        if (currentNode->value == value)
        {
            return 1;
        }
        currentNode = currentNode->next;
    }
    return 0;
}

int main()
{
    FILE *fin = fopen("input.bin", "rb");
    FILE *fout = fopen("output.bin", "wb");

    int n;
    fread(&n, sizeof(int), 1, fin);

    int *arr = malloc(n * sizeof(int));
    fread(arr, sizeof(int), n, fin);

    int *res = calloc(n, sizeof(int));
    int ind = 0;
    for (int i = 0; i < n; i++)
    {
        int index = jenkinsHash(arr[i]) % HASH_SIZE;
        if (!isDuplicate(arr[i], index))
        {
            insert(arr[i], index);
            res[ind] = arr[i];
            ind++;
            res[ind] = INT_MIN;
        }
    }
    fwrite(&ind, sizeof(int), 1, fout);
    for (int i = 0; i < ind; i++)
    {
        fwrite(&res[i], sizeof(int), 1, fout);
    }

    fclose(fin);
    fclose(fout);
    free(arr);

    return 0;
}
