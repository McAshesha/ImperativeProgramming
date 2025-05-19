#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int module(long long x, int mod)
{
    return (x % mod + mod) % mod;
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "No parameters specified.\n");
        return 13;
    }

    int mod = -1;
    int index = 1;

    if (argc == 6)
    {
        if (strcmp(argv[1], "-m") == 0)
        {
            mod = atoi(argv[2]);
            index = 3;
        } else
        {
            mod = atoi(argv[5]);
        }
    }

    char *operation = argv[index];
    long long result;

    if (operation[0] == 's' && strcmp(operation, "sub") == 0)
    {
        long long num1 = atoll(argv[index + 1]);
        long long num2 = atoll(argv[index + 2]);
        result = num1 - num2;
    }
    else if (operation[0] == 'a' && strcmp(operation, "add") == 0)
    {
        long long num1 = atoll(argv[index + 1]);
        long long num2 = atoll(argv[index + 2]);
        result = num1 + num2;
    }
    else if (operation[0] == 'm' && strcmp(operation, "mul") == 0)
    {
        long long num1 = atoll(argv[index + 1]);
        long long num2 = atoll(argv[index + 2]);
        result = num1 * num2;
    }
    else
    {
        fprintf(stderr, "Invalid operation: %s\n", operation);
        return 1;
    }

    if (mod != -1)
    {
        result = module(result, mod);
    }

    printf("%lld\n", result);

    return 0;
}