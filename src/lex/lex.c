#include "lex.h"

int input;
int fence;
char buffer[2 * N];

const char *keywords[] = {
    "program",
    "begin",
    "end",
    "var",
    "integer",
    "real",
    "bagOfInteger",
    "bagOfReal",
    "procedure",
    "function",
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
    "COLON",
    "SEMICOLON",
    "COMMA",
    "L_PARENTHESIS",
    "R_PARENTHESIS",
    "L_BRACKET",
    "R_BRACKET",
    "ASSIGN",
    "SUM_OP",
    "SUB_OP",
    "MUL_OP",
    "DIV_OP",
    "IDIV_OP",
    "REL_OP",
    "BAG_UNION",
    "BAG_INTERSECTION",
    "BAG_POS",
    "BAG_ELEMENT",
    "BAG_QUANTITY",
    "INTEGER",
    "REAL",
    "IDENTIFIER",
    "KEYWORD",
    "ERROR"
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
                return createToken(L_PARENTHESIS, lexeme, lexSize);
            else if (readChar == ')')
                return createToken(R_PARENTHESIS, lexeme, lexSize);
            else if (readChar == '{')
                return createToken(L_BRACKET, lexeme, lexSize);
            else if (readChar == '}')
                return createToken(R_BRACKET, lexeme, lexSize);
            else if (readChar == '*')
                return createToken(MUL_OP, lexeme, lexSize);
            else if (readChar == '=')
                return createToken(REL_OP, lexeme, lexSize);
            else if (readChar == '<')
            {
                readChar = nextChar(file);
                if (readChar == '=' || readChar == '>')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(REL_OP, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(REL_OP, lexeme, lexSize);
                }
            }
            else if (readChar == '/')
            {
                readChar = nextChar(file);
                if (readChar == '/')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(IDIV_OP, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(DIV_OP, lexeme, lexSize);
                }
            }
            else if (readChar == ':' || readChar == '>')
            {
                readChar = nextChar(file);
                if (readChar == '=')
                {
                    lexeme[lexSize++] = readChar;
                    return createToken(*lexeme == ':' ? ASSIGN : REL_OP, lexeme, lexSize);
                }
                else
                {
                    rollBack();
                    return createToken(*lexeme == ':' ? COLON : REL_OP, lexeme, lexSize);
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
                    token.type = BAG_UNION;
                else if (strcmp(token.value, "Intersection") == 0)
                    token.type = BAG_INTERSECTION;
                else if (strcmp((token.value), "Pos") == 0)
                    token.type = BAG_POS;
                else if (strcmp((token.value), "Element") == 0)
                    token.type = BAG_ELEMENT;
                else if (strcmp((token.value), "Quantity") == 0)
                    token.type = BAG_QUANTITY;
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
                    return createToken(*lexeme == '+' ? SUM_OP : SUB_OP, lexeme, lexSize);
                }
            }
            else
                return createToken(ERROR, lexeme, lexSize);
        }
        else
            lexSize = 0;

    } while (true);
}

void printToken(Token token)
{
    printf("%-15s %s\n", token.value, tokenTypeNames[token.type]);
}
