#include <stdio.h>
#define MAX_LENGTH 15

int readTime(const char *iStr, int *oHours, int *oMinutes, int *oSeconds)
{
    int hours = 0, minutes = 0, seconds = 0;
    int n = sscanf(iStr, "%d:%d:%d", &hours, &minutes, &seconds);

    if (n < 2 || hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59)
    {
        return 0;  // Input does not match the expected format or invalid time values
    }

    if (oHours)
    {
        *oHours = hours;
    }
    if (oMinutes)
    {
        *oMinutes = minutes;
    }
    if (oSeconds)
    {
        *oSeconds = seconds;
    }

    return 1;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int hours, minutes, seconds;
    char testStr[MAX_LENGTH + 1];

    scanf("%s", testStr);

    if (readTime(testStr, &hours, &minutes, &seconds)) {
        printf("1 %d %d %d\n", hours, minutes, seconds);
    } else {
        printf("0 -1 -1 -1\n");
    }

    if (readTime(testStr, &hours, &minutes, NULL)) {
        printf("1 %d %d\n", hours, minutes);
    } else {
        printf("0 -1 -1\n");
    }

    if (readTime(testStr, &hours, NULL, NULL)) {
        printf("1 %d\n", hours);
    } else {
        printf("0 -1\n");
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
