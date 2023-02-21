#include <stdio.h>

#define N 4

FILE *inputFile;
char buffer[2 * N];
int input = 0;
int fence = 0;

void fillBuffer(int start, int end)
{
    int i;
    char readChar;

    for (i = start; i < end; i++)
    {
        readChar = fgetc(inputFile);
        if (readChar == EOF)
        {
            buffer[i] = '\0';
            return;
        }
        else
            buffer[i] = readChar;
    }
}

void init(char *fileName)
{
    inputFile = fopen(fileName, "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file.");
        return;
    }
    fillBuffer(0, N);
}

char nextChar()
{
    if (input == -1)
        return 0;

    char c = buffer[input];

    if (c == '\0')
    {
        if (feof(inputFile))
        {
            input = -1;
            return 0;
        }
    }

    input = (input + 1) % (2 * N);

    if (input % N == 0)
    {
        fillBuffer(input, input + N);
        fence = (input + N) % (2 * N);
    }

    return c;
}

int main(int argc, char const *argv[])
{
    char currentChar, dispChar;
    char *filePath = "../test/program.txt";

    init(filePath);

    while (input != -1)
    {
        currentChar = nextChar();
        if (currentChar != '\0')
        {
            dispChar = currentChar == '\n' ? ' ' : currentChar;
            printf("Read char: %c ", dispChar);
            if (currentChar == ' ')
                puts("(space)");
            else if (currentChar == '\n')
                puts("(line break)");
            else
                puts("");
        }
    }

    fclose(inputFile);

    return 0;
}
