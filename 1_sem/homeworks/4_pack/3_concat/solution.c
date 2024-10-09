#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100

char *concat(char *pref, char *suff)
{
    while (*pref != '\0')
    {
        pref++;
    }
    while (*suff != '\0')
    {
        *pref++ = *suff++;
    }
    *pref = '\0';
    return pref;
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    char *buffer = (char *) malloc(N * MAX_LENGTH + 1);
    char *pref = buffer;
    *pref = '\0';

    for (int _ = 0; _ < N; _++)
    {
        char str[MAX_LENGTH + 1];
        scanf("%s", str);
        pref = concat(pref, str);
    }

    printf("%s\n", buffer);

    free(buffer);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
