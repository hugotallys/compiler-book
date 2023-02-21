#include <stdio.h>
#include "lex/lex.h"

int main(int argc, char const *argv[])
{
    char dispChar;
    char currentChar;

    FILE *inputFile = fopen("../test/program.txt", "r");

    init(inputFile);

    while (input != -1)
    {
        currentChar = nextChar(inputFile);
        if (currentChar != '\0')
        {
            dispChar = currentChar == '\n' ? ' ' : currentChar;
            printf("Read char: %c ", dispChar);
            if (currentChar == ' ')
                puts("(space)");
            else if (currentChar == '\n')
                puts("(line break)");
            else
                puts("");
        }
    }

    fclose(inputFile);

    return 0;
}
