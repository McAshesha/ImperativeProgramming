#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s
{
	int data;
	struct Node_s *next, *prev;
} Node;

Node *create_node(int data)
{
	Node *new = (Node *) malloc(sizeof(Node));
	new->data = data;
	new->next = new->prev = NULL;
	return new;
}

Node *delete_node(Node *current, int k)
{
	if (current->next == current)
	{
		printf("%d\n", current->data);
		free(current);
		return NULL;
	}

	for (int i = 0; i < k - 1; i++)
	{
		current = current->next;
	}

	Node *new = current->prev->next = current->next;
	current->next->prev = current->prev;

	printf("%d\n", current->data);
	free(current);

	return new;
}

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N, K;
	scanf("%d %d", &N, &K);

	Node *head = create_node(1);
	head->next = head->prev = head;

	Node *current = head;
	for (int i = 2; i <= N; i++, current = current->next) {
		current->next = create_node(i);
		current->next->prev = current;
		current->next->next = head;
	}
	head->prev = current;

	while (head)
	{
		head = delete_node(head, K);
	}

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}
