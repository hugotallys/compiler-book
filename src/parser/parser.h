//
// Created by hgtll on 19/03/2023.
//

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"
#include "../lex/lex.h"

#define N_STATES 198
#define N_PRODUCTIONS 75
#define TERMINAL_SIZE 28
#define NON_TERMINAL_SIZE 38

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
    int left;
    int rightSize;
} Production;

int parse(Token *tokens, int tokenCount);

#endif //COMPILER_BOOK_PARSER_H
