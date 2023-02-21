#include "lex.h"

char buffer[2 * N];
int input = 0;
int fence = 0;

void fillBuffer(FILE *file, int start, int end)
{
    int i;
    char readChar;

    for (i = start; i < end; i++)
    {
        readChar = fgetc(file);
        if (readChar == EOF)
        {
            buffer[i] = '\0';
            return;
        }
        else
            buffer[i] = readChar;
    }
}

void init(FILE *file)
{

    if (file == NULL)
    {
        printf("Error opening input file.");
        return;
    }
    fillBuffer(file, 0, N);
}

char nextChar(FILE *file)
{
    if (input == -1)
        return 0;

    char c = buffer[input];

    if (c == '\0')
    {
        if (feof(file))
        {
            input = -1;
            return 0;
        }
    }

    input = (input + 1) % (2 * N);

    if (input % N == 0)
    {
        fillBuffer(file, input, input + N);
        fence = (input + N) % (2 * N);
    }

    return c;
}
