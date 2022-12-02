
#include "token.h"
#include <ctype.h>
#include <string.h>
#include "petscii.h"

#define ISSTR(c)	(isalnum(c) || (c) == '_')

Token lookahead(const char* pin)
{
    const char* dummy = pin;

    return gettok(&dummy);
}

Token gettok(const char** ppin)
{
    Token tok;
    const char* pin = *ppin;

    memset(&tok, 0, sizeof(Token));

    for (;;) {
        switch (*pin) {
        case '\0':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
            }
            return tok;
        case BASE:
        case COMMA:
        case EQUAL:
        case GT:
        case LPAREN:
        case LT:
        case POUND:
        case RPAREN:
        case SEMI:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        case QUOTE:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            pin++;
            (*ppin)++;

            while (*pin && *pin++ != QUOTE) {
            }

            ascii2petscii(tok.value, *ppin, pin - *ppin - 1);

            *ppin = pin;
            tok.type = LITERAL;
            return tok;
        case PSEUDO:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        case ' ': /* white space */
        case '\t':
        case '\r':
        case '\n':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            (*ppin)++; /* eat white */
            break;
        case DOLLAR:
            if (isxdigit(*(pin + 1))) {
                pin++;
                (*ppin)++;
                while (isxdigit(*pin))
                    pin++;
                tok.type = NUM;
                continue;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        default: {
            if (ISSTR(*pin)) {
                while (ISSTR(*pin))
                    pin++;
                tok.type = STR;
                continue;
            }
            tok.type = UNDEF;
            tok.value[0] = *(*ppin)++;
            return tok;
        }
        }
        pin++;
    }
}
