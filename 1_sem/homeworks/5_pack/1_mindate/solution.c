#include <stdio.h>
#include <stdlib.h>

typedef struct DateTime_s
{
    int year, month, day ;
    int hours, minutes, seconds ;
} DateTime;

DateTime min(const DateTime *arr , int cnt);

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    DateTime *dates = (DateTime *) malloc(sizeof(DateTime) * N);

    for (int i = 0; i < N; i++)
    {
        DateTime *date = dates + i;
        scanf("%d %d %d %d %d %d",
            &date->year, &date->month, &date->day,
                &date->hours, &date->minutes, &date->seconds);
    }

    DateTime minimum = min(dates, N);
    printf("%d %d %d %d %d %d\n",
        minimum.year, minimum.month, minimum.day,
        minimum.hours, minimum.minutes, minimum.seconds);

    free(dates);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}

long long convert_date(const DateTime *date)
{
    return date->year * 10000000000 + date->month * 100000000 + date->day * 1000000 +
        date->hours * 10000 + date->minutes * 100 + date->seconds;
}

DateTime min(const DateTime *arr , int cnt)
{
    DateTime *min = arr;
    long long min_value = convert_date(min);

    for (int i = 1; i < cnt; i++)
    {
        long long converted = convert_date(arr + i);
        if (converted < min_value)
        {
            min_value = converted;
            min = arr + i;
        }
    }
    return *min;
}
