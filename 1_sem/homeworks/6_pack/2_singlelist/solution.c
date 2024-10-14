#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char value[16];
    int next;
} Node;

Node nodes[1000000];
int head, tail;

char temp[30] = "";

void add(int index, char* value)
{
    strcpy(nodes[tail].value, value);
    if (index == -1)
    {
        nodes[tail].next = head;
        head = tail;
    }
    else
    {
        nodes[tail].next = (nodes + index)->next;
        nodes[index].next = tail;
    }
    sprintf(temp, "%d", tail ++);
}

void delete(int index)
{
    int target;
    if (index == -1)
    {
        target = head;
        head = nodes[head].next;
    }
    else
    {
        target = nodes[index].next;
        nodes[index].next = nodes[target].next;
    }
    sprintf(temp, "%s", nodes[target].value);
}

int main() {
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);

    char **result = malloc(sizeof(char *) * 1000000);
    int indx = 0;

    while (T--)
    {
        int N, F, Q;
        scanf("%d%d%d", &N, &F, &Q);
        head = F;
        tail = N;

        for (int i = 0; i < N; i++)
        {
            scanf("%s%d", nodes[i].value, &nodes[i].next);
        }
        while (Q --)
        {
            int op, index;
            char value[16];
            scanf("%d%d", &op, &index);

            if (op == 0)
            {
                scanf("%s", value);
                add(index, value);
            }
            else
            {
                delete(index);
            }
            result[indx ++] = strdup(temp);
        }

        result[indx ++] = "===";
        for (int i = head; i != -1; i = nodes[i].next)
        {
            result[indx ++] = strdup(nodes[i].value);
        }

        result[indx ++] = "===";
    }

    for (int i = 0; i < indx; i ++)
    {
        printf("%s\n", result[i]);
    }
    free(result);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
