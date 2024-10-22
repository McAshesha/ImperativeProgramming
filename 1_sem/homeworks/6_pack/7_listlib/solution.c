#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s
{
	struct Node_s *prev, *next;
	void *value;
} Node;

typedef Node List;

void initList(List *list)
{
	list->prev = list->next = list;
	list->value = NULL;
}

Node* addAfter(Node *node, void *ptr)
{
	Node *newNode = malloc(sizeof(Node));
	newNode->value = ptr;
	newNode->next = node->next;
	newNode->prev = node;

	node->next->prev = newNode;
	node->next = newNode;
	return newNode;
}

Node* addBefore(Node *node, void *ptr)
{
	Node *newNode = malloc(sizeof(Node));
	newNode->value = ptr;
	newNode->next = node;
	newNode->prev = node->prev;

	node->prev->next = newNode;
	node->prev = newNode;
	return newNode;
}

void* erase(Node *node)
{
	void *value = node->value;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
	return value;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++)
	{
		int Q;
		scanf("%d", &Q);

		List list;
		initList(&list);

		Node **nodes = (Node**) malloc((Q + 1) * sizeof(Node *));
		nodes[0] = &list;
		int idx = 1;

		for (int i = 0; i < Q; i++)
		{
			int op, nodeIdx;
			scanf("%d %d", &op, &nodeIdx);
			nodeIdx++;

			if (op == 1)
			{
				int *value = malloc(sizeof(int));
				scanf("%d", value);
				nodes[idx++] = addAfter(nodes[nodeIdx], value);
			}
			else if (op == -1)
			{
				int *value = malloc(sizeof(int));
				scanf("%d", value);
				nodes[idx++] = addBefore(nodes[nodeIdx], value);
			}
			else
			{
				Node *node = nodes[nodeIdx];
				int *value = (int*) erase(node);
				free(value);
			}
		}

		for (Node *node = list.next; node != &list; node = node->next)
		{
			printf("%d\n", *((int*) node->value));
		}
		printf("===\n");

		for (Node *node = list.next; node != &list; )
		{
		    Node *next = node->next;
		    free(node->value);
		    free(node);
		    node = next;
		}

		free(nodes);
	}

	return 0;
}
