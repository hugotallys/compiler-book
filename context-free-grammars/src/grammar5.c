#include <string.h>

#include "stack.h"

int main(int argc, char const *argv[]) {
    
    Stack* stack = createStack(MAXSIZE);
    push(stack, '$');

    char input[MAXSIZE];
    printf("Grammar G5 recognizer. Type a word.\n");
    scanf("%s", input);

    int accept = 1;
    luint p = 0;
    luint currentState = 1;

    while ((p < strlen(input)) && accept) {
        switch (currentState) {
            case 1:
                if (input[p] == '0') {
                    currentState = 1;
                    push(stack, '#');
                } else if (input[p] == '1' && peek(stack) == '#') {
                    currentState = 2;
                    pop(stack);
                    if (peek(stack) == '#') {
                        currentState = 3;
                        pop(stack);
                    } else
                        accept = 0;
                }
                else
                    accept = 0;
                break;
            case 3:
                if (input[p] == '1') {
                    if (peek(stack) == '#') {
                        currentState = 3;
                        pop(stack);
                    } else {
                        accept = 0;
                    }
                }
                else
                    accept = 0;

                if (peek(stack) == '$') {
                    currentState = 4;
                    pop(stack);
                }

                break;
            case 4:
                accept = 0;
            default:
                break;
        }
        p++;
    }

    if (currentState == 3 && peek(stack) == '$') {
        currentState = 4;
        pop(stack);
    }

    if (currentState == 4 && accept) {
        printf("Accepted!\n");
    } else {
        printf("Not accepted!\n");
    }

    return 0;
}