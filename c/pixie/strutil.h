/*
 * STRUTIL.H
 *
 * String Utility functions
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __STRUTIL_H__
#define __STRUTIL_H__

typedef long Handle;

typedef struct {
	Handle handle;				/* string handle */
} String;

String stringalloc(void);
unsigned stringlen(String s);
void stringfree(String s);
void stringpush(String s, char c);
void stringvpush(String s, const char *v);
const char *stringptr(String s);

#endif							/* __STRUTIL_H__ */
