#include <stdio.h>

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	char prev = ' ', curr = ' ', strCom = 0, caseCom = 0, start = 1;

	while (1)
	{
		if (scanf("%c", &curr) != 1)
		{
			if (!(strCom || caseCom))
			{
				printf("%c", prev);
			}
			else if (prev == '\n')
			{
				printf("%c", prev);
			}
			break;
		}

		if (start)
		{
			start = 0;
			prev = curr;
			continue;
		}

		if (prev == '/' && !(strCom || caseCom))
		{
			if (curr == '/')
			{
				strCom = 1;
				scanf("%c", &curr);
				prev = curr;
				continue;
			}
			if (curr == '*')
			{
				caseCom = 1;
				scanf("%c", &curr);
				prev = curr;
				continue;
			}
		}

		if (prev == '*' && curr == '/' && caseCom)
		{
			caseCom = 0;
			scanf("%c", &curr);
			prev = curr;
			continue;
		}

		if (prev == '\n')
		{
			strCom = strCom ? 0 : 1;
			printf("%c", prev);
		} else if (!(strCom || caseCom))
		{
			printf("%c", prev);
		}
		prev = curr;
	}

	return 0;
}