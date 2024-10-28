#include <stdio.h>
#include <stdlib.h>

typedef struct Record_s
{
	char value[8];
	int key, pos;
} Record;

int compare(const void *a, const void *b)
{
	int x_key = ((Record *) a)->key - ((Record *) b)->key;
	int x_pos = ((Record *) a)->pos - ((Record *) b)->pos;
	return (x_key ? x_key : x_pos);
}

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N;
	scanf("%d", &N);
	Record *array = (Record *) malloc(N * sizeof(Record));

	for (int i = 0; i < N; i++)
	{
		Record record = {.pos = i};
		scanf("%d %s", &record.key, &record.value);
		array[i] = record;
	}

	qsort(array, N, sizeof(Record), compare);

	for (int i = 0; i < N; i++)
	{

		printf("%d %s\n", array[i].key, array[i].value);
	}

	free(array);

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
