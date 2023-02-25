#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>

#define N 4096
#define MAX_LEN 64
#define true 1
#define false 0
#define KEYWORDS 5

typedef enum _token_type
{
    COLON,
    SEMICOLON,
    COMMA,
    LPAR,
    RPAR,
    LBRA,
    RBRA,
    ASSIGN,
    PLUS,
    SUB,
    MULT,
    DIVIDE,
    IDIVIDE,
    RELOP,
    UNION,
    INTERSECTION,
    INTEGER,
    REAL,
    IDENTIFIER,
    KEYWORD,
    ERROR
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

void printToken(Token token);

#endif