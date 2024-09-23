#include <stdio.h>

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Variables to keep track of the previous and current characters
    char previous = ' ', current = ' ';
    // Flags to track whether we are inside a single-line or multi-line comment
    char strCom = 0, caseCom = 0;
    // Flag to track the start of the input
    char start = 1;

    // Infinite loop to process each character from the input file
    while (1)
    {
        // Read a character from the input file
        if (scanf("%c", &current) != 1)
        {
            // If the end of the file is reached, check if we are inside a comment
            if (!(strCom || caseCom) || !caseCom && previous == '\n')
            {
                // Print the last character if not inside a comment
                printf("%c", previous);
            }
            break; // Exit the loop as there are no more characters to read
        }

        // If it's the start of reading the file, initialize previous and continue
        if (start)
        {
            start = 0;
            previous = current;
            continue;
        }

        // Check for the start of a comment
        if (previous == '/' && !(strCom || caseCom))
        {
            // If "//" is detected, mark the start of a single-line comment
            if (current == '/')
            {
                strCom = 1;
                scanf("%c", &current);
                previous = current;
                continue;
            }
            // If "/*" is detected, mark the start of a multi-line comment
            if (current == '*')
            {
                caseCom = 1;
                scanf("%c", &current);
                previous = current;
                continue;
            }
        }

        // Check for the end of a multi-line comment
        if (previous == '*' && current == '/' && caseCom)
        {
            caseCom = 0; // End of multi-line comment
            scanf("%c", &current);
            previous = current;
            continue;
        }

        // Handle new line character, which ends a single-line comment
        if (previous == '\n')
        {
            strCom = 0; // End of single-line comment
            printf("%c", previous); // Print the new line character
        }
        else if (!(strCom || caseCom))
        {
            // If not inside any comment, print the previous character
            printf("%c", previous);
        }

        // Move to the next character
        previous = current;
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
