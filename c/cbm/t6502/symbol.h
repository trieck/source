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
#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#define TBLSIZE 1103
typedef enum {
    opcode,						/* machine opcode */
    kentry,						/* kernel jump table entry */
    lentry						/* label entry */
} Type;
/* Symbol structure */
typedef struct Symbol {
	char *name;
	Type type;
	union {
		const Instr *instr;
		word kjmp;
		word mem;
	} u;
	struct Symbol *next;
} Symbol;
typedef Symbol *PSYMBOL;
typedef PSYMBOL *SymbolTable;
/***************************************************************************/
SymbolTable symalloc(void);
void symfree(SymbolTable);
void syminit(SymbolTable);
PSYMBOL symlookup(SymbolTable, const char *name);
PSYMBOL opinsert(SymbolTable, const char *name, const Instr * instr);
PSYMBOL kinsert(SymbolTable, const char *name, const word kjmp);
PSYMBOL linsert(SymbolTable, const char *name, word pmem);
/***************************************************************************/
#endif							/* __SYMBOL_H__ */
