#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Label_s {
    char name [16]; //имя автора (заканчивается нулём)
    int age; //возраст автора (сколько лет)
} Label ;

typedef struct NameStats_s {
    int cntTotal ; //сколько всего подписей
    int cntLong ; //сколько подписей с именами длиннее 10 букв
} NameStats ;

typedef struct AgeStats_s {
    int cntTotal ; //сколько всего подписей
    int cntAdults ; //сколько подписей взрослых (хотя бы 18 лет)
    int cntKids ; //сколько подписей детей (меньше 14 лет)
} AgeStats ;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges)
{
    oAges->cntTotal = oNames->cntTotal = cnt;
    for (int i = 0; i < cnt; i ++)
    {
        Label *label = arr + i;
        if (strlen(label->name) > 10)
        {
            oNames->cntLong ++;
        }
        if (label->age >= 18)
        {
            oAges->cntAdults ++;
        }
        if (label->age < 14)
        {
            oAges->cntKids ++;
        }

    }
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    Label *arr = malloc(sizeof(Label) * N);
    NameStats names = {0, 0};
    AgeStats ages = {0, 0, 0};

    for (int i = 0; i < N; i ++)
    {
        scanf("%s %d %*[^\n]%*c", (arr + i)->name, &(arr + i)->age);
    }
    calcStats(arr, N, &names, &ages);

    free(arr);

    printf("names: total = %d\nnames: long = %d\n", names.cntTotal, names.cntLong);
    printf("ages: total = %d\nages: adult = %d\nages: kid = %d", ages.cntTotal, ages.cntAdults, ages.cntKids);


    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
