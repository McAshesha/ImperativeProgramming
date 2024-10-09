#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 1000000

int get_length_word(char *str, char *separators)
{
    int i = -1;
    while (i++, str[i] != '\0' && strchr(separators, str[i]) == NULL);
    return i;
}

int get_count_upper(char *str, int length)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            count++;
        }
    }
    return count;
}


int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char buffer[MAX_LENGTH + 1];
    gets(buffer);

    int length = strlen(buffer), i = 0;
    char *separators = ".:,;\n";
    
    while (i < length)
    {
        int length_word = get_length_word(buffer + i, separators);
        if (length_word != 0)
        {
            int count_upper = get_count_upper(buffer + i, length_word);
            buffer[i + length_word] = '\0';
            printf("%d/%d %s\n", count_upper, length_word, buffer + i);
            i += length_word;
        }
        i ++;
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
