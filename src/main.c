#include <stdio.h>

#include "lex/lex.h"
#include "parser/parser.h"

#define MAX_TOKENS 1024

int main(int argc, char *argv[])
{
    puts("### Compiler started. ###");

    if (argc != 2) {
        puts("> Please, specify a input file as a command line parameter: ./compiler <input file>");
        return -1;
    }

    int inputSize = 0;

    Token input[MAX_TOKENS];
    FILE *inputFile = fopen(argv[1], "r");

    init(inputFile);

    puts("### Lexical analysis started. ###");

    if (getTokenStream(inputFile, input, &inputSize)) {
        puts("> Token stream:");
        for (int i = 0; i < inputSize; i++) {
            printToken(input[i]);
        }
        puts("### Lexical analysis succeeded. ###");
    } else {
        puts("> Lexical analysis error! Invalid symbols found:");
        for (int i = 0; i < inputSize; i++) {
            if (input[i].type == TOKEN_ERROR) {
                printf("%s ", input[i].value);
            }
        }
        puts("\n### Lexical analysis failed. ###");
        return -1;
    }

    puts("### Syntax analysis started. ###\n");

    if (parse(input, inputSize)) {
        puts("\n### Syntax analysis succeeded. Symbol table generated. ###");
    } else {
        puts("### Syntax analysis failed. ###");
    }

    fclose(inputFile);

    return 0;
}
