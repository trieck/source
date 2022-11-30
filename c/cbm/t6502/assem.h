/*
 *	ASSEM.H : assembler
 *
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
#ifndef __ASSEM_H__
#define __ASSEM_H__

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
    EQUAL = '='
} TokenType;

typedef struct
{
    TokenType type;
    char value[MAXTOK];
} Token;

/***************************************************************************/
void assemble(void);
Token gettok(const char** ppin);
/***************************************************************************/

#endif  /* __ASSEM_H__ */
