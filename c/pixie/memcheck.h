/*
 * MEMCHECK.H
 *
 * Memory allocation checking
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __MEMCHECK_H__
#define __MEMCHECK_H__

#ifdef ALLOC_CHECK
void mcalloc(void *pv, unsigned size);
void mcfree(void *pv);
void mcatexit(void (*pfn) (void));
#else
#define mcalloc(x, y)	((void)0)
#define mcfree(x)		((void)0)
#define mcatexit(x)		(atexit(x))
#endif							/* ALLOC_CHECK */

#endif							/* __MEMCHECK_H__ */
