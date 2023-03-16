//
// Created by hgtll on 15/03/2023.
//

#include <stdio.h>

#define N_STATES 7
#define N_PRODUCTIONS 3

typedef enum {
    b, a, STOP, TERMINAL_SIZE
} Terminal;

typedef enum {
    S, B, NON_TERMINAL_SIZE
} NonTerminal;

typedef enum {
    shift, reduce, accept, error
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
Stack *newStack(int capacity)
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->data = (int *) malloc(capacity * sizeof(int));
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

// push a new element to the stack
void push(Stack *stack, int element)
{
    if (stack->size == stack->capacity)
    {
        stack->capacity *= 2;
        stack->data = (int *) realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[stack->size++] = element;
}

// pop the last element from the stack
int pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack is empty");
        return -1;
    }
    return stack->data[--stack->size];
}

// peek the last element from the stack
int peek(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack is empty");
        return -1;
    }
    return stack->data[stack->size - 1];
}

int main ()
{
    TableEntry actionTable[N_STATES][TERMINAL_SIZE] = {
            { { .action = shift, .id = 2 }, { .action = error }, { .action = error } },
            { { .action = error }, { .action = error }, { .action = accept } },
            { { .action = error }, { .action = shift, .id = 4 }, { .action = error } },
            { { .action = error }, { .action = shift, .id = 5 }, { .action = reduce, .id = 1 } },
            { { .action = error }, { .action = reduce, .id = 3 }, { .action = reduce, .id = 3 } },
            { { .action = error }, { .action = shift, .id = 6 }, { .action = error } },
            { { .action = error }, { .action = reduce, .id = 2 }, { .action = reduce, .id = 2 } }
    };

    int goTable[N_STATES][NON_TERMINAL_SIZE] = {
            {1, -1}, {-1, -1}, {-1, 3},
            {-1, -1}, {-1, -1}, {-1, -1},
            {-1, -1}
    };

    Production productions[N_PRODUCTIONS] = {
            { .left = S, .rightSize = 2 }, { .left = B, .rightSize = 3 }, { .left = B, .rightSize = 1 }
    };

    Terminal input[10] = { b , a , a, a, a, a, STOP};

    int head = 0;
    Terminal currTerminal = input[head];

    Stack *stack = newStack(100);

    push(stack, 0);

    while (1)
    {
        int s = peek(stack);

        TableEntry entry = actionTable[s][currTerminal];

        if ( entry.action == shift )
        {
            push(stack, entry.id);
            currTerminal = input[++head];
        }
        else if ( entry.action == reduce )
        {
            for (int i = 0; i < productions[entry.id-1].rightSize; i++ )
                pop(stack);

            s = peek(stack);

            push(stack, goTable[s][productions[entry.id-1].left]);
        }
        else if ( entry.action == accept )
        {
            puts("ACCEPTED! [PARSING IS DONE]");
            break;
        }
        else
        {
            puts("REJECTED! [SYNTAX ERROR]");
            break;
        }
    }

    return 0;
}
