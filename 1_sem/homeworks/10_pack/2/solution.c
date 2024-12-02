#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

typedef struct
{
    char value[8];
    int key;
} Record;

int main()
{
    int N;
    scanf("%d", &N);

    Record *records[ARRAY_SIZE + 1] = { NULL };
    int capacities[ARRAY_SIZE + 1] = { 0 };
    int counts[ARRAY_SIZE + 1] = { 0 };

    for (int i = 0; i <= ARRAY_SIZE; ++i)
    {
        records[i] = NULL;
        capacities[i] = 0;
        counts[i] = 0;
    }

    for (int i = 0; i < N; ++i)
    {
        Record record;
        scanf("%d %s", &record.key, record.value);

        int key = record.key;

        if (counts[key] + 1 >= capacities[key])
        {
            capacities[key] = capacities[key] == 0 ? 1 : capacities[key] * 2;
            records[key] = realloc(records[key], capacities[key] * sizeof(Record));
        }

        records[key][counts[key]] = record;
        records[key][counts[key] + 1].key = -1;
        counts[key]++;
    }

    for (int i = 0; i <= ARRAY_SIZE; i++)
    {
        if (records[i] != NULL)
        {
            int j = 0;
            while (records[i][j].key != -1)
            {
                printf("%d %s\n", records[i][j].key, records[i][j].value);
                j++;
            }

            free(records[i]);
        }
    }
    return 0;
}
