//
// Created by hgtll on 19/03/2023.
//

#ifndef PARSER_H
#define PARSER_H

#define N_STATES 24
#define N_PRODUCTIONS 11
#define TERMINAL_SIZE 9

typedef enum
{
    PROGRAMA,
    CORPO,
    DECLARA,
    MAIS_DC,
    CONT_DC,
    DVAR,
    VARIAVEIS,
    MAIS_VAR,
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

Production productions[N_PRODUCTIONS] = {{.left = PROGRAMA, .rightSize = 4},
                                         {.left = CORPO, .rightSize = 3},
                                         {.left = DECLARA, .rightSize = 3},
                                         {.left = DECLARA, .rightSize = 0},
                                         {.left = MAIS_DC, .rightSize = 2},
                                         {.left = CONT_DC, .rightSize = 3},
                                         {.left = CONT_DC, .rightSize = 0},
                                         {.left = DVAR, .rightSize = 3},
                                         {.left = VARIAVEIS, .rightSize = 2},
                                         {.left = MAIS_VAR, .rightSize = 2},
                                         {.left = MAIS_VAR, .rightSize = 0}};

TableEntry actionTable[N_STATES][TERMINAL_SIZE] = {{{.action = SHIFT, .id = 2},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ACCEPT, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = SHIFT, .id = 3},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 4},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = SHIFT, .id = 7},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = REDUCE, .id = 4}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = SHIFT, .id = 8},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = SHIFT, .id = 11}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 12}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 14}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 15},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 17}, {.action = REDUCE, .id = 11}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 2}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = REDUCE, .id = 3}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = SHIFT, .id = 19}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = REDUCE, .id = 7}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = SHIFT, .id = 20}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 9},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = SHIFT, .id = 11}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = REDUCE, .id = 5}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = SHIFT, .id = 11}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 8}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 10}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 14}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}},
                                                   {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1},  {.action = REDUCE, .id = 6}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}}};

int goTable[N_STATES][NON_TERMINAL_SIZE] = {{1,  -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, 5,  6,  -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, 9,  10, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, 13, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, 16},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, 18, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, 21, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, 22, 10, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, 23, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, -1}};

#endif //COMPILER_BOOK_PARSER_H
