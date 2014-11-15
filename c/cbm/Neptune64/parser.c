/*
 * 	PARSER.C
 *
 * 	Parser routines
 *
 *	Neptune64 Commodore 64 Emulator
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 */
#include "common.h"
#include "parser.h"
/*
 * get the next token from the input string
 */
Token gettok(const char **ppin)
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
        case LPAREN:
        case RPAREN:
        case COMMA:
        case POUND:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = *pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        case ' ':		/* white space */
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
        default:
            if (isxdigit(*pin)) {
                while (isxdigit(*pin))
                    pin++;
                tok.type = NUM;
                continue;
            } else if (isalpha(*pin)) {
                while (isalpha(*pin))
                    pin++;
                tok.type = STR;
                continue;
            } else {
                tok.type = UNDEF;
                tok.value[0] = *(*ppin)++;
                return tok;
            }
        }
        pin++;
    }
}
