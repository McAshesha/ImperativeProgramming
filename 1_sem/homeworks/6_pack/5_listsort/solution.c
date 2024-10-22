#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000000 // maximum list length 10^6

typedef struct Node
{
    char value[8];
    struct Node *next;
} Node;

Node **array;

void print_array()
{
    for (int key = 0; key < MAX_NODES + 1; key++)
    {
        Node *current = array[key];
        while (current)
        {
            printf("%d %s\n", key, current->value);
            current = current->next;
        }
    }
}

void free_array()
{
    for (int key = 0; key < MAX_NODES + 1; key++)
    {
        Node *current = array[key];
        while (current)
        {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }

    free(array);
}

void add_node(int key, Node *node)
{
    if (!array[key]) {
        array[key] = node;
        return;
    }

    Node *last = array[key];
    while (last->nextL)
    {
        last = last->next;
    }

    last->next = node;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);
    array = (Node *) calloc(MAX_NODES + 1, sizeof(Node *));

    for (int i = 0; i < N; i++)
    {
        int key;
        char value[8];
        scanf("%d %s", &key, value);

        Node *new = (Node *) malloc(sizeof(Node));
        strcpy(new->value, value);
        new->next = NULL;

        add_node(key, new);
    }

    print_array();
    free_array();

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
