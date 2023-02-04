#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef long unsigned int luint;

typedef struct stack
{
    luint size;
    char* stack;
} Stack;

char peek(Stack* s) {
    if (s->size) {
        return s->stack[s->size-1];
    }
    printf("Stack is empty!\n");
    return '\0';
}

char pop(Stack* s) {
    char top = peek(s);
    s->size--;
    return top;
}

void push(Stack* s, char c) {
    s->stack[s->size++] = c;
}

Stack* createStack(luint size) {
    Stack* s = malloc(sizeof(Stack));
    s->size = 0;
    s->stack = malloc(s->size * sizeof(char));
    return s;
}

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
                    currentState = 3;
                    pop(stack);
                    pop(stack);
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
                break;
            default:
                break;
        }
        p++;
    }

    if(peek(stack) == '$') {
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