#include <stdio.h>
#include <stdlib.h>

#define N_STATES 13
#define N_PRODUCTIONS 7

typedef enum
{
    PLUS,
    MULT,
    LPAREN,
    RPAREN,
    ID,
    STOP,
    TERMINAL_SIZE
} Terminal;

typedef enum
{
    S,
    E,
    T,
    F,
    NON_TERMINAL_SIZE
} NonTerminal;

Production productions[N_PRODUCTIONS] = {{.left = S, .rightSize = 1}, {.left = E, .rightSize = 3}, {.left = E, .rightSize = 1}, {.left = T, .rightSize = 3}, {.left = T, .rightSize = 1}, {.left = F, .rightSize = 3}, {.left = F, .rightSize = 1}};

TableEntry actionTable[N_STATES][TERMINAL_SIZE] = {{{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 5}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 6}, {.action = ERROR, .id = -1}}, {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ACCEPT, .id = -1}}, {{.action = SHIFT, .id = 7}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 1}}, {{.action = REDUCE, .id = 3}, {.action = SHIFT, .id = 8}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 3}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 3}}, {{.action = REDUCE, .id = 5}, {.action = REDUCE, .id = 5}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 5}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 5}}, {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 5}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 6}, {.action = ERROR, .id = -1}}, {{.action = REDUCE, .id = 7}, {.action = REDUCE, .id = 7}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 7}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 7}}, {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 5}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 6}, {.action = ERROR, .id = -1}}, {{.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 5}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 6}, {.action = ERROR, .id = -1}}, {{.action = SHIFT, .id = 7}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}, {.action = SHIFT, .id = 12}, {.action = ERROR, .id = -1}, {.action = ERROR, .id = -1}}, {{.action = REDUCE, .id = 2}, {.action = SHIFT, .id = 8}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 2}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 2}}, {{.action = REDUCE, .id = 4}, {.action = REDUCE, .id = 4}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 4}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 4}}, {{.action = REDUCE, .id = 6}, {.action = REDUCE, .id = 6}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 6}, {.action = ERROR, .id = -1}, {.action = REDUCE, .id = 6}}};

int goTable[N_STATES][NON_TERMINAL_SIZE] = {{1, 2, 3, 4}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, 9, 3, 4}, {-1, -1, -1, -1}, {-1, -1, 10, 4}, {-1, -1, -1, 11}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};