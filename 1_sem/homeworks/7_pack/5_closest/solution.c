#include <stdio.h>
#include <stdlib.h>

int binary_search(int *array, int size, int element)
{
	int left = 0, right = size - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (array[mid] == element)
		{
			return mid;
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
	return left;
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

	int Q;
	scanf("%d", &Q);

	for (int i = 0; i < Q; i++)
	{
		int Y;
		scanf("%d", &Y);

		int result = binary_search(A, N, Y);
		if (result > 0 && abs(A[result - 1] - Y) <= abs(A[result] - Y))
		{
			result -= 1;
		}
		else if (result < N - 1 && abs(A[result + 1] - Y) < abs(A[result] - Y))
		{
			result += 1;
		}

		int distance = abs(A[result] - Y);\
		printf("%d %d\n", result, distance);
	}

	free(A);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
