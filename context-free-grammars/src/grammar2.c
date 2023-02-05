#include <string.h>

#include "stack.h"

int main(int argc, char const *argv[]) {
    
    Stack* stack = createStack(MAXSIZE);
    push(stack, '$');

    char input[MAXSIZE];
    printf("Grammar G2 recognizer. Type a word.\n");
    scanf("%s", input);

    int accept = 1;
    luint p = 0;
    luint currentState = 1;

    while (p < strlen(input) && accept) {
        switch (currentState) {
            case 1:
                if (input[p] == 'a') {
                    currentState = 1;
                    push(stack, '#');
                } else if (input[p] == '^') {
                    currentState = 2;
                }
                else
                    accept = 0;
                break;
            case 2:
                if (input[p] == 'b') {
                    if (peek(stack) == '#') {
                        currentState = 2;
                        pop(stack);
                    } else if (peek(stack) == '$') {
                        currentState = 3;
                        pop(stack);
                    } else {
                        accept = 0;
                    }
                }
                else
                    accept = 0;
                break;
            case 3:
                if (input[p] == 'b')
                    currentState = 3;
                else
                    accept = 0;
                break;
            default:
                break;
        }
        p++;
    }

    if (currentState == 3 && accept) {
        printf("Accepted!\n");
    } else {
        printf("Not accepted!\n");
    }

    return 0;
}