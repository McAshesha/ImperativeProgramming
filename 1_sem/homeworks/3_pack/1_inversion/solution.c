#include <stdio.h>

int main(void)
{
	/* Redirect standard input to read from "input.txt" and output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	int array[100];

	// Read the number of elements
	scanf("%d", &N);

	// Read the array elements
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &array[i]);
	}

	// Outer loop to consider each element
	for (int i = 0; i < N - 1; i++)
	{
		int count = 0;

		// Inner loop to count elements smaller than array[i]
		for (int j = i + 1; j < N; j++)
		{
			if (array[i] > array[j])
			{
				count++;
			}
		}

		// Output the count for the current element
		printf("%d ", count);
	}

	// The last element always has a count of 0, since there are no elements after it
	printf("0\n");

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0; // Successful program termination
}
