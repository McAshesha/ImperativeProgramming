#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort, used to sort characters in ascending order
int compare(char *a, char *b)
{
    return *a - *b;
}

// Function to swap two characters
void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N); // Read the length of the string

    // Allocate memory for the original string and the result string
    char *str = (char *) malloc(N + 1), *rslt = (char *) malloc(N + 1);

    // Read the string and copy it to the result string
    for (int i = 0; i < N; i++)
    {
        scanf(" %c\n", str + i);
        rslt[i] = str[i];
    }
    str[N] = rslt[N] = '\0'; // Null-terminate both strings

    // Generate the next lexicographical permutation of the string
    for (int i = N - 2; i >= 0; i--)
    {
        // Sort the suffix starting from index i
        qsort(rslt + i, N - i, sizeof(char), compare);

        // Find the next lexicographical permutation by swapping
        for (int j = i + 1; j < N; j++)
        {
            swap(rslt + i, rslt + j);
            if (strcmp(str + i, rslt + i) < 0)
            {
                goto skip; // If a valid permutation is found, exit the loop
            }
        }
    }

    skip:

    // Print the result string with spaces between characters
    for (int i = 0; i < N - 1; i++)
    {
        printf("%c ", rslt[i]);
    }
    printf("%c\n", rslt[N - 1]);

    // Free the dynamically allocated memory
    free(str);
    free(rslt);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
