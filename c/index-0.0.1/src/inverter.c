/*
 * INVERTER.C
 *
 * Inverted list of term locations in memory
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include <limits.h>
#include "global.h"
#include "inverter.h"
#include "sort.h"

/* maximum size of internal index in terms */
#define MEMORY_SIZE		(2000000)

/* initial record size */
#define INITIAL_SIZE	(80)

/* average record size */
#define AVERAGE_SIZE	(50)

/* maximum number of terms allowed */
#define MAX_COUNT 		(MEMORY_SIZE / AVERAGE_SIZE)

/* fraction of table to fill */
#define FILL_RATIO 		(2)

/* empty vector docid */
#define EMPTY           UINT_MAX

#define PLIST(record) (((uint32_t**)record)[-1])
#define PEND(record)  (((uint32_t**)record)[-2])

static uint32_t inverter_lookup(Inverter_t * v, const char *term);
static void inverter_alloc(Inverter_t * v);
static void alloc(Inverter_t * v, uint32_t i, const char *term);
static void inverter_realloc(Inverter_t * v, uint32_t i);
static void inverter_clear(Inverter_t * v);
static void inverter_compact(Inverter_t * v);

/* create inverter instance */
Inverter_t *inverter_create(void)
{
    Inverter_t *v = (Inverter_t *) malloc(sizeof(Inverter_t));
    memset(v, 0, sizeof(Inverter_t));
    return v;
}

/* free inverter */
void inverter_free(Inverter_t * v)
{
    if (v->pool != NULL) {
        free(v->pool);
        v->pool = NULL;
    }

    if (v->record != NULL) {
        free(v->record);
        v->record = NULL;
    }

    free(v);
}

/* allocate memory for inverter */
void inverter_alloc(Inverter_t * v)
{
    v->size = (uint32_t) prime(FILL_RATIO * MAX_COUNT);
    v->maxpool = 2 * MEMORY_SIZE;
    v->count = 0;
    v->record = (char **) malloc(v->size * sizeof(char *));

    memset(v->record, 0, v->size * sizeof(char *));
    v->ppool = v->pool = (char *) malloc(3 * MEMORY_SIZE);
}

/* lookup bucket for term */
uint32_t inverter_lookup(Inverter_t * v, const char *term)
{
    const char *p = term;

    uint32_t i = 0;

    while (*p)
        i = 127 * i + *p++;

    i = i % v->size;

    while (v->record[i] && strcmp(v->record[i], term))
        i = ++i % v->size;

    return i;
}

/* insert term/docid pair into inverter */
void inverter_insert(Inverter_t * v, const char *term, uint32_t docid)
{
    uint32_t i;

    if (v->record == NULL)
        inverter_alloc(v);

    i = inverter_lookup(v, term);

    if (v->record[i] == NULL) {
        alloc(v, i, term);
        *PLIST(v->record[i])++ = docid;
        v->count++;
        return;
    }

    if (docid > PLIST(v->record[i])[-1]) {
        if (PLIST(v->record[i]) >= PEND(v->record[i]) - 1)
            inverter_realloc(v, i);

        *PLIST(v->record[i])++ = docid;
    }
}

void alloc(Inverter_t * v, uint32_t i, const char *term)
{
    char *p = v->ppool + 2 * sizeof(uint32_t *);
    char *pterm = p;

    while (*pterm++ = *term++);

    v->ppool = pterm + INITIAL_SIZE;

    PLIST(p) = (uint32_t *) pterm;
    PEND(p) = (uint32_t *) v->ppool;

    v->record[i] = p;
}

void inverter_realloc(Inverter_t * v, uint32_t i)
{
    uint32_t p1 = 1 + (100 * (v->ppool - v->pool)) / v->maxpool;
    uint32_t p2 = 1 + (100 * v->count) / MAX_COUNT;

    uint32_t oldsize = (char *) PLIST(v->record[i]) - v->record[i];
    uint32_t newsize = (150 * oldsize) / MAX(p1, p2);

    char *p = v->ppool + 2 * sizeof(uint32_t *);
    v->ppool = p + newsize;

    memcpy(p, v->record[i], oldsize);

    PLIST(p) = (uint32_t *) (p + oldsize);
    PEND(p) = (uint32_t *) (p + newsize);

    v->record[i] = p;
}

void inverter_clear(Inverter_t * v)
{
    memset(v->record, 0, v->size * sizeof(char *));
    v->ppool = v->pool;
    v->count = 0;
}

void inverter_compact(Inverter_t * v)
{
    uint32_t i, j;

    for (i = 0, j = 0; i < v->size; i++) {
        if (v->record[i])
            continue;

        for (; j < v->size; j++)
            if (j > i && v->record[j])
                break;

        if (j >= v->size)
            break;

        v->record[i] = v->record[j];
        v->record[j] = NULL;
    }
}

int inverter_write(Inverter_t * v, FILE * fp)
{
    uint32_t i, size;

    inverter_compact(v);
    radixsort(v->record, 0, v->count - 1, 0);

    for (i = 0; i < v->count; i++) {
        *PLIST(v->record[i])++ = EMPTY;
        size = (char *) PLIST(v->record[i]) - v->record[i];
        if (fwrite(&size, sizeof(uint32_t), 1, fp) != 1)
            return 0;	/* can't write */

        if (fwrite(v->record[i], size, 1, fp) != 1)
            return 0;	/* can't write */
    }

    inverter_clear(v);

    return 1;
}

int inverter_isfull(Inverter_t * v)
{
    return (v->count > MAX_COUNT
            || v->ppool - v->pool > (int) v->maxpool);
}
