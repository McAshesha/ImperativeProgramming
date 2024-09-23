#include <stdio.h>
#define MAX_VALUE 100000 // Define the maximum possible value

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N_A, N_B;
    int A[MAX_VALUE + 1] = {0}; // Array to track elements in set A, initialized to 0

    // Read the number of elements in set A
    scanf("%d", &N_A);

    // Mark the elements of set A in the array A[]
    for (int i = 0; i < N_A; i++)
    {
        int element;
        scanf("%d", &element); // Read each element of set A
        A[element] = 1; // Mark the element's presence in set A
    }

    // Read the number of elements in set B
    scanf("%d", &N_B);

    // Unmark elements that are present in set B
    for (int i = 0; i < N_B; i++)
    {
        int element;
        scanf("%d", &element); // Read each element of set B
        A[element] = 0; // Unmark the element if it exists in set A
    }

    int index = 0;
    int result[MAX_VALUE + 1]; // Array to store the result set

    // Collect elements that are in set A but not in set B
    for (int i = 0; i < MAX_VALUE + 1; i++)
    {
        if (A[i]) // If the element is marked (i.e., in A but not in B)
        {
            result[index++] = i; // Add it to the result array
        }
    }

    // Output the number of elements in the result set
    printf("%d\n", index);

    // Output all elements in the result set
    for (int i = 0; i < index - 1; i++)
    {
        printf("%d ", result[i]); // Print each element followed by a space
    }

    // Handle the last element separately to avoid trailing space
    if (index != 0)
    {
        printf("%d\n", result[index - 1]); // Print the last element with a newline
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
