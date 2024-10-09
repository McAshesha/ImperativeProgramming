#include <stdio.h>
#define MAX_LENGTH 100

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt)
{
    int i = -1;
    while (i++, iStr[i]  != '\0' && iStr[i] != '\n')
    {
        if (iStr[i] >= 'a' && iStr[i] <= 'z')
        {
            (*oLowerCnt)++;
        }
        else if (iStr[i] >= 'A' && iStr[i] <= 'Z')
        {
            (*oUpperCnt)++;
        }
        else if (iStr[i] >= '0' && iStr[i] <= '9')
        {
            (*oDigitsCnt)++;
        }
    }
    return i;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char buffer[MAX_LENGTH + 1];
    int line = 0;

    while(line++, gets(buffer))
    {
        int lower = 0, upper = 0, digits = 0;
        int letters = calcLetters(buffer, &lower, &upper, &digits);
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n",
            line, letters, lower + upper, lower, upper, digits);
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
