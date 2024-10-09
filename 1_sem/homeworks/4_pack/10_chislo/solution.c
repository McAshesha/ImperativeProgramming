#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *onesMale[] = { "", "odin", "dva", "tri", "chetyre", "pyat'", "shest'",
		"sem'", "vosem'", "devyat'" };
char *onesFemale[] = { "", "odna", "dve", "tri", "chetyre", "pyat'", "shest'",
		"sem'", "vosem'", "devyat'" };
char *teens[] = { "desyat'", "odinnadtsat'", "dvenadtsat'", "trinadtsat'",
		"chetyrnadtsat'", "pyatnadtsat'", "shestnadtsat'", "semnadtsat'",
		"vosemnadtsat'", "devyatnadtsat'" };
char *tens[] = { "", "desyat'", "dvadtsat'", "tridtsat'", "sorok",
		"pyat'desyat", "shest'desyat", "sem'desyat", "vosem'desyat",
		"devyanosto" };
char *hundreds[] = { "", "sto", "dvesti", "trista", "chetyresta", "pyat'sot",
		"shest'sot", "sem'sot", "vosem'sot", "devyat'sot" };
char *thousands[] = { "tysyach", "tysyacha", "tysyachi", "tysyachi", "tysyachi",
		"tysyach", "tysyach", "tysyach", "tysyach", "tysyach" };
char *millions[] = { "millionov", "million", "milliona", "milliona", "milliona",
		"millionov", "millionov", "millionov", "millionov", "millionov" };
char *billions[] = { "milliardov", "milliard", "milliarda", "milliarda",
		"milliarda", "milliardov", "milliardov", "milliardov", "milliardov",
		"milliardov" };

char *deleteExtraSpaces(char *str)
{
	int length = strlen(str);
	for (int i = 0; i < length - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i; j < length - 1; j++)
			{
				str[j] = str[j + 1];
			}
			length--;
			i--;
		}
	}
	str[length] = '\0';
	return str;
}

char *convert_to_words(int n, int maleWord)
{
	static char result[1000];
	if (n < 10)
	{
		strcpy(result, maleWord ? onesMale[n] : onesFemale[n]);
	}
	else if (n < 20)
	{
		strcpy(result, teens[n - 10]);
	}
	else if (n < 100)
	{
		sprintf(result, "%s %s", tens[n / 10],
				maleWord ? onesMale[n % 10] : onesFemale[n % 10]);
	}
	else if (n < 1000)
	{
		if ((n % 100) > 10 && (n % 100) < 20)
		{
			sprintf(result, "%s %s", hundreds[n / 100], teens[(n % 100) - 10]);
		} else
		{
			sprintf(result, "%s %s %s", hundreds[n / 100], tens[(n % 100) / 10],
					maleWord ? onesMale[n % 10] : onesFemale[n % 10]);
		}
	}
	return result;
}

char *num_to_words(int n)
{
	char *result = (char*) malloc(1000 * sizeof(char));
	char *word;

	if (n % 10 == 1 && n % 100 != 11)
	{
		word = "stroka";
	}
	else if (n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20))
	{
		word = "stroki";
	}
	else
	{
		word = "strok";
	}

	if (n < 1000)
	{
		sprintf(result, "%s %s", convert_to_words(n, 0), word);
	}
	else if (n < 1000000)
	{
		sprintf(result, "%s %s %s", convert_to_words(n / 1000, 0),
				((n / 1000) % 100) >= 10 && ((n / 1000) % 100) <= 20 ?
						thousands[0] : thousands[(n / 1000) % 10],
				num_to_words(n % 1000));
	}
	else if (n < 1000000000) {
		sprintf(result, "%s %s %s", convert_to_words(n / 1000000, 1),
				((n / 1000000) % 100) >= 10 && ((n / 1000000) % 100) <= 20 ?
						millions[0] : millions[(n / 1000000) % 10],
				num_to_words(n % 1000000));
	}
	else
	{
		sprintf(result, "%s %s %s", convert_to_words(n / 1000000000, 1),
				((n / 1000000000) % 100) >= 10
						&& ((n / 1000000000) % 100) <= 20 ?
						billions[0] : billions[(n / 1000000000) % 10],
				num_to_words(n % 1000000000));
	}
	return result;
}

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N, x;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &x);
		printf("%s\n", deleteExtraSpaces(num_to_words(x)));
	}

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}