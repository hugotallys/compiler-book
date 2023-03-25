//
// Created by hgtll on 19/03/2023.
//

#ifndef UTILS_H
#define UTILS_H

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

// create a new stack
Stack *newStack(int capacity);

// push a new element to the stack
void push(Stack *stack, int element);

// pop the last element from the stack
int pop(Stack *stack);

// peek the last element from the stack
int peek(Stack *stack);

#endif // COMPILER_BOOK_UTILS_H
