//
// Created by hgtll on 02/04/2023.
//

#ifndef COMPILER_BOOK_STABLE_H
#define COMPILER_BOOK_STABLE_H

#include "../lex/lex.h"

typedef struct {
    char *idName;
    TokenType entryType;
    TokenType evalType;
    double value;
    int scope;
} Symbol;

typedef struct {
    Symbol *data;
    int size;
    int capacity;
} SymbolTable;

// create a new symbol table
SymbolTable *newSymbolTable(int capacity);

// insert a new element to the symbol table
void insertSymbol(SymbolTable *symbolTable, Symbol symbol);

// get an element from the symbol table by name and scope
Symbol *getSymbol(SymbolTable *symbolTable, char *name, int scope);

// remove an element from the symbol table by name and scope
void removeSymbol(SymbolTable *symbolTable, char *name, int scope);

// prints the symbol table
void printSymbolTable(SymbolTable *symbolTable);

char *entryTypeToString(TokenType entryType);

char *evalTypeToString(TokenType evalType);

#endif //COMPILER_BOOK_STABLE_H
