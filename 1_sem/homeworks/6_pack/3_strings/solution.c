#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 500000

char *strings[MAX_STRINGS];

void createString(int id, int len, char *content)
{
    strings[id] = malloc((len + 1) * sizeof(char));
    strcpy(strings[id], content);
    strings[id][len] = '\0';
}

void deleteString(int id)
{
    free(strings[id]);
    strings[id] = NULL;
}

int countChar(int id, char c)
{
    int count = 0;
    int len = strlen(strings[id]);
    for (int i = 0; i < len; i++)
    {
        if (strings[id][i] == c)
        {
            count++;
        }
    }
    return count;
}

int main() {
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, k, m, id = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &k, &m);
        switch (k)
        {
            case 0:
            	char *content = malloc((m + 1) * sizeof(char));
                scanf("%s", content);
                createString(id, m, content);
                free(content);
                id++;
                break;

            case 1:
                deleteString(m);
                break;

            case 2:
                printf("%s\n", strings[m]);
                break;

            case 3:
                char c;
                scanf(" %c", &c);
                printf("%d\n", countChar(m, c));
                break;
        }
    }

    for (int i = 0; i < id; i++)
    {
        if (strings[i])
        {
            free(strings[i]);
        }
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
