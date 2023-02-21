#include <stdio.h>
#include "lex/lex.h"

const char *tokenTypeNames[] = {"SEMICOLON", "IDENTIFIER", "KEYWORD"};

void printToken(Token token)
{
    printf("( %s , %s )\n", token.value, tokenTypeNames[token.type]);
}

int main(int argc, char const *argv[])
{

    FILE *inputFile = fopen("../test/program.txt", "r");

    init(inputFile);

    for (int i = 0; i < 5; i++)
    {
        Token token = nextToken(inputFile);
        if (token.type != -1)
            printToken(token);
    }

    return 0;
}
