#include <stdio.h>

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		int P, Q;
		unsigned long long M;
		scanf("%d/%d xor %llx", &P, &Q, &M);

		double X = (double) P / Q;
		unsigned long long X_bits = *(unsigned long long *) &X;
		unsigned long long result = X_bits ^ M;
		printf("%.15g\n", *(double *) &result);
	}

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
