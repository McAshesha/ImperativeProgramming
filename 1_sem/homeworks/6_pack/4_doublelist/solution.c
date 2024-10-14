#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    int next;
    int prev;
} Node;

void delete(Node *nodes, int idx)
{
    printf("%d\n", nodes[idx].value);
    nodes[nodes[idx].prev].next = nodes[idx].next;
    nodes[nodes[idx].next].prev = nodes[idx].prev;
}

void add_forward(Node *nodes, int idx, int *size, int value)
{
    nodes[*size].next = nodes[idx].next;
    nodes[*size].prev = idx;
    nodes[nodes[idx].next].prev = *size;
    nodes[idx].next = *size;
    nodes[*size].value = value;
    printf("%d\n", *size - 1);
    (*size)++;
}

void add_back(Node *nodes, int idx, int *size, int value)
{
    nodes[*size].next = idx;
    nodes[*size].prev = nodes[idx].prev;
    nodes[nodes[idx].prev].next = *size;
    nodes[idx].prev = *size;
    nodes[*size].value = value;
    printf("%d\n", *size - 1);
    (*size)++;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++)
    {
        int N, F, L, Q;
        scanf("%d %d %d %d", &N, &F, &L, &Q);

        Node *nodes = (Node *) calloc((N + Q + 1), sizeof(Node));
        int size = N + 1;

        nodes[0].next = F + 1;
        nodes[0].prev = L + 1;

        for (int i = 1; i <= N; i++)
        {
            int next, prev;
            scanf("%d %d %d", &nodes[i].value, &next, &prev);
            nodes[i].next = ++next;
            nodes[i].prev = ++prev;
        }

        for (int i = 0; i < Q; i++)
        {
            int op, idx, value;
            scanf("%d %d", &op, &idx);
            idx++;

            if (op != 0)
            {
                scanf("%d", &value);
            }

            if (op == 1)
            {
                add_forward(nodes, idx, &size, value);
            }
            else if (op == -1)
            {
                add_back(nodes, idx, &size, value);
            }
            else
            {
                delete(nodes, idx);
            }
        }

        printf("===\n");
        for (int i = nodes[0].next; i != 0; i = nodes[i].next)
        {
            printf("%d\n", nodes[i].value);
        }
        printf("===\n");

        free(nodes);
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}