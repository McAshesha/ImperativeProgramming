#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 2000005

typedef struct Node
{
    uint64_t value;
    int position;
    struct Node* next;
} Node;

Node* hashtable[MAX];

uint64_t func(uint64_t s, uint64_t a, uint64_t b, uint64_t c, uint64_t M)
{
    return (s * s * a + s * b + c) % M;
}

void insert(uint64_t index, uint64_t value, int position)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->position = position;
    newNode->next = hashtable[index];
    hashtable[index] = newNode;
}

int search(uint64_t index, uint64_t value)
{
    Node* current = hashtable[index];
    while (current != NULL)
    {
        if (current->value == value)
        {
            return current->position;
        }
        current = current->next;
    }
    return 0;
}

int main()
{
    uint64_t M;
    int a, b, c;
    scanf("%llu", &M);
    scanf("%d %d %d", &a, &b, &c);

    uint64_t state = 1;
    int l = 0, r = 0;

    insert(state % MAX, state, 0);

    for (int i = 1; i <= MAX; i++)
    {
        state = func(state, a, b, c, M);
        uint64_t index = state % MAX;

        int foundPosition = search(index, state);
        if (foundPosition)
        {
            r = i;
            l = foundPosition - 1;
            break;
        }

        insert(index, state, i);
    }

    printf("%d %d\n", ++l, r);

    return 0;
}
