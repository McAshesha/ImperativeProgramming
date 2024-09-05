#include <stdio.h>

#define LENGTH_DAY 3


int get_number_day(char day[LENGTH_DAY])
{
    switch (day[0] + day[1] + day[2])
    {
        case 'M' + 'o' + 'n':
            return 1;

        case 'T' + 'u' + 'e':
            return 2;

        case 'W' + 'e' + 'd':
            return 3;

        case 'T' + 'h' + 'u':
            return 4;

        case 'F' + 'r' + 'i':
            return 5;

        case 'S' + 'a' + 't':
            return 6;

        case 'S' + 'u' + 'n':
            return 7;

        default:
            return 0;
    }
}


int main(void)
{
    char day[LENGTH_DAY];

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%s", day);

    printf("%d\n", get_number_day(day));

    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
