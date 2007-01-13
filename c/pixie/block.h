/*
 * BLOCK.H
 *
 * Block scope
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __BLOCK_H__
#define __BLOCK_H__

void blockinit(void);
void blockenter(void);
void blockleave(void);
Symbol *binstall(const char *s, int t, int sub, double val);
int islocal(const char *s);
Symbol *blookup(const char *s);

#endif							/* __BLOCK_H__ */
