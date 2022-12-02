#pragma once

#define MAXTOK 256

typedef enum
{
    UNDEF = 0,
    LITERAL,
    STR,
    NUM,
    LPAREN = '(',
    RPAREN = ')',
    COMMA = ',',
    POUND = '#',
    SEMI = ';',
    QUOTE = '\'',
    PSEUDO = '.',
    BASE = '*',
    EQUAL = '=',
    LT = '<',
    GT = '>',
    DOLLAR = '$'
} TokenType;

typedef struct
{
    TokenType type;
    char value[MAXTOK];
} Token;

/***************************************************************************/
Token gettok(const char** ppin);
Token lookahead(const char* pin);
/***************************************************************************/