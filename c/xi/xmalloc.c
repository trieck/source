/*
 * XMALLOC.C
 *
 * Memory allocation routines
 *
 * 'X' Programming Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"
#include "x.h"

/* allocate memory block */
void *xmalloc(size_t size)
{
    void *pv = malloc(size);
    if (pv == 0) {
        error("unable to allocate memory block.");
    }

    return pv;
}

/* reallocate memory block */
void *xrealloc(void *old, size_t size)
{
    void *new = realloc(old, size);
    if (new == 0) {
        error("unable to reallocate memory block.");
    }

    return new;
}

/* free memory block */
void xfree(void *pv)
{
    if (pv != 0) {
        free(pv);
    }
}

/* like strdup, using xmalloc */
char *xstrdup(const char *s)
{
    char *t = xmalloc(strlen(s) + 1);
    strcpy(t, s);
    return t;
}
