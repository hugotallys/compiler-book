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
    TokenType input[100];

    while (true)
    {
        token = nextToken(inputFile);
        if (*token.value != '\0') {
            printToken(token);
            input[inputSize++] = token.type;
        }
        else
            break;
    }

    input[inputSize++] = STOP;

    puts("");

    fclose(inputFile);

    int head = 0;
    TokenType currTerminal = input[head];

    Stack *stack = newStack(100);

    push(stack, 0);

    while (1) {
        int s = peek(stack);

        TableEntry entry = actionTable[s][currTerminal];

        if (entry.action == SHIFT) {
            push(stack, entry.id);
            currTerminal = input[++head];
        } else if (entry.action == REDUCE) {

            for (int i = 0; i < productions[entry.id - 1].rightSize; i++)
                pop(stack);

            s = peek(stack);

            push(stack, goTable[s][productions[entry.id - 1].left]);
        } else if (entry.action == ACCEPT) {
            puts("ACCEPTED! [PARSING IS DONE]");
            break;
        } else {
            puts("REJECTED! [SYNTAX ERROR]");
            break;
        }
    }

    return 0;
}
