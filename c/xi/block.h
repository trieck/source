/*
 * BLOCK.H
 *
 * Block scope
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __BLOCK_H__
#define __BLOCK_H__

void blockinit(void);
void blockenter(void);
void blockleave(void);
PSYMBOL binstall(const char *s, int t, int sub, double val);
int islocal(const char *s);
PSYMBOL blookup(const char *s);

#endif							/* __BLOCK_H__ */
