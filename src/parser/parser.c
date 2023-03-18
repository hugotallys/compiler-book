//
// Created by hgtll on 15/03/2023.
//

#include <stdio.h>
#include <stdlib.h>

#define N_STATES 13
#define N_PRODUCTIONS 7

typedef enum {
    PLUS,
    MULT,
    LPAREN,
    RPAREN,
    ID,
    STOP,
    TERMINAL_SIZE
} Terminal;

typedef enum {
    S,
    E,
    T,
    F,
    NON_TERMINAL_SIZE
} NonTerminal;

typedef enum {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
} Action;

typedef struct {
    int id;
    Action action;
} TableEntry;

typedef struct {
    int rightSize;
    NonTerminal left;
} Production;

// strcut to stack of int
typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

// create a new stack
Stack *newStack(int capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->data = (int *) malloc(capacity * sizeof(int));
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

// push a new element to the stack
void push(Stack *stack, int element) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->data = (int *) realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[stack->size++] = element;
}

// pop the last element from the stack
int pop(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty");
        return -1;
    }
    return stack->data[--stack->size];
}

// peek the last element from the stack
int peek(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty");
        return -1;
    }
    return stack->data[stack->size - 1];
}

int main() {
    Production productions[N_PRODUCTIONS] = {{ .left = S, .rightSize = 1 },
                                             { .left = E, .rightSize = 3 },
                                             { .left = E, .rightSize = 1 },
                                             { .left = T, .rightSize = 3 },
                                             { .left = T, .rightSize = 1 },
                                             { .left = F, .rightSize = 3 },
                                             { .left = F, .rightSize = 1 }};

    TableEntry actionTable[N_STATES][TERMINAL_SIZE] = {{{ .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 5 },  { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 6 },  { .action = ERROR, .id = -1 }},
                                                       {{ .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ACCEPT, .id = -1 }},
                                                       {{ .action = SHIFT, .id = 7 },  { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 1 }},
                                                       {{ .action = REDUCE, .id = 3 }, { .action = SHIFT, .id = 8 },  { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 3 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 3 }},
                                                       {{ .action = REDUCE, .id = 5 }, { .action = REDUCE, .id = 5 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 5 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 5 }},
                                                       {{ .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 5 },  { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 6 },  { .action = ERROR, .id = -1 }},
                                                       {{ .action = REDUCE, .id = 7 }, { .action = REDUCE, .id = 7 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 7 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 7 }},
                                                       {{ .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 5 },  { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 6 },  { .action = ERROR, .id = -1 }},
                                                       {{ .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 5 },  { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 6 },  { .action = ERROR, .id = -1 }},
                                                       {{ .action = SHIFT, .id = 7 },  { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }, { .action = SHIFT, .id = 12 }, { .action = ERROR, .id = -1 }, { .action = ERROR, .id = -1 }},
                                                       {{ .action = REDUCE, .id = 2 }, { .action = SHIFT, .id = 8 },  { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 2 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 2 }},
                                                       {{ .action = REDUCE, .id = 4 }, { .action = REDUCE, .id = 4 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 4 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 4 }},
                                                       {{ .action = REDUCE, .id = 6 }, { .action = REDUCE, .id = 6 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 6 }, { .action = ERROR, .id = -1 }, { .action = REDUCE, .id = 6 }}};

    int goTable[N_STATES][NON_TERMINAL_SIZE] = {{ 1,  2,  3,  4 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 },
                                                { -1, 9,  3,  4 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, 10, 4 },
                                                { -1, -1, -1, 11 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 },
                                                { -1, -1, -1, -1 }};

    Terminal input[10] = { LPAREN, ID, MULT, ID, RPAREN, PLUS, ID, STOP };

    int head = 0;
    Terminal currTerminal = input[head];

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
