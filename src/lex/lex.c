#include "lex.h"

int input;
int fence;
char buffer[2 * N];

const char *keywords[] = {
    "program",
    "var",
    "integer",
    "real",
    "bagOfInteger",
    "bagOfReal",
    "read",
    "write",
    "for",
    "to",
    "do",
    "repeat",
    "until",
    "while",
    "if",
    "then",
    "else"
};

const char *tokenTypeNames[] = {
    "KEYWORD",
    "IDENTIFIER",
    "SEMICOLON",
    "COMMA",
    "COLON",
    "BEGIN",
    "END",
    "PROCEDURE",
    "FUNCTION",
    "LEFT_PARENTHESIS",
    "RIGHT_PARENTHESIS",
    "EMPTY",
    "STOP",
    "LEFT_BRACKET",
    "RIGHT_BRACKET",
    "ASSIGNMENT",
    "OPERATOR",
    "RELATION",
    "BAG_OPERATOR",
    "INTEGER",
    "REAL",
    "TOKEN_ERROR"
};

static inline int isLetter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

static inline int isDigit(char c) { return (c >= '0' && c <= '9'); }

void fillBuffer(FILE *file, int start, int end)
{
    int i;
    char readChar;

    for (i = start; i < end; i++)
    {
        readChar = (char) fgetc(file);
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
    for (i = 0; i < sizeof(keywords) / sizeof(char*); i++)
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

Token recognizeNumber(FILE* file, char readChar, char *lexeme, int lexSize)
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
                return createToken(LEFT_PARENTHESIS, lexeme, lexSize);
            else if (readChar == ')')
                return createToken(RIGHT_PARENTHESIS, lexeme, lexSize);
            else if (readChar == '{')
                return createToken(LEFT_BRACKET, lexeme, lexSize);
            else if (readChar == '}')
                return createToken(RIGHT_BRACKET, lexeme, lexSize);
            else if (readChar == '*')
                return createToken(OPERATOR, lexeme, lexSize);
            else if (readChar == '=')
                return createToken(RELATION, lexeme, lexSize);
            else if (readChar == '<')
            {
                readChar = nextChar(file);
                if (readChar == '=' || readChar == '>')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(RELATION, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(RELATION, lexeme, lexSize);
                }
            }
            else if (readChar == '/')
            {
                readChar = nextChar(file);
                if (readChar == '/')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(OPERATOR, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(OPERATOR, lexeme, lexSize);
                }
            }
            else if (readChar == ':' || readChar == '>')
            {
                readChar = nextChar(file);
                if (readChar == '=')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(*lexeme == ':' ? ASSIGNMENT : RELATION, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(*lexeme == ':' ? COLON : RELATION, lexeme, lexSize);
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
                if (strcmp(token.value, "Union") == 0)
                    token.type = BAG_OPERATOR;
                else if (strcmp(token.value, "Intersection") == 0)
                    token.type = BAG_OPERATOR;
                else if (strcmp((token.value), "Pos") == 0)
                    token.type = BAG_OPERATOR;
                else if (strcmp((token.value), "Element") == 0)
                    token.type = BAG_OPERATOR;
                else if (strcmp((token.value), "Quantity") == 0)
                    token.type = BAG_OPERATOR;
                else if (strcmp(token.value, "begin") == 0)
                    token.type = BEGIN;
                else if (strcmp(token.value, "end") == 0)
                    token.type = END;
                else if (strcmp(token.value, "procedure") == 0)
                    token.type = PROCEDURE;
                else if (strcmp(token.value, "function") == 0)
                    token.type = FUNCTION;
                else if (isKeyword(token.value))
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
                return recognizeNumber(file, readChar, lexeme, lexSize);
            }
            else if (readChar == '+' || readChar == '-')
            {
                readChar = nextChar(file);
                while (readChar == ' ' || readChar == '\n' || readChar == '\t') { readChar = nextChar(file); }
                if (isDigit(readChar))
                {
                    lexeme[lexSize++] = readChar;
                    return recognizeNumber(file, readChar, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(OPERATOR, lexeme, lexSize);
                }
            }
            else
                return createToken(TOKEN_ERROR, lexeme, lexSize);
        }
        else
            lexSize = 0;

    } while (true);
}

void printToken(Token token)
{
    printf("%-15s %s\n", token.value, tokenTypeNames[token.type]);
}
