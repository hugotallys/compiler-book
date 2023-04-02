#include "parser.h"
#include "../utils/stable.h"

// function to open production file and read it line by line
void readProductions(Production *productions) {
    FILE *file = fopen("../bnf/productions.txt", "r");

    if (file == NULL) {
        puts("> Error opening productions file.");
        exit(1);
    }

    char line[100];

    for (int i = 0; i < N_PRODUCTIONS; i++) {
        fgets(line, sizeof(line), file);
        char *ptr;
        char *token = strtok(line, " ");
        productions[i].left = strtol(token, &ptr, 10);
        token = strtok(NULL, " ");
        productions[i].rightSize = strtol(token, &ptr, 10);
    }

    fclose(file);
}

// function to open action table file and read it line by line
void readActionTable(TableEntry actionTable[N_STATES][TERMINAL_SIZE]) {
    FILE *file = fopen("../bnf/action_table.txt", "r");

    if (file == NULL) {
        puts("> Error opening action table file.");
        exit(1);
    }

    char line[100];

    for (int i = 0; i < N_STATES; i++) {
        for (int j = 0; j < TERMINAL_SIZE; j++) {
            fgets(line, sizeof(line), file);
            char *ptr;
            char *token = strtok(line, " ");
            actionTable[i][j].action = strtol(token, &ptr, 10);
            token = strtok(NULL, " ");
            actionTable[i][j].id = strtol(token, &ptr, 10);
        }
    }

    fclose(file);
}

// function to open action table file and read it line by line
void readGoToTable(int goTable[N_STATES][NON_TERMINAL_SIZE]) {
    FILE *file = fopen("../bnf/goto_table.txt", "r");

    if (file == NULL) {
        puts("> Error opening goto table file.");
        exit(1);
    }

    char line[100];

    for (int i = 0; i < N_STATES; i++) {
        for (int j = 0; j < NON_TERMINAL_SIZE; j++) {
            fgets(line, sizeof(line), file);
            char *ptr;
            char *token = strtok(line, " ");
            goTable[i][j] = strtol(token, &ptr, 10);;
        }
    }

    fclose(file);
}


int parse(Token *input, int inputSize) {

    Production productions[N_PRODUCTIONS];
    readProductions(productions);
    TableEntry actionTable[N_STATES][TERMINAL_SIZE];
    readActionTable(actionTable);
    int goTable[N_STATES][NON_TERMINAL_SIZE];
    readGoToTable(goTable);

    Token stop = {.type = STOP, .value = "STOP"};

    input[inputSize++] = stop;

    int head = 0;
    TokenType currTerminal = input[head].type;

    Stack *stack = newStack(100);

    push(stack, 0);

    SymbolTable *symbolTable = newSymbolTable(100);

     Symbol symbol_var_n = {
        .idName = "n",
        .idType = VAR,
        .type = INTEGER,
        .value = 0.0,
        .scope = 0
     };

    Symbol symbol_function_fact = {
        .idName = "fact",
        .idType = FUNCTION,
        .type = INTEGER,
        .value = 0.0,
        .scope = 0
    };

    insertSymbol(symbolTable, symbol_var_n);
    insertSymbol(symbolTable, symbol_function_fact);

    while (1) {
        int s = peek(stack);

        TableEntry entry = actionTable[s][currTerminal];

        if (entry.action == SHIFT) {
            push(stack, entry.id);
            currTerminal = input[++head].type;
        } else if (entry.action == REDUCE) {
            for (int i = 0; i < productions[entry.id - 1].rightSize; i++)
                pop(stack);
            s = peek(stack);
            push(stack, goTable[s][productions[entry.id - 1].left]);
        } else if (entry.action == ACCEPT) {
            printSymbolTable(symbolTable);
            return 1;
        } else {
            puts("> Syntax error at token:");

            for (int window = -3; window <= 4; window++) {
                if (head + window >= 0 && head + window < inputSize) {
                    if (window == 0)
                        printf(" >>>>");
                    else
                        printf(" ");
                    printf("%s", input[head + window].value);
                }
            }

            int expectedSize = 0;
            TokenType expected[TERMINAL_SIZE];

            for (int k = 0; k < TERMINAL_SIZE; k++) {
                if (actionTable[s][k].action != ERROR) {
                    expected[expectedSize++] = k;
                }
            }

            if (expectedSize == 1) {
                printf("... [ Expected a %s token ]\n", getTokenTypeString(expected[0]));
                currTerminal = expected[0];
                puts("> Ignoring error and continuing analysis.");
            } else if (expectedSize > 1) {
                printf("... [ Ambiguous statement. Expected one of the following tokens: ");
                for (int k = 0; k < expectedSize; k++) {
                    printf("%s", getTokenTypeString(expected[k]));
                    if (k < expectedSize - 1)
                        printf(", ");
                }
                printf(" ]\n");
                return 0;
            }
        }
    }
}