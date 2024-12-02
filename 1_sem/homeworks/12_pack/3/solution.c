#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char Name[31];
    int BirthYear;
    char Country[11];
} ActorBioRecord;

typedef struct
{
    char ActorName[31];
    char MovieName[21];
} ActorInMovieRecord;

typedef struct
{
    char Name[31];
    int BirthYear;
    char Country[11];
    char MovieName[21];
} InnerJoinRecord;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d\n", &N);

    ActorBioRecord *actorBioTable = (ActorBioRecord*) malloc(N * sizeof(ActorBioRecord));

    for (int i = 0; i < N; i++)
    {
        scanf("\"%[^\"]\" %d \"%[^\"]\"\n", actorBioTable[i].Name,
                &actorBioTable[i].BirthYear, actorBioTable[i].Country);
    }

    scanf("%d\n", &M);

    ActorInMovieRecord *actorInMovieTable = (ActorInMovieRecord*) malloc(M * sizeof(ActorInMovieRecord));

    for (int i = 0; i < M; i++)
    {
        scanf("\"%[^\"]\" \"%[^\"]\"\n", actorInMovieTable[i].ActorName,
                actorInMovieTable[i].MovieName);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (strcmp(actorBioTable[i].Name, actorInMovieTable[j].ActorName) == 0)
                {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                        actorBioTable[i].Name, actorBioTable[i].BirthYear,
                        actorBioTable[i].Country, actorBioTable[i].Name,
                        actorInMovieTable[j].MovieName);
                }
        }
    }

    free(actorBioTable);
    free(actorInMovieTable);

    return 0;
}
