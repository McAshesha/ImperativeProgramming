#include <stdio.h>

// Function to check if a given year is a leap year
int is_leap(int year)
{
    // A year is a leap year if it is divisible by 4 but not by 100,
    // or it is divisible by 400.
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a given month of a given year
int get_days_in_months(int month, int year)
{
    switch (month) {
        case 2:
            // February has 29 days in a leap year, 28 otherwise
                return is_leap(year) ? 29 : 28;

        case 4:
        case 6:
        case 9:
        case 11:
            // April, June, September, and November have 30 days
            return 30;

        default:
            // All other months have 31 days
                return 31;
    }
}

int main(void)
{
	/* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int D, M, Y, K;
    scanf("%d %d %d %d", &D, &M, &Y, &K); // Read the initial date and the number of days to add

    while (K-- > 0)
    {
        if (++D > get_days_in_months(M, Y))
        {
            D = 1; // Reset day and possibly increment month
            if (++M > 12) // New year, if the number of months exceeds 12
            {
                M = 1; // Reset month and increment year
                Y++;
            }
        }
    }

    printf("%d %d %d", D, M, Y); // Print the final date

	/* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
