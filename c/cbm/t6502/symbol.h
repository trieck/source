/*
 * 	SYMBOL.H : symbol table
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

#pragma once

#include "opcodes.h"

#define TBLSIZE 1103

typedef enum
{
    // undefined
    SYM_UNDEFINED,
    // machine opcode
    SYM_OPCODE,
    // identifier
    SYM_ID,
    // word value
    SYM_WORD,
    // byte value
    SYM_BYTE,
    // function
    SYM_FUNC
} SymType;

typedef word (*SymFnc)(void);

/* Symbol structure */
typedef struct Symbol
{
    char* name;
    SymType type;
    int sub_type;

    union
    {
        const Instr* instr;
        SymFnc fnc;
        word word_value;
        byte byte_value;
    } u;

    struct Symbol* next;
} Symbol;

typedef Symbol* PSYMBOL;
typedef PSYMBOL* SymbolTable;

/***************************************************************************/
SymbolTable symalloc(void);
void symfree(SymbolTable);
void syminit(SymbolTable);
PSYMBOL symlookup(SymbolTable, const char* name);
PSYMBOL idinsert(SymbolTable, const char* name, int sub_type);
PSYMBOL opinsert(SymbolTable, const char* name, const Instr* instr, int sub_type);
PSYMBOL wordinsert(SymbolTable, const char* name, word value);
PSYMBOL byteinsert(SymbolTable, const char* name, byte value);
PSYMBOL fncinsert(SymbolTable, const char* name, SymFnc fnc);
word symevalword(SymbolTable, const char* name);
/***************************************************************************/
