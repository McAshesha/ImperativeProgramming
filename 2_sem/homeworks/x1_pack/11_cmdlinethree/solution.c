#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 101

void process_char(char c, int *in_quotes, int *backslash_count, char **current_arg, int *arg_len, int *arg_cap, int *count_quot)
{
    if (c == '"') {
        (*count_quot)++;
    }
    else {
        *count_quot = 0;
    }
    if (!*in_quotes)
    {
        if (c == '\\')
        {
            (*backslash_count)++;
        }
        else if (c == '"')
        {
            int num_back = *backslash_count;
            *backslash_count = 0;
            if (num_back % 2 == 0)
            {
                int add = num_back / 2;
                while (add-- > 0)
                {
                    if (*arg_len >= *arg_cap - 1)
                    {
                        *arg_cap *= 2;
                        *current_arg = realloc(*current_arg, *arg_cap);
                    }
                    (*current_arg)[(*arg_len)++] = '\\';
                }
                *in_quotes = 1;
                if (*count_quot % 2 == 0) {
                    // Добавляем кавычку в аргумент
                    if (*arg_len >= *arg_cap - 1) {
                        *arg_cap *= 2;
                        *current_arg = realloc(*current_arg, *arg_cap);
                    }
                    (*current_arg)[(*arg_len)++] = '"'; // Добавляем кавычку в аргумент
                }
            }
            else
            {
                int add = (num_back - 1) / 2;
                while (add-- > 0)
                {
                    if (*arg_len >= *arg_cap - 1)
                    {
                        *arg_cap *= 2;
                        *current_arg = realloc(*current_arg, *arg_cap);
                    }
                    (*current_arg)[(*arg_len)++] = '\\';
                }
                if (*arg_len >= *arg_cap - 1)
                {
                    *arg_cap *= 2;
                    *current_arg = realloc(*current_arg, *arg_cap);
                }
                (*current_arg)[(*arg_len)++] = '"';
            }
        }
        else
        {
            while (*backslash_count > 0)
            {
                if (*arg_len >= *arg_cap - 1)
                {
                    *arg_cap *= 2;
                    *current_arg = realloc(*current_arg, *arg_cap);
                }
                (*current_arg)[(*arg_len)++] = '\\';
                (*backslash_count)--;
            }
            if (c == ' ')
            {
                if (*arg_len > 0)
                {
                    (*current_arg)[*arg_len] = '\0';
                    *arg_len = 0;
                }
            }
            else
            {
                if (*arg_len >= *arg_cap - 1)
                {
                    *arg_cap *= 2;
                    *current_arg = realloc(*current_arg, *arg_cap);
                }
                (*current_arg)[(*arg_len)++] = c;
            }
        }
    }
    else
    {
        if (c == '\\')
        {
            (*backslash_count)++;
        }
        else if (c == '"')
        {
            int num_back = *backslash_count;
            *backslash_count = 0;
            if (num_back % 2 == 0)
            {
                int add = num_back / 2;
                while (add-- > 0)
                {
                    if (*arg_len >= *arg_cap - 1)
                    {
                        *arg_cap *= 2;
                        *current_arg = realloc(*current_arg, *arg_cap);
                    }
                    (*current_arg)[(*arg_len)++] = '\\';
                }
                *in_quotes = 0;
            }
            else
            {
                int add = (num_back - 1) / 2;
                while (add-- > 0)
                {
                    if (*arg_len >= *arg_cap - 1)
                    {
                        *arg_cap *= 2;
                        *current_arg = realloc(*current_arg, *arg_cap);
                    }
                    (*current_arg)[(*arg_len)++] = '\\';
                }
                if (*arg_len >= *arg_cap - 1)
                {
                    *arg_cap *= 2;
                    *current_arg = realloc(*current_arg, *arg_cap);
                }
                (*current_arg)[(*arg_len)++] = '"';
            }
        }
        else
        {
            while (*backslash_count > 0)
            {
                if (*arg_len >= *arg_cap - 1)
                {
                    *arg_cap *= 2;
                    *current_arg = realloc(*current_arg, *arg_cap);
                }
                (*current_arg)[(*arg_len)++] = '\\';
                (*backslash_count)--;
            }
            if (*arg_len >= *arg_cap - 1)
            {
                *arg_cap *= 2;
                *current_arg = realloc(*current_arg, *arg_cap);
            }
            (*current_arg)[(*arg_len)++] = c;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char line[MAX_LINE];
    gets(line);
    line[strcspn(line, "\n")] = '\0';

    int in_quotes = 0;
    int backslash_count = 0;
    char *current_arg = malloc(16);
    int arg_cap = 16;
    int arg_len = 0;
    int count_quot = 0;

    char *p = line;
    while (*p != '\0')
    {
        if (!in_quotes && *p == ' ')
        {
            while (backslash_count > 0)
            {
                if (arg_len >= arg_cap - 1)
                {
                    arg_cap *= 2;
                    current_arg = realloc(current_arg, arg_cap);
                }
                current_arg[arg_len++] = '\\';
                backslash_count--;
            }
            if (arg_len > 0)
            {
                current_arg[arg_len] = '\0';
                printf("[%s]\n", current_arg);
                arg_len = 0;
            }
            while (*p == ' ') p++;
        }
        else
        {
            process_char(*p, &in_quotes, &backslash_count, &current_arg, &arg_len, &arg_cap, &count_quot);
            p++;
        }
    }

    if (!in_quotes)
    {
        while (backslash_count > 0)
        {
            if (arg_len >= arg_cap - 1)
            {
                arg_cap *= 2;
                current_arg = realloc(current_arg, arg_cap);
            }
            current_arg[arg_len++] = '\\';
            backslash_count--;
        }
    }

    if (arg_len > 0)
    {
        current_arg[arg_len] = '\0';
        printf("[%s]\n", current_arg);
    }

    free(current_arg);
    return 0;
}