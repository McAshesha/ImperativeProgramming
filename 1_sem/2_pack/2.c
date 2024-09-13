#include <stdio.h>

#define LENGTH_DAY 4 // Define a constant for the length of the day abbreviation + 1 for null terminator

// Function to get the day number based on a 3-letter abbreviation of the day
int get_number_day(const char day[LENGTH_DAY])
{
    // Use a switch case to check the sum of the ASCII values of the first three letters
    switch (day[0] + day[1] + day[2])
    {
        case 'M' + 'o' + 'n':
            return 1; // Monday

        case 'T' + 'u' + 'e':
            return 2; // Tuesday

        case 'W' + 'e' + 'd':
            return 3; // Wednesday

        case 'T' + 'h' + 'u':
            return 4; // Thursday

        case 'F' + 'r' + 'i':
            return 5; // Friday

        case 'S' + 'a' + 't':
            return 6; // Saturday

        case 'S' + 'u' + 'n':
            return 7; // Sunday

        default:
            return 0; // Invalid input
    }
}

int main(void)
{
    char day[LENGTH_DAY]; // Array to store the 3-letter day abbreviation

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Read the 3-letter day abbreviation from the input file
    scanf("%3s", day); // Read up to 3 characters to avoid buffer overflow

    // Output the corresponding number of the day
    printf("%d", get_number_day(day));

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
