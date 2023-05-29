#include <stdio.h>

#include "lex/lex.h"
#include "parser/parser.h"
#include "utils/stable.h"

#define MAX_TOKENS 1024

void populateSymbolTable(SymbolTable *symbolTable, Token *input, int inputSize) {
    
    // VAR rule
    for (int i = 0; i < inputSize; i++) {
        if (input[i].type == VAR) {
            int j = i + 1;
            while (input[j].type != KEYWORD) {
                j++;
            }
            char* varType = input[j].value;

            TokenType type;

            if (varType[0] == 'i') {
                type = INTEGER;
            } else if (varType[0] == 'r') {
                type = REAL;
            } else if (varType[5] == 'I') {
                type = BAG_INTEGER;
            } else if (varType[5] == 'R') {
                type = BAG_REAL;
            }

            j = i + 1;

            while (input[j].type != COLON) {
                if (input[j].type == IDENTIFIER) {
                    
                    Symbol symbol_var = {
                        .idName = input[j].value,
                        .entryType = VAR,
                        .evalType = type,
                        .value = 0.0,
                        .scope = 0
                    };
                    
                    insertSymbol(symbolTable, symbol_var);
                }
                j++;
            }
        }
    }

}

double expression(SymbolTable *symbolTable, Token *input, int inputSize, int index, int scope) {
    double result = 0.0;
    
    Token token = input[index];

    if (token.type == OPERATOR) {
        if (token.value[0] == '+') {
            result = expression(symbolTable, input, inputSize, index + 2, scope) + expression(symbolTable, input, inputSize, index + 4, scope);
        } else if (token.value[0] == '-') {
            result = expression(symbolTable, input, inputSize, index + 2, scope) - expression(symbolTable, input, inputSize, index + 4, scope);
        } else if (token.value[0] == '*') {
            result = expression(symbolTable, input, inputSize, index + 2, scope) * expression(symbolTable, input, inputSize, index + 4, scope);
        } else if (token.value[0] == '/') {
            result = expression(symbolTable, input, inputSize, index + 2, scope) / expression(symbolTable, input, inputSize, index + 4, scope);
        } 
    } else if (token.type == IDENTIFIER) {
        Symbol *symbol = getSymbol(symbolTable, token.value, scope);
        result = symbol->value;
    } else if (token.type == INTEGER || token.type == REAL) {
        result = atof(token.value);
    }
    return result;
}

int analyse(SymbolTable *symbolTable, Token *input, int inputSize) {
    int scope = -1;
    for (int i = 0; i < inputSize; i++) {
        if (input[i].type == BEGIN) {
            scope++;
        } else if (input[i].type == END) {
            scope--;
        } else if (input[i].type == ASSIGN) {
            // previous token form input:

            Token previous = input[i - 1];
            Token next = input[i + 1];

            Symbol *prev = getSymbol(symbolTable, previous.value, scope);

            /*puts("\n-- Assignment found (:=)");
            printf("previous: %s (%s)\n", prev->idName, getTokenTypeString(prev->evalType));
            printf("next: %s (%s)\n\n", next.value, getTokenTypeString(next.type));*/

            if (prev->evalType != next.type && next.type != OPERATOR) {
                printf(
                    "Semantic error: cannot assign NUMBER %s (%s) to VAR %s (%s)\n",
                    next.value, getTokenTypeString(next.type),
                    prev->idName, getTokenTypeString(prev->evalType)
                );
                return 0;
            }

            // perform assigment of value to variable
            if (next.type == INTEGER || next.type == REAL) {
                prev->value = atof(next.value);
            } else if (next.type == BAG_INTEGER || next.type == BAG_REAL) {
                continue;
            } else if (next.type == IDENTIFIER) {
                Symbol *nextSymbol = getSymbol(symbolTable, next.value, scope);
                prev->value = nextSymbol->value;
            } else if (next.type == OPERATOR) {
                prev->value = expression(symbolTable, input, inputSize, i + 1, scope);
            }

            puts("\n- Symbol table updated:\n");
            printSymbolTable(symbolTable);
        }
    }
    return 1;
}

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

    SymbolTable *symbolTable = newSymbolTable(100);

    if (parse(input, inputSize)) {
        populateSymbolTable(symbolTable, input, inputSize);
        printSymbolTable(symbolTable);
        puts("\n### Syntax analysis succeeded. Symbol table generated. ###");
    } else {
        puts("### Syntax analysis failed. ###");
    }

    puts("\n### Semantic analysis started. ###\n");

    if (analyse(symbolTable, input, inputSize)) {
        puts("\n### Semantic analysis succeeded. ###\n");
    } else {
        puts("\n### Semantic analysis failed. ###");
    }

    fclose(inputFile);

    return 0;
}
