#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double value;
    int next;
} Node;

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, F;
    scanf("%d %d", &N, &F);

    Node* nodes = malloc(N * sizeof(Node));

    for (int i = 0; i < N; i++)
    {
        scanf("%lf %d", &nodes[i].value, &nodes[i].next);
    }

    while (F != -1)
    {
        printf("%.3lf\n", nodes[F].value);
        F = nodes[F].next;
    }

    free(nodes);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
