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

/* buffer size */
#define BSIZE 128

extern void error(const char *fmt, ...);

#endif							/* __GLOBAL_H__ */
