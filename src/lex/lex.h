#ifndef LEX_H
#define LEX_H

#include <stdio.h>

#define N 4096

extern int input;
extern int fence;
extern char buffer[2 * N];

void fillBuffer(FILE *file, int start, int end);

void init(FILE *file);

char nextChar(FILE *file);

#endif