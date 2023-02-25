#include "lex.h"

int input;
int fence;
char buffer[2 * N];
char lexeme[MAX_LEN];

const char *keywords[] = {"program",
                          "begin",
                          "end",
                          "var",
                          "integer"};

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
    for (i = 0; i < KEYWORDS; i++)
    {
        if (strcmp(lexeme, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

Token createToken(TokenType type, char *lexeme, int lexSize)
{
    Token token;
    token.type = type;
    strncpy(token.value, lexeme, lexSize);
    token.value[lexSize] = '\0';
    return token;
}

int isLetter(char c)
{
    return (c >= 'a' && c <= 'z');
}

int isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

Token nextToken(FILE *file)
{
    char readChar;
    char lexeme[MAX_LEN];
    int lexSize = 0;

    do
    {
        readChar = nextChar(file);

        lexeme[lexSize++] = readChar;

        if (readChar != ' ' && readChar != '\n' && readChar != '\t')
        {
            if (readChar == ';')
                return createToken(SEMICOLON, lexeme, lexSize);
            else if (readChar == ',')
                return createToken(COMMA, lexeme, lexSize);
            else if (readChar == '(')
                return createToken(LPAR, lexeme, lexSize);
            else if (readChar == ')')
                return createToken(RPAR, lexeme, lexSize);
            else if (readChar == '{')
                return createToken(LBRA, lexeme, lexSize);
            else if (readChar == '}')
                return createToken(RBRA, lexeme, lexSize);
            else if (readChar == '*')
                return createToken(MULT, lexeme, lexSize);
            else if (readChar == '=')
                return createToken(RELOP, lexeme, lexSize);
            else if (readChar == 'U')
                return createToken(UNION, lexeme, lexSize);
            else if (readChar == 'I')
                return createToken(INTERSECTION, lexeme, lexSize);
            else if (readChar == '<')
            {
                readChar = nextChar(file);
                if (readChar == '=' || readChar == '>')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(RELOP, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(RELOP, lexeme, lexSize);
                }
            }
            else if (readChar == '/')
            {
                readChar = nextChar(file);
                if (readChar == '/')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(IDIVIDE, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(DIVIDE, lexeme, lexSize);
                }
            }
            else if (readChar == ':' || readChar == '>')
            {
                readChar = nextChar(file);
                if (readChar == '=')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(*lexeme == ':' ? ASSIGN : RELOP, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(*lexeme == ':' ? COLON : RELOP, lexeme, lexSize);
                }
            }
            else if (isLetter(readChar))
            {
                readChar = nextChar(file);
                while (isLetter(readChar) || isDigit(readChar))
                {
                    lexeme[lexSize++] = readChar;
                    readChar = nextChar(file);
                }
                rollBack();
                Token token = createToken(IDENTIFIER, lexeme, lexSize);
                if (isKeyword(token.value))
                    token.type = KEYWORD;
                return token;
            }
            else if (readChar == '0')
            {
                readChar = nextChar(file);
                if (readChar != '.')
                {
                    rollBack();
                    return createToken(INTEGER, lexeme, lexSize);
                }
                else
                {
                    do
                    {
                        lexeme[lexSize++] = readChar;
                        readChar = nextChar(file);
                    } while (isDigit(readChar));
                    rollBack();
                    return createToken(REAL, lexeme, lexSize);
                }
            }
            else if (isDigit(readChar))
            {
                int isReal = false;
                readChar = nextChar(file);
                while (isDigit(readChar) || readChar == '.')
                {
                    if (readChar == '.')
                        isReal = true;
                    lexeme[lexSize++] = readChar;
                    readChar = nextChar(file);
                }
                rollBack();
                return createToken(isReal ? REAL : INTEGER, lexeme, lexSize);
            }
            else if (readChar == '+' || readChar == '-')
            {
                readChar = nextChar(file);
                if (isDigit(readChar))
                {
                    lexeme[lexSize++] = readChar;
                    int isReal = false;
                    readChar = nextChar(file);
                    while (isDigit(readChar) || readChar == '.')
                    {
                        if (readChar == '.')
                            isReal = true;
                        lexeme[lexSize++] = readChar;
                        readChar = nextChar(file);
                    }
                    rollBack();
                    return createToken(isReal ? REAL : INTEGER, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(*lexeme == '+' ? PLUS : SUB, lexeme, lexSize);
                }
            }
            else
                return createToken(ERROR, lexeme, lexSize);
        }
        else
            lexSize = 0;

    } while (true);
}

int terminatedInput()
{
    return input == -1;
}
