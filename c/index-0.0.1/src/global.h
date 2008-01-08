/*
 * GLOBAL.H
 *
 * Global definitions
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>		/* load i/o routines */
#include <ctype.h>		/* load character test routines */
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

/*
 * lexical buffer size 
 */
#define BSIZE 128

/*
 * ensure one byte packing under GCC 
 */
#define PACK_ONE	__attribute__((aligned(1)))

/*
 * file open modes 
 */
enum {
	OM_READ_ONLY,
	OM_WRITE
};

/* Macros for min/max. */
#define    MIN(a,b)    (((a)<(b))?(a):(b))
#define    MAX(a,b)    (((a)>(b))?(a):(b))

/* utility functions */
extern void error(const char *fmt, ...);
uint64_t doublehash(const void *key, uint32_t len);
uint64_t prime(uint64_t i);

#endif				/* __GLOBAL_H__ */
