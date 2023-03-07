#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>

#define N 4096
#define MAX_LEN 64
#define true 1
#define false 0

typedef enum token_type_
{
    COLON,
    SEMICOLON,
    COMMA,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    ASSIGNMENT,
    OPERATOR,
    RELATION,
    BAG_OPERATOR,
    INTEGER,
    REAL,
    IDENTIFIER,
    KEYWORD,
    ERROR
} TokenType;

typedef struct token_
{
    char value[MAX_LEN];
    TokenType type;
} Token;

void fillBuffer(FILE *file, int start, int end);

void init(FILE *file);

char nextChar(FILE *file);

int rollBack();

Token nextToken(FILE *file);

void printToken(Token token);

#endif