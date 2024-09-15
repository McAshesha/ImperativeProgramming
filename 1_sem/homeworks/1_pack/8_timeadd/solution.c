#include <stdio.h>

int main(void)
{
    int H, M, S, K; // Variables to store hours, minutes, seconds, and additional seconds

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d %d %d", &H, &M, &S, &K); // Read the input values

    // Convert the time to total seconds and add the additional seconds
    int total_seconds = H * 3600 + M * 60 + S + K;

    // Compute new hour, minute, and second values
    H = (total_seconds / 3600) % 24; // Calculate the hour and wrap around 24 hours
    M = (total_seconds / 60) % 60;   // Calculate the minute and wrap around 60 minutes
    S = total_seconds % 60;          // Calculate the seconds

    // Output the updated time in hours, minutes, and seconds
    printf("%d %d %d\n", H, M, S);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
