#include <stdio.h>

int main(void)
{

	/* Redirect standard input to read from "input.txt" and output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int L, R, K;

	// Read values for L, R, and K from the input
	scanf("%d %d %d", &L, &R, &K);

	int count = 0;

	for (int i = L; i <= R - K + 1; i ++)
	{
		for (int j = (R - i) / K; j <= (R - i) / (K - 1); j ++)
		{
			if (i + j * K > R)
			{
				count ++;
			}
		}
	}

	// Output the count of valid sequences
	printf("%d", count);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0; // Indicate successful program termination
}

