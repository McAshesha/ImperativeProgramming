#include <stdio.h>

int main(void)
{
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    int result = 0, i = 0; // Initialize result and loop counter
    scanf("%d", &N); // Read the total number of bits

    // Loop to process N characters (bits)
    for (; i < N; i++)
    {
        char byte;
        scanf(" \n%c", &byte); // Read each bit, skipping whitespace and new lines

        // If we've processed 8 bits, print the result and reset
        if (i % 8 == 0 && i != 0)
        {
            printf("%d ", result); // Print the converted byte
            result = 0; // Reset result for the next byte
        }

        // Convert '1' to the corresponding bit in the byte
        if (byte == '1')
        {
            result += 1 << (i % 8); // Shift left and accumulate
        }
    }

    printf("%d ", result);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
