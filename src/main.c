#include <stdio.h>

#include "lex/lex.h"
#include "utils/utils.h"
#include "parser/parser.h"

int main()
{
    Token token;
    FILE *inputFile = fopen("../test/program.txt", "r");

    init(inputFile);

    int inputSize = 0;
    Token input[100];

    int lexError = 0;

    puts("### Lexical analysis started. ###\n> Token stream:");

    while (true)
    {
        token = nextToken(inputFile);
        if (*token.value != '\0') {
            input[inputSize++] = token;
            if (token.type == TOKEN_ERROR)
                lexError = 1;
        }
        else
            break;
    }

    fclose(inputFile);

    for (int i = 0; i < inputSize; i++) {
        printToken(input[i]);
    }

    if (lexError) {
        puts("> Lexical analysis error! Invalid symbols found:");

        for (int i = 0; i < inputSize; i++) {
            if (input[i].type == TOKEN_ERROR) {
                printf("%s ", input[i].value);
            }
        }

        puts("\n### Lexical analysis failed. ###");

        return -1;
    } else {
        puts("### Lexical analysis succeded. ###");
    }

    puts("### Syntactic analysis started. ###");

    Token stop = { .type = STOP, .value = "STOP" };

    input[inputSize++] = stop;

    int head = 0;
    TokenType currTerminal = input[head].type;

    Stack *stack = newStack(100);

    push(stack, 0);

    while (1) {
        int s = peek(stack);

        TableEntry entry = actionTable[s][currTerminal];

        if (entry.action == SHIFT) {
            push(stack, entry.id);
            currTerminal = input[++head].type;
        } else if (entry.action == REDUCE) {
            for (int i = 0; i < productions[entry.id - 1].rightSize; i++)
                pop(stack);
            s = peek(stack);
            push(stack, goTable[s][productions[entry.id - 1].left]);
        } else if (entry.action == ACCEPT) {
            puts("\n<Symbol table here>");
            puts("\n### Syntactic analysis succeded. Symbol table generated. ###");
            break;
        } else {
            puts("> Syntax error at token:");

            for (int window = -3; window <= 4; window++) {
                if (head + window >= 0 && head + window < inputSize) {
                    if (window == 0)
                        printf(" >>>>");
                    else
                        printf(" ");
                    printf("%s", input[head + window].value);
                }
            }

            int expectedSize = 0;
            TokenType expected[TERMINAL_SIZE];

            for (int k = 0; k < TERMINAL_SIZE; k++) {
                if (actionTable[s][k].action != ERROR) {
                    expected[expectedSize++] = k;
                }
            }

            if (expectedSize == 1) {
                printf("... [ Expected a %s token ]\n", getTokenTypeString(expected[0]));
                currTerminal = expected[0];
                puts("> Ignoring error and continuing analysis.");
            } else if (expectedSize > 1) {
                printf("... [ Ambiguous statement. Expected one of the following tokens: ");
                for (int k = 0; k < expectedSize; k++) {
                    printf("%s", getTokenTypeString(expected[k]));
                    if (k < expectedSize - 1)
                        printf(", ");
                }
                printf(" ]\n");
                puts("### Syntactic analysis failed. ###");
                break;
            }
        }
    }

    return 0;
}
