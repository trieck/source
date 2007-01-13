/*
 * TEMP.H
 *
 * Temporary symbols
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __TEMP_H__
#define __TEMP_H__

#include "symbol.h"

void tinit(void);
Symbol *tlookup(const char *s);
Symbol *tinstall(const char *s, int t, int sub, double d);
Symbol *tinstalls(const char *s, const char *v);

#endif							/* __TEMP_H__ */
