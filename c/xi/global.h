/*
 * GLOBAL.H
 *
 * Global symbol table 
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "symbol.h"

void globinit(void);
PSYMBOL glookup(const char *s);
PSYMBOL ginstallf(const char *s, int type, int subtype, double d);
PSYMBOL ginstall(const char *s, int type, int subtype, const char *v);

#endif							/* __GLOBAL_H__ */
