/*
 * GLOBAL.H
 *
 * Global definitions
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>				/* load i/o routines */
#include <ctype.h>				/* load character test routines */
#include <stdlib.h>
#include <stdint.h>

/* lexical buffer size */
#define BSIZE 128

/* ensure one byte packing under GCC */
#define PACK_ONE	__attribute__((aligned(1)))

/* file open modes */
enum {
	OM_READ_ONLY,
	OM_WRITE
};

extern void error(const char *fmt, ...);

#endif							/* __GLOBAL_H__ */
