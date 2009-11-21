/*
 *	SYMBOL.H
 *
 * 	Instruction Symbol Table
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
 *
 */
#ifndef __SYMBOL_H__
#define __SYMBOL_H__
/* symbol table entry */
typedef struct Symbol {
	char *name;
	const instr *instr;
	struct Symbol *next;
} Symbol;
typedef Symbol * PSYMBOL;
typedef PSYMBOL * SymbolTable;
SymbolTable symalloc(void);
void symfree(SymbolTable);
void syminit(SymbolTable);
PSYMBOL lookup(SymbolTable, const char *name);
PSYMBOL opinsert(SymbolTable, const char *name, const instr *instr);
#endif /* __SYMBOL_H__ */
