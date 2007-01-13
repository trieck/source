/*
 * MEMCHECK.C
 *
 * Memory allocation checking
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifdef ALLOC_CHECK

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pixie.h"
#include "memcheck.h"
#include "xmalloc.h"

#define ALLOCED 1

typedef struct memcheck {
	void *pv;					/* allocated block */
	size_t size;				/* size of block */
	int flags;					/* allocation flags */
	struct memcheck *next;		/* link to next block */
} memcheck;

typedef struct pfclean {
	void (*pfn) (void);			/* cleanup function */
	struct pfclean *next;		/* link to next func */
} pfclean;

static memcheck *bhead;			/* block list head pointer */
static pfclean *chead;			/* cleanup list head pointer */

static void cleanup(void);

/* mcalloc:  memory allocation check */
void mcalloc(void *pv, unsigned size)
{
	memcheck *m;
	if (bhead == 0)
		atexit(cleanup);
	m = malloc(sizeof(memcheck));	/* can't use xmalloc */
	m->pv = pv;
	m->size = size;
	m->flags = ALLOCED;
	m->next = bhead;
	bhead = m;
}

/* mcfree:  memory free check */
void mcfree(void *pv)
{
	memcheck *link = bhead;
	while (link) {
		memcheck *next = link->next;
		if (link->pv == pv) {
			link->flags &= ~ALLOCED;
			break;
		}
		link = next;
	}

	if (link == 0)
		error("block 0x%x never allocated!", pv);
}

/* mcatexit:  register cleanup function */
void mcatexit(void (*pfn) (void))
{
	pfclean *c;
	c = xmalloc(sizeof(pfclean));
	c->pfn = pfn;
	c->next = chead;
	chead = c;
}

/* cleanup:  call registered funcs and perform localized cleanup */
void cleanup(void)
{
	memcheck *blink;
	pfclean *clink;
	unsigned leaks = 0;

	/* call registered cleanup funcs */
	clink = chead;
	while (clink) {
		pfclean *next = clink->next;
		(*clink->pfn) ();		/* call the cleanup function */
		xfree(clink);
		clink = next;
	}

	/* cleanup memblock list */
	blink = bhead;
	while (blink) {
		memcheck *next = blink->next;
		if (blink->flags & ALLOCED) {
			unsigned i, n;
			char *pb;

			n = min(40, blink->size);
			pb = (char *) blink->pv;

			dprint("\n**************************************************");
			dprint("\tmemory block 0x%p of size 0x%x never freed!",
				   blink->pv, blink->size);
			dprint("\tthe next %d bytes follow...", n);
			putc('\t', stderr);
			putc('[', stderr);
			for (i = 0; i < n; i++) {
				if (isprint(pb[i]))
					putc(pb[i], stderr);
				else
					putc('.', stderr);
			}
			putc(']', stderr);
			dprint("\n**************************************************");
			fflush(stderr);
			leaks++;
		}
		free(blink);			/* not allocated with xmalloc */
		blink = next;
	}

	dprint("%d memory leaks found.", leaks);

	bhead = 0;
	chead = 0;
}

#endif							/* ALLOC_CHECK */
