#include <stdio.h>

typedef struct LongNum_s
{
    int len;
    int arr[3000];
} LongNum;

void print_num(LongNum num)
{
    for (int i = num.len - 1; i >= 0; i--)
    {
        printf("%d", num.arr[i]);
    }
    printf("\n");
}

int multiply(int x, LongNum *num)
{
    int carry = 0;

    for (int i = 0; i < num->len; i ++)
    {
        int prod = num->arr[i] * x + carry;
        num->arr[i] = prod % 10;
        carry = prod / 10;
    }

    while (carry)
    {
        num->arr[num->len ++] = carry % 10;
        carry /= 10;
    }
    return num->len;
}

LongNum factorial(int n)
{
    LongNum num = {.len = 1};
    num.arr[0] = 1;

    for (int x = 2; x <= n; x ++)
    {
        num.len = multiply(x, &num);
    }
    return num;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);
    LongNum num = factorial(N);
    print_num(num);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
