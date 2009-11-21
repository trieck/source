/*
 * SYMBOL.H
 *
 * Symbol table
 * Pixie language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

typedef Symbol **SymbolTable;

SymbolTable maketab(void);
void tabfree(SymbolTable table);
Symbol *lookup(SymbolTable table, const char *s);
Symbol *install(SymbolTable table, const char *s, int t, int sub,
                double d);
Symbol *installs(SymbolTable table, const char *s, const char *v);

#endif							/* __SYMBOL_H__ */
