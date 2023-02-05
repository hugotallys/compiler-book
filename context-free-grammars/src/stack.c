#include "stack.h"

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
