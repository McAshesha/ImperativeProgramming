#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

typedef struct LongNum_s
{
    int len;
    int *arr;
} LongNum;

LongNum mult_nums(LongNum a, LongNum b)
{
    LongNum c = {.len=0};
    c.arr = calloc(MAX_LENGTH * MAX_LENGTH + 1, sizeof(int));
    for (int i = 0; i < a.len; i++)
    {
        for (int j = 0; j < b.len; j++)
        {
            c.arr[i + j] += a.arr[i] * b.arr[j];
            c.arr[i + j + 1] += c.arr[i + j] / 10;
            c.arr[i + j] %= 10;
        }
    }

    c.len = a.len + b.len;
    while (c.len > 1 && c.arr[c.len - 1] == 0)
    {
        c.len--;
    }

    return c;
}

LongNum str_to_num(char *str)
{
    LongNum num;
    num.len = strlen(str);
    num.arr = malloc(sizeof(int) * (MAX_LENGTH + 1));
    for (int i = 0; i < num.len; i++)
    {
        num.arr[i] = str[num.len - i - 1] - '0';
    }
    return num;
}

void print_num(LongNum num)
{
    for (int i = num.len - 1; i >= 0; i--)
    {
        printf("%d", num.arr[i]);
    }
    printf("\n");
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char a_str[MAX_LENGTH + 1], b_str[MAX_LENGTH + 1];
    LongNum a, b, c;

    scanf("%s", a_str);
    scanf("%s", b_str);

    a = str_to_num(a_str);
    b = str_to_num(b_str);

    c = mult_nums(a, b);

    print_num(c);

    free(a.arr);
    free(b.arr);
    free(c.arr);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
