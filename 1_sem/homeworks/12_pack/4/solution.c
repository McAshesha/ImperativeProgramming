#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 10007

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

typedef struct Node
{
    ActorBioRecord data;
    struct Node* next;
} Node;

Node* hashTable[HASH_TABLE_SIZE] = {NULL};

unsigned int hashFunction(const char* name)
{
    unsigned int hash = 0;
    while (*name)
    {
        hash = (hash * 31) + *name;
        name++;
    }
    return hash % HASH_TABLE_SIZE;
}

void addToHashTable(const char* name, int birthYear, const char* country)
{
    unsigned int hash = hashFunction(name);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strncpy(newNode->data.Name, name, 30);
    newNode->data.BirthYear = birthYear;
    strncpy(newNode->data.Country, country, 10);
    newNode->next = hashTable[hash];
    hashTable[hash] = newNode;
}

Node** searchInHashTable(const char* name, int* resultCount)
{
    unsigned int hash = hashFunction(name);
    *resultCount = 0;

    Node* current = hashTable[hash];
    Node** resultArray = NULL;

    while (current != NULL)
    {
        if (strcmp(current->data.Name, name) == 0)
        {
            resultArray = realloc(resultArray, (*resultCount + 1) * sizeof(Node*));
            resultArray[*resultCount] = current;
            (*resultCount)++;
        }
        current = current->next;
    }

    return resultArray;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d\n", &N);

    ActorBioRecord* actorBioTable = (ActorBioRecord*)malloc(N * sizeof(ActorBioRecord));

    for (int i = 0; i < N; i++)
    {
        scanf("\"%[^\"]\" %d \"%[^\"]\"\n", actorBioTable[i].Name, &actorBioTable[i].BirthYear, actorBioTable[i].Country);
        addToHashTable(actorBioTable[i].Name, actorBioTable[i].BirthYear, actorBioTable[i].Country);
    }

    scanf("%d\n", &M);

    ActorInMovieRecord* actorInMovieTable = (ActorInMovieRecord*)malloc(M * sizeof(ActorInMovieRecord));

    for (int i = 0; i < M; i++)
    {
        scanf("\"%[^\"]\" \"%[^\"]\"\n", actorInMovieTable[i].ActorName, actorInMovieTable[i].MovieName);
    }

    for (int i = 0; i < M; i++)
    {
        int resultCount;
        Node** matches = searchInHashTable(actorInMovieTable[i].ActorName, &resultCount);

        for (int j = 0; j < resultCount; j++)
        {
            printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", matches[j]->data.Name, matches[j]->data.BirthYear,
                   matches[j]->data.Country, actorInMovieTable[i].ActorName, actorInMovieTable[i].MovieName);
        }

        free(matches);
    }

    free(actorBioTable);
    free(actorInMovieTable);

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        Node* current = hashTable[i];
        while (current != NULL)
        {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
