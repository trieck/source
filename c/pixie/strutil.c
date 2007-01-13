/*
 * STRUTIL.C
 *
 * String Utility functions
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <memory.h>
#include "strutil.h"
#include "xmalloc.h"

#define STRLEN 100				/* initial string length */

#define HANDLE2REP(h) ((StringRep*)(h))
#define REP2HANDLE(r) ((Handle)(r))

/* string representation */
typedef struct {
	char *v;					/* string data */
	unsigned n;					/* length of string */
	unsigned m;					/* allocated size */
} StringRep;

static Handle getstring(void);
static StringRep *allocrep(void);

/* allocate a string */
String stringalloc()
{
	String s;
	s.handle = getstring();
	return s;
}

/* return length of string */
unsigned stringlen(String s)
{
	StringRep *rep = HANDLE2REP(s.handle);
	return rep->n;
}

Handle getstring(void)
{
	StringRep *rep = allocrep();
	Handle handle = REP2HANDLE(rep);
	return handle;
}

/* allocate a string representation */
StringRep *allocrep(void)
{
	StringRep *rep = xmalloc(sizeof(StringRep));
	rep->v = (char *) xmalloc(STRLEN);
	rep->v[0] = '\0';
	rep->n = 0;
	rep->m = STRLEN;
	return rep;
}

/* free a string */
void stringfree(String s)
{
	StringRep *rep = HANDLE2REP(s.handle);
	xfree(rep->v);
	xfree(rep);
}

/* return a C style string */
const char *stringptr(String s)
{
	StringRep *rep = HANDLE2REP(s.handle);
	rep->v[rep->n] = '\0';
	return rep->v;
}

/* push a character onto a string */
void stringpush(String s, char c)
{
	StringRep *rep = HANDLE2REP(s.handle);

	if (rep->n == rep->m - 1) {
		rep->v = (char *) xrealloc(rep->v, rep->m * 2);
		rep->m = rep->m * 2;
	}

	rep->v[rep->n++] = c;
}

/* push a char* onto a string */
void stringvpush(String s, const char *v)
{
	for (; *v; v++)
		stringpush(s, *v);
}
