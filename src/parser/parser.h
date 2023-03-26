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
#define TERMINAL_SIZE 27

typedef enum
{
    programa,
    corpo,
    declara,
    mais_dc,
    cont_dc,
    dvar,
    variaveis,
    mais_var,
    rotina,
    procedimento,
    funcao,
    parametros,
    lista_parametros,
    cont_lista_par,
    lista_id,
    cont_lista_id,
    sentencas,
    mais_sentencas,
    cont_sentencas,
    var_read,
    mais_var_read,
    var_write,
    mais_var_write,
    comando,
    chamada_procedimento,
    argumentos,
    lista_arg,
    cont_lista_arg,
    condicao,
    pfalsa,
    expressao,
    expressao_num,
    operando,
    termo,
    expressao_bag,
    conteudo,
    conteudo_integer_cont,
    conteudo_real_cont,
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

int parse(Token *tokens, int tokenCount);

#endif //COMPILER_BOOK_PARSER_H
