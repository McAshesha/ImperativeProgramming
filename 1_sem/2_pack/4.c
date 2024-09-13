#include <stdio.h>
#include <math.h>

// Function to check if two rectangles (B and C) can fit inside a rectangle (A)
int canFit(int a_1, int a_2, int b_1, int b_2, int c_1, int c_2)
{
    // Check various configurations for fitting both rectangles B and C within A
    if ((b_1 + c_1 <= a_1 && b_2 <= a_2 && c_2 <= a_2) || // B and C horizontally fit inside A
        (b_2 + c_2 <= a_2 && b_1 <= a_1 && c_1 <= a_1))   // B and C vertically fit inside A
    {
        return 1; // They fit
    }

    if ((b_1 <= a_1 && c_1 <= a_1 && b_2 + c_2 <= a_2) || // Another configuration for B and C inside A
        (b_2 <= a_2 && c_2 <= a_2 && b_1 + c_1 <= a_1))   // Another configuration
    {
        return 1; // They fit
    }

    return 0; // They don't fit
}

int main(void)
{
    // Variables for dimensions of rectangles A, B, and C
    int a_1, a_2;
    int b_1, b_2;
    int c_1, c_2;

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Read dimensions of rectangle A
    scanf("%d %d", &a_1, &a_2);
    // Read dimensions of rectangle B
    scanf("%d %d", &b_1, &b_2);
    // Read dimensions of rectangle C
    scanf("%d %d", &c_1, &c_2);

    // Check if the total area of B and C exceeds the area of A
    if (b_1 * b_2 + c_1 * c_2 > a_1 * a_2)
    {
        printf("NO"); // If area exceeds, they cannot fit
        return 0;
    }

    // Check all possible rotations of rectangles B and C to fit inside A
    if (canFit(a_1, a_2, b_1, b_2, c_1, c_2) ||  // Both B and C in default orientation
        canFit(a_1, a_2, b_1, b_2, c_2, c_1) ||  // Rotate C by 90 degrees
        canFit(a_1, a_2, b_2, b_1, c_1, c_2) ||  // Rotate B by 90 degrees
        canFit(a_1, a_2, b_2, b_1, c_2, c_1))    // Rotate both B and C by 90 degrees
    {
        printf("YES"); // They fit
    }
    else
    {
        printf("NO"); // They don't fit
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
