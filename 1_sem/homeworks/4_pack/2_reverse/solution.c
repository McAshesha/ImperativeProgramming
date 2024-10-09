#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100

void reverse(char *start, int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        int tmp = *(start + i);
        *(start + i) = *(start + len - i - 1);
        *(start + len - i - 1) = tmp;
    }
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    for (int _ = 0; _ < N; _++)
    {
        char str[MAX_LENGTH + 1];
        scanf("%s", str);
        reverse(str, strlen(str));
        printf("%s\n", str);
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
