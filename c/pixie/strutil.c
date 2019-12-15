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

#define STRLEN 100  /* initial string length */

#define STRING2REP(h) ((StringRep*)(h))
#define REP2STRING(r) ((String)(r))

/* string representation */
typedef struct {
    char *str;      /* string data */
    unsigned len;   /* length of string */
    unsigned size;  /* allocated size */
} StringRep;

static String getstring(void);
static StringRep *allocrep(void);

/* allocate a string */
String stringalloc()
{
    String s = getstring();
    return s;
}

/* return length of string */
unsigned stringlen(String s)
{
    StringRep *rep = STRING2REP(s);
    return rep->len;
}

String getstring(void)
{
    StringRep *rep = allocrep();
    String s = REP2STRING(rep);
    return s;
}

/* allocate a string representation */
StringRep *allocrep(void)
{
    StringRep *rep = xmalloc(sizeof(StringRep));
    rep->str = (char *) xmalloc(STRLEN);
    rep->str[0] = '\0';
    rep->len = 0;
    rep->size = STRLEN;
    return rep;
}

/* free a string */
void stringfree(String s)
{
    StringRep *rep = STRING2REP(s);
    xfree(rep->str);
    xfree(rep);
}

/* return a C style string */
const char *stringptr(String s)
{
    StringRep *rep = STRING2REP(s);
    rep->str[rep->len] = '\0';
    return rep->str;
}

/* push a character onto a string */
void stringpush(String s, char c)
{
    StringRep *rep = STRING2REP(s);

    if (rep->len == rep->size - 1) {
        rep->str = (char *) xrealloc(rep->str, rep->size * 2);
        rep->size *= 2;
    }

    rep->str[rep->len++] = c;
}

/* push a char* onto a string */
void stringvpush(String s, const char *v)
{
    for (; *v; v++)
        stringpush(s, *v);
}
