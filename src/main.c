#include <stdio.h>
#include "lex/lex.h"

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

    fclose(inputFile);

    return 0;
}
