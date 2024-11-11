#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct
{
    uint32_t N;
    uint64_t A;
    uint64_t B;
} NAB;

typedef struct
{
    char name[21];
    uint64_t S;
    int8_t is_directory;
    uint64_t C;
    uint64_t M;
    int8_t is_hidden;
} File;
#pragma pack(pop)

File* filterFiles(File *files, NAB *nab, int *filteredCount)
{
    File *filteredFiles = (File*) malloc(nab->N * sizeof(File));
    *filteredCount = 0;
    for (int i = 0; i < nab->N; i++)
    {
        if (!files[i].is_directory && !files[i].is_hidden && files[i].C >= nab->A && files[i].M <= nab->B)
        {
            filteredFiles[*filteredCount] = files[i];
            (*filteredCount)++;
        }
    }
    return filteredFiles;
}

int compare(const void* a, const void* b)
{
    return strcmp(((File *) a)->name, ((File *) b)->name);
}

int main()
{
    FILE *in = fopen("binput.txt", "rb");
    FILE *out = fopen("boutput.txt", "wb");

    NAB nab;
    fread(&nab, sizeof(NAB), 1, in);

    File *files = (File*) malloc(nab.N * sizeof(File));
    fread(files, sizeof(File), nab.N, in);

    int filteredCount;
    File* filteredFiles = filterFiles(files, &nab, &filteredCount);
    qsort(filteredFiles, filteredCount, sizeof(File), compare);

    fwrite(filteredFiles, sizeof(File), filteredCount, out);

    free(files);
    free(filteredFiles);

    fclose(in);
    fclose(out);

    return 0;
}
