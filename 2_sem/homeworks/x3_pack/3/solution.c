#pragma comment (linker , "/ STACK :50000000 ")
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define EXPRESSION_SIZE 500001

double parseExpr();
double parseMonome();
double parseAtom();

char str[EXPRESSION_SIZE];
int pos = 0;
char token[EXPRESSION_SIZE];

char* readToken()
{
    while (str[pos] == ' ')
    {
        pos++;
    }

    if (str[pos] == '\0')
    {
        token[0] = '\0';
        return token;
    }

    if (strchr("+-*/()", str[pos]) != 0)
    {
        token[0] = str[pos];
        token[1] = '\0';
        pos++;
        return token;
    }

    int left = pos;
    while (isdigit(str[pos]))
    {
        pos++;
    }
    int right = pos;
    int len = right - left;
    strncpy(token, &str[left], len);
    token[len] = '\0';
    return token;
}

char* peekToken()
{
    int oldPos = pos;
    readToken();
    pos = oldPos;
    return token;
}

double parseExpr()
{
    double value = parseMonome();
    while (strcmp(peekToken(), "+") == 0 || strcmp(peekToken(), "-") == 0)
    {
        char operation = readToken()[0];
        double nextMonome = parseMonome();
        if (operation == '+')
        {
            value += nextMonome;
        }
        else
        {
            value -= nextMonome;
        }
    }
    return value;
}

double parseMonome()
{
    double value = parseAtom();
    while (strcmp(peekToken(), "*") == 0 || strcmp(peekToken(), "/") == 0)
    {
        char operation = readToken()[0];
        double nextAtom = parseAtom();
        if (operation == '*')
        {
            value *= nextAtom;
        }
        else
        {
            value /= nextAtom;
        }
    }
    return value;
}

double parseAtom()
{
    double value;
    if (strcmp(peekToken(), "(") == 0)
    {
        readToken();
        value = parseExpr();
        readToken();
    }
    else if (strcmp(peekToken(), "-") == 0)
    {
        readToken();
        value = -parseMonome();
    }
    else
    {
        value = atoi(readToken());
    }
    return value;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    fgets(str, EXPRESSION_SIZE, stdin);

    printf("%.20f\n", parseExpr());

    return 0;
}
