#include <stdio.h>

typedef struct LongNum_s
{
    int len;
    int arr[500];
} LongNum;

void print_num(LongNum num)
{
    for (int i = num.len - 1; i >= 0; i--)
    {
        printf("%d", num.arr[i]);
    }
    printf("\n");
}

LongNum add_nums(LongNum a, LongNum b)
{
    LongNum result;
    result.len = 0;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len || carry; i++)
    {
        result.len++;

        if (i == a.len && i == b.len)
        {
            result.arr[i] = carry;
            carry = 0;
            continue;
        }

        int sum = i == a.len ? b.arr[i] + carry :
            i == b.len ? a.arr[i] + carry :
                a.arr[i] + b.arr[i] + carry;

        result.arr[i] = sum % 10;
        carry = sum / 10;
    }
    return result;
}

LongNum fib(int N)
{
    LongNum a, b;
    a.len = b.len = 1;
    a.arr[0] = b.arr[0] = 1;
    for (int i = 2; i < N; i++)
    {
        LongNum c = add_nums(a, b);
        a = b;
        b = c;
    }
    return b;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);
    LongNum result = fib(N);
    print_num(result);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
