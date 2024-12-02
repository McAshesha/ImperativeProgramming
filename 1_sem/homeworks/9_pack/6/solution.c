#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint32_t key;
    uint32_t value;
} Element;

// Radix Sort function
void radix_sort(Element *array, uint32_t N)
{
    Element *aux = (Element *)malloc(N * sizeof(Element));

    Element *input = array;
    Element *output = aux;

    uint32_t count[256];

    for (int byte = 0; byte < 4; byte++)
    {
        // Initialize count array
        for (int i = 0; i < 256; i++)
        {
            count[i] = 0;
        }

        // Count occurrences
        for (int i = 0; i < N; i++)
        {
            uint8_t key_byte = (input[i].key >> (8 * byte)) & 0xFF;
            count[key_byte]++;
        }

        // Compute cumulative counts
        for (int i = 1; i < 256; i++)
        {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = N; i > 0; i--)
        {
            uint8_t key_byte = (input[i - 1].key >> (8 * byte)) & 0xFF;
            output[--count[key_byte]] = input[i - 1];
        }

        // Swap input and output for next pass
        Element *temp = input;
        input = output;
        output = temp;
    }

    // If the sorted data is not in the original array, copy it back
    if (input != array)
    {
        for (int i = 0; i < N; i++)
        {
            array[i] = input[i];
        }
    }

    free(aux);
}

int main() {
    FILE *fin = fopen("input.txt", "rb");
    FILE *fout = fopen("output.txt", "wb");

    uint32_t N;
    fread(&N, sizeof(uint32_t), 1, fin);

    Element *array = (Element *)malloc(N * sizeof(Element));

    // Read N elements
    for (int i = 0; i < N; i++)
    {
        fread(&array[i].key, sizeof(uint32_t), 1, fin);
        fread(&array[i].value, sizeof(uint32_t), 1, fin);
    }

    radix_sort(array, N);

    for (int i = 0; i < N; i++)
    {
        fwrite(&array[i].key, sizeof(int32_t), 1, fout);
        fwrite(&array[i].value, sizeof(int32_t), 1, fout);
    }

    free(array);

    fclose(fout);
    fclose(fin); // Done with input file

    return 0;
}
