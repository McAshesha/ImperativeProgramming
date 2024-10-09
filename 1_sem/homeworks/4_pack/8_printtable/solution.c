#include <stdio.h>
#define MAX_ID 100000

int get_number_length(int number)
{
    if (number <= 9)
    {
        return 1;
    }

    int length = 1;
    while (number /= 10)
    {
        length++;
    }
    return length;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void print_indent(int length_1, int length_2, int length_3)
{
    printf("+");
    for (int i = 0; i < length_1 + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < length_2 + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < length_3 + 2; i++)
    {
        printf("-");
    }
    printf("+\n");
}

void print_number(int length, int number)
{
    int count = length - get_number_length(number);
    for (int j = 0; j < count; j++)
    {
        printf(" ");
    }
    printf("%d |", number);
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    int times[MAX_ID + 1] = {0};
    int counts[MAX_ID + 1] = {0};

    int length_id = 1;
    int length_count = 1;
    int length_time = 1;

    for (int i = 0; i < N; i++)
    {
        int ID, time;
        scanf("%d %d", &ID, &time);

        times[ID] += time;
        counts[ID]++;

        length_id = max(length_id, get_number_length(ID));
        length_count = max(length_count, get_number_length(counts[ID]));
        length_time = max(length_time, get_number_length(times[ID]));
    }

    print_indent(length_id, length_count, length_time);
    for (int ID = 0; ID < MAX_ID + 1; ID++)
    {
        if (counts[ID] == 0)
        {
            continue;
        }

        printf("| ");
        print_number(length_id, ID);
        printf(" ");
        print_number(length_count, counts[ID]);
        printf(" ");
        print_number(length_time, times[ID]);
        printf("\n");

        print_indent(length_id, length_count, length_time);
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
