#include <stdio.h>
#include <math.h>

// Function to find the entrance and floor number for a given apartment number
void find(int inputApartmentNumber, int totalApartments, int entrance, int floor, int floorsPerEntrance, int *resultEntrance, int *resultFloor)
{
    // Calculate the number of flats per floor
    int flatsPerFloor = ceil((double) totalApartments / ((entrance - 1) * floorsPerEntrance + floor));

    // Calculate the entrance number
    *resultEntrance = (int)ceil((double)inputApartmentNumber / (flatsPerFloor * floorsPerEntrance));

    // Calculate the floor number within the entrance
    *resultFloor = (int)ceil((double)(inputApartmentNumber - (*resultEntrance - 1) * flatsPerFloor * floorsPerEntrance) / flatsPerFloor);

    // Adjust the entrance and floor if the floor calculation yields 0
    if (*resultFloor == 0)
    {
        *resultFloor = floorsPerEntrance;
        (*resultEntrance)--;
    }
}

int main(void)
{
    int N, M, P, K, L; // Variables to store input values

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d %d %d %d", &N, &M, &P, &K, &L); // Read inputs

    int result_entrance, result_floor; // Variables to store the result entrance and floor
    find(N, M, P, K, L, &result_entrance, &result_floor); // Call the function to find entrance and floor
    printf("%d %d\n", result_entrance, result_floor); // Output the results

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
