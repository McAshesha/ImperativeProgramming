;#include <stdio.h>
#include <stdlib.h>

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int argc = 0;
    char **argv = NULL;
    int argv_capacity = 0;

    char *current_arg = NULL;
    size_t current_arg_size = 0;
    size_t current_arg_capacity = 0;

    int in_quotes = 0;
    int in_arg = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (c == '"')
        {
            if (in_quotes)
            {
                in_quotes = 0;
                if (current_arg != NULL)
                {
                    current_arg[current_arg_size] = '\0';
                    if (argc >= argv_capacity)
                    {
                        argv_capacity = argv_capacity ? argv_capacity * 2 : 4;
                        argv = realloc(argv, argv_capacity * sizeof(char *));
                    }
                    argv[argc++] = current_arg;
                    current_arg = NULL;
                    current_arg_size = 0;
                    current_arg_capacity = 0;
                }
            } else
            {
                in_quotes = 1;
                if (!in_arg)
                {
                    in_arg = 1;
                    current_arg_capacity = 16;
                    current_arg = malloc(current_arg_capacity);
                    current_arg_size = 0;
                }
            }
        }
        else if (c == ' ' && !in_quotes)
        {
            if (in_arg)
            {
                in_arg = 0;
                if (current_arg != NULL)
                {
                    current_arg[current_arg_size] = '\0';
                    if (argc >= argv_capacity)
                    {
                        argv_capacity = argv_capacity ? argv_capacity * 2 : 4;
                        argv = realloc(argv, argv_capacity * sizeof(char *));
                    }
                    argv[argc++] = current_arg;
                    current_arg = NULL;
                    current_arg_size = 0;
                    current_arg_capacity = 0;
                }
            }
        }
        else
        {
            if (!in_arg)
            {
                in_arg = 1;
                current_arg_capacity = 16;
                current_arg = malloc(current_arg_capacity);
                current_arg_size = 0;
            }
            if (current_arg_size + 1 >= current_arg_capacity)
            {
                current_arg_capacity *= 2;
                current_arg = realloc(current_arg, current_arg_capacity);
            }
            current_arg[current_arg_size++] = c;
        }
    }

    if ((in_arg || in_quotes) && current_arg != NULL)
    {
        current_arg[current_arg_size] = '\0';
        if (argc >= argv_capacity)
        {
            argv_capacity = argc + 1;
            argv = realloc(argv, argv_capacity * sizeof(char *));
        }
        argv[argc++] = current_arg;
    }

    for (int i = 0; i < argc; i++)
    {
        printf("[%s]\n", argv[i]);
        free(argv[i]);
    }
    free(argv);

    return 0;
}
