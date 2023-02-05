#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef long unsigned int luint;

typedef struct stack
{
    luint size;
    char* stack;
} Stack;

char peek(Stack* s);

char pop(Stack* s);

void push(Stack* s, char c);

Stack* createStack(luint size);
