#include <stdio.h>
#define LAST_ASCII 126
#define FIRST_ASCII 32

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int count[LAST_ASCII + 1] = {0};
    char symbol;
    while (scanf("%c", &symbol) == 1 && symbol != '\0' && symbol != EOF)
    {
        count[symbol]++;
    }

    for (int i = FIRST_ASCII; i < LAST_ASCII + 1; i++)
    {
        if (count[i])
        {
            printf("%c ", i);
            for (int _ = 0; _ < count[i]; _++)
            {
                printf("#");
            }
            printf("\n");
        }
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
