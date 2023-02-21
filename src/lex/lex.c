#include "lex.h"

int input;
int fence;
char buffer[2 * N];
char lexeme[MAX_LEN];

const char *keywords[] = {"program", "begin", "end"};

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
    input = fence = 0;
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

int rollBack()
{
    if (input == fence)
        return 0;
    input = (input - 1) % (2 * N);
    return 1;
}

int isKeyword(char *lexeme)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (strcmp(lexeme, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

Token nextToken(FILE *file)
{
    char readChar;
    char lexeme[MAX_LEN];
    int lexSize = 0;

    Token token;

    int state = 0;

    while (1)
    {
        readChar = nextChar(file);
        switch (state)
        {
        case 0:
            if (readChar == ';')
            {
                lexeme[lexSize++] = readChar;
                state = 1;
                lexeme[lexSize] = '\0';
                token.type = SEMICOLON;
                strcpy(token.value, lexeme);
            }
            else if ((readChar >= 'a' && readChar <= 'z') || (readChar >= 'A' && readChar <= 'Z'))
            {
                lexeme[lexSize++] = readChar;
                state = 2;
            }
            break;
        case 1:
            rollBack();
            return token;
        case 2:
            if ((readChar >= 'a' && readChar <= 'z') || (readChar >= 'A' && readChar <= 'Z') || (readChar >= '0' && readChar <= '9'))
            {
                lexeme[lexSize++] = readChar;
                state = 2;
            }
            else
            {
                state = 1;
                lexeme[lexSize] = '\0';

                if (isKeyword(lexeme))
                    token.type = KEYWORD;
                else
                    token.type = IDENTIFIER;

                strcpy(token.value, lexeme);
                rollBack();
            }
            break;
        default:
            lexeme[lexSize] = '\0';

            if (isKeyword(lexeme))
                token.type = KEYWORD;
            else
                token.type = IDENTIFIER;

            strcpy(token.value, lexeme);
            return token;
        }
    }

    return token;
}

int terminatedInput()
{
    return input == -1;
}
