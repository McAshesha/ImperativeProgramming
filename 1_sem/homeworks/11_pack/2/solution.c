#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

typedef void (*callback)(void* ctx, int* value);

void arrayForeach(void* ctx, callback func, int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        func(ctx, &arr[i]);
    }
}

void listForeach(void* ctx, callback func, struct Node* head)
{
    struct Node* current = head;
    while (current != NULL)
    {
        func(ctx, &current->data);
        current = current->next;
    }
}

void sumEven(void* ctx, int* value)
{
    int *sum = (int*)ctx;
    if (*value % 2 == 0)
    {
        *sum += *value;
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    struct Node* head = NULL;
    struct Node* tail = NULL;
    for (int i = 0; i < N; i++)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int sumArray = 0;
    int sumList = 0;
    arrayForeach(&sumArray, sumEven, arr, N);
    listForeach(&sumList, sumEven, head);
    printf("%d %d\n", sumArray, sumList);

    struct Node* current = head;
    while (current != NULL)
    {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
