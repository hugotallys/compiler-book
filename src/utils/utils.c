//
// Created by hgtll on 19/03/2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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