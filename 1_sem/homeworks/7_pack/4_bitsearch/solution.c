#include <stdio.h>
#include <stdlib.h>

int binary_search(int *array, int size, int element)
{
	int left = 0, right = size - 1, result = -1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (array[mid] == element)
		{
			result = mid;
			left = mid + 1;
		}
		else if (array[mid] < element)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return result;
}

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);

	int *A = malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &A[i]);
	}

	int Q, R = 0;
	scanf("%d", &Q);

	for (int i = 0; i < Q; i++)
	{
		int X;
		scanf("%d", &X);
		R = binary_search(A, N, X + R);
		printf("%d\n", R);
	}

	free(A);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
