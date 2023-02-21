#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>

#define N 4096
#define MAX_LEN 64

typedef enum _token_type
{
    SEMICOLON,
    IDENTIFIER,
    KEYWORD
} TokenType;

typedef struct _token
{
    char value[MAX_LEN];
    TokenType type;
} Token;

void fillBuffer(FILE *file, int start, int end);

void init(FILE *file);

char nextChar(FILE *file);

int terminatedInput();

int rollBack();

Token nextToken(FILE *file);

#endif