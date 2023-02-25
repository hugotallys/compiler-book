#include <stdio.h>
#include "lex/lex.h"

const char *tokenTypeNames[] = {"COLON",
                                "SEMICOLON",
                                "COMMA",
                                "LPAR",
                                "RPAR",
                                "LBRA",
                                "RBRA",
                                "ASSIGN",
                                "PLUS",
                                "SUB",
                                "MULT",
                                "DIVIDE",
                                "IDIVIDE",
                                "RELOP",
                                "UNION",
                                "INTERSECTION",
                                "INTEGER",
                                "REAL",
                                "IDENTIFIER",
                                "KEYWORD",
                                "ERROR"};

void printToken(Token token)
{
    printf("%s\t%s\n", token.value, tokenTypeNames[token.type]);
}

int main(int argc, char const *argv[])
{
    Token token;
    FILE *inputFile = fopen("../test/program.txt", "r");

    init(inputFile);

    while (true)
    {
        token = nextToken(inputFile);
        if (*token.value != '\0')
            printToken(token);
        else
            break;
    }

    return 0;
}
