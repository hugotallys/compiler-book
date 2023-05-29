//
// Created by hgtll on 02/04/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stable.h"

// create a new symbol table
SymbolTable *newSymbolTable(int capacity) {
    SymbolTable *symbolTable = (SymbolTable *) malloc(sizeof(SymbolTable));
    symbolTable->data = (Symbol *) malloc(capacity * sizeof(Symbol));
    symbolTable->size = 0;
    symbolTable->capacity = capacity;
    return symbolTable;
}

// insert a new element to the symbol table
void insertSymbol(SymbolTable *symbolTable, Symbol symbol) {
    if (symbolTable->size == symbolTable->capacity) {
        symbolTable->capacity *= 2;
        Symbol *temp = (Symbol *) realloc(symbolTable->data, symbolTable->capacity * sizeof(Symbol));
        if (temp == NULL) {
            puts("Error: could not allocate memory for symbol table.");
            exit(-1);
        }
        symbolTable->data = temp;
    }
    symbolTable->data[symbolTable->size++] = symbol;
}

// get an element from the symbol table by name and scope
Symbol *getSymbol(SymbolTable *symbolTable, char *name, int scope) {
    for (int i = symbolTable->size - 1; i >= 0; i--) {
        if (symbolTable->data[i].scope == scope && strcmp(symbolTable->data[i].idName, name) == 0) {
            return &symbolTable->data[i];
        }
    }
    return NULL;
}

// remove an element from the symbol table by name and scope
void removeSymbol(SymbolTable *symbolTable, char *name, int scope) {
    for (int i = symbolTable->size - 1; i >= 0; i--) {
        if (symbolTable->data[i].scope == scope && strcmp(symbolTable->data[i].idName, name) == 0) {
            symbolTable->data[i] = symbolTable->data[--symbolTable->size];
            return;
        }
    }
}

// prints the symbol table
void printSymbolTable(SymbolTable *symbolTable) {

    const char *hline = "----------------";
    const char *bighline = "---------------------------------------";

    printf("| %s Symbol Table %s |\n", bighline, bighline);
    printf("| %-16s | %-16s | %-16s | %-16s | %-16s |\n", "ID Name", "ID Type", "Type", "Value", "Scope");
    printf("| %-16s | %-16s | %-16s | %-16s | %-16s |\n", hline, hline, hline, hline, hline);

    for (int i = 0; i < symbolTable->size; i++) {

        Symbol symbol = symbolTable->data[i];

        const char *idTypeName = getTokenTypeString(symbol.entryType);
        const char *typeName = getTokenTypeString(symbol.evalType);

        printf("| %-16s | %-16s | %-16s |", symbol.idName, idTypeName, typeName);

        if (symbol.evalType == INTEGER) {
            printf(" %-16d | ", (int) symbol.value);
        } else if (symbol.evalType == REAL) {
            printf(" %-16.4f | ", symbol.value);
        } else {
            printf(" %-16s | ", "{}");
        }

        printf("%-16d |\n", symbol.scope);
    }
}