#include <stdio.h>
#include <stdlib.h>

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);
	unsigned long long *masks = malloc(N * sizeof(unsigned long long));

	for (int i = 0; i < N; i++)
	{
		scanf("%llx", &masks[i]);
	}

	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if ((masks[i] & masks[j]) == 0)
			{
				count ++;
			}
		}
	}

	printf("%d\n", count);
	free(masks);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
