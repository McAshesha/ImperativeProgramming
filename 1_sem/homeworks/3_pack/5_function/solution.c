#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M); // Read the values of N and M

    // Dynamically allocate memory for a array (relation)
    int **relation = (int **) malloc(M * sizeof(int *));

    for (int i = 0; i < M; i++)
    {
        relation[i] = (int *) malloc(2 * sizeof(int)); // Each predicate has two integers
        scanf("%d %d", &relation[i][0], &relation[i][1]); // Read the pair of integers
    }

    // Check for duplicate first elements
    for (int i = 0; i < M; i++)
    {
        for (int j = i + 1; j < M; j++)
        {
            if (relation[i][0] == relation[j][0])
            {
                printf("0"); // Output 0 if any duplicates are found
                goto skip; // Exit loops and skip
            }
        }
    }

    // If no duplicates found, output 1
    printf("1");

    if (N == M)
        printf(" 2");

    for (int i = 0; i < M; i++)
    {
        for (int j = i + 1; j < M; j++)
        {
            if (relation[i][1] == relation[j][1])
            {
                goto skip;
            }
        }
    }

    printf(" 3");

    if (N == M)
        printf(" 4 5");

    skip:

    printf("\n");

    // Free dynamically allocated memory
    for (int i = 0; i < M; i++)
    {
        free(relation[i]);
    }
    free(relation);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
