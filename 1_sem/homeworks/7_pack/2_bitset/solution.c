#include <stdio.h>
#include <stdlib.h>

#define bit(a, i) a.bit[i].bit

typedef union bitword_s
{
	unsigned char _;
	struct
	{
		unsigned bit:1;
	} bit[8];
} bitword;


void bitsetZero(bitword *arr , int num)
{
	for (int i = 0; i < num; i++)
	{
		bit(arr[i / 8], i % 8) = 0;
	}
}

int bitsetGet(const bitword *arr, int idx)
{
	return bit(arr[idx / 8], idx % 8);
}

void bitsetSet(bitword *arr, int idx, int newval)
{
	bit(arr[idx / 8], idx % 8) = newval;
}

int bitsetAny(const bitword *arr, int left, int right)
{
	for (int i = left; i < right; i++)
	{
		if (bit(arr[i / 8], i % 8))
		{
			return 1;
		}
	}
	return 0;
}

#define MAX_SIZE_ARRAY 20000000

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);

	bitword *arr = calloc((MAX_SIZE_ARRAY / 8), sizeof(bitword));

	for (int i = 0; i < N; i++)
	{
		int t, idx, num, newval, left, right;
		scanf("%d", &t);

		switch (t)
		{
			case 0:
				scanf("%d", &num);
				bitsetZero(arr, num);
				break;
			case 1:
				scanf("%d", &idx);
				printf("%d\n", bitsetGet(arr, idx));
				break;
			case 2:
				scanf("%d %d", &idx, &newval);
				bitsetSet(arr, idx, newval);
				break;
			case 3:
				scanf("%d %d", &left, &right);
				printf(bitsetAny(arr, left, right) ? "some\n" : "none\n");
				break;
		}
	}

	free(arr);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
