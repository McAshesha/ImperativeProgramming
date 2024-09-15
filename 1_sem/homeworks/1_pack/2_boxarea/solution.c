#include <stdio.h>

int main(void)
{
    int x, y, z; // Variables to store the input numbers

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d %d", &x, &y, &z); // Read three integers from the user

    // Check for negative inputs and print corresponding error codes
    if (x < 0)
    {
        printf("-1\n");
        return 0;
    }
    if (y < 0)
    {
        printf("-2\n");
        return 0;
    }
    if (z < 0)
    {
        printf("-3\n");
        return 0;
    }

    // Calculate the areas of the sides of the cuboid
    int side_area_1 = x * y;
    int side_area_2 = x * z;
    int side_area_3 = y * z;

    // Calculate the surface area of the cuboid
    int result = 2 * (side_area_1 + side_area_2 + side_area_3);

    // Output the result
    printf("%d\n", result);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate that the program ended successfully
}
