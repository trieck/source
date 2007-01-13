/*
 * XMALLOC.H
 *
 * Memory allocation routines
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __XMALLOC_H__
#define __XMALLOC_H__

void *xmalloc(size_t size);
void *xrealloc(void *pv, size_t size);
void xfree(void *pv);

#endif							/* __XMALLOC_H__ */
