#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 64 // Maximum length of the input number string

// Function to convert a number from a given base (system) to decimal (base 10)
int to_decimal(const char number[MAX_LENGTH + 1], int system)
{
    int result = 0, index = 0;

    // Convert each character to its corresponding digit and accumulate the result
    while (number[index] != '\0')
    {
        char symbol = number[index];
        int digit = (symbol >= 'a') ? symbol - 'a' + 10 : symbol - '0';
        result = result * system + digit;
        index++;
    }

    return result;
}

// Function to convert a decimal number to a given base (system)
char *from_decimal(int number, int system)
{
    if (number == 0)
    {
        return "0";
    }

    char temp[MAX_LENGTH + 1];
    int index = 0;

    // Convert the number to the target base and store the result in reverse order
    while (number > 0)
    {
        int digit = number % system;
        char symbol = (digit >= 10) ? digit - 10 + 'a' : digit + '0';
        temp[index++] = symbol;
        number /= system;
    }
    temp[index] = '\0'; // Null-terminate the temporary string

    // Allocate memory for the final result and reverse the string
    char *result = (char *) malloc(index + 1);
    for (int i = 0; i < index; i++)
    {
        result[i] = temp[index - 1 - i];
    }
    result[index] = '\0'; // Null-terminate the final result

    return result;
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int p, q;
    char N[MAX_LENGTH + 1];

    // Read the base of the input number (p), the target base (q), and the number itself (N)
    scanf("%d %d %s", &p, &q, N);

    // Convert the number from base p to decimal (base 10)
    int decimal_number = to_decimal(N, p);

    // Convert the decimal number to the target base q
    char *converted_number = from_decimal(decimal_number, q);

    // Print the converted number
    printf("%s\n", converted_number);

    // Free the dynamically allocated memory
    free(converted_number);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
