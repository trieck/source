/*
 * GLOBAL.H
 *
 * Global definitions
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <string.h>

#ifdef __GNUC__
#include <unistd.h>
#define PLATFORM_S64(x) x##ll
/* ensure one byte packing under GCC */
#define PACK_ONE	__attribute__((aligned(1)))
#define FSEEK	fseek
#else				/* __GNU_C__ */
#define PACK_ONE
#define PLATFORM_S64(x) x##i64
#define FSEEK	_fseeki64

#define vsnprintf	_vsnprintf
#endif				/* __GNUC__ */

/*
 * lexical buffer size
 */
#define BSIZE 128

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
