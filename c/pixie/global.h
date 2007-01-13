/*
 * GLOBAL.H
 *
 * Global symbols
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "symbol.h"

void globinit(void);
Symbol *glookup(const char *s);
Symbol *ginstall(const char *s, int t, int sub, double d);
Symbol *ginstalls(const char *s, const char *v);

#endif							/* __GLOBAL_H__ */
