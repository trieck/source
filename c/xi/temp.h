/*
 * TEMP.H
 *
 * Temporary symbols
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __TEMP_H__
#define __TEMP_H__

#include "symbol.h"

void tinit(void);
PSYMBOL tlookup(const char *s);
PSYMBOL tinstallf(const char *s, int type, double d);
PSYMBOL tinstall(const char *s, int type, const char *v);

#endif							/* __TEMP_H__ */
