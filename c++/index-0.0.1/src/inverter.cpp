/////////////////////////////////////////////////////////////////////////////
//
// INVERTER.CPP
//
// Inverted list of term locations in memory
// Copyright (c) 2008 Thomas A. Rieck
//

#include <limits.h>
#include "global.h"
#include "inverter.h"
#include "sort.h"

// maximum size of internal index in terms
#define MEMORY_SIZE		(48000000)

// initial record size
#define INITIAL_SIZE	(80)

// average record size
#define AVERAGE_SIZE	(50)

// empty vector docid
#define EMPTY           UINT_MAX

#define PLIST(record) 	(((uint32_t**)record)[-1])
#define PEND(record)  	(((uint32_t**)record)[-2])

#define FILL_RATIO		(2)

/////////////////////////////////////////////////////////////////////////////
Inverter::Inverter()
{
	size = prime(FILL_RATIO * maxcount);
	maxcount = MEMORY_SIZE / AVERAGE_SIZE;

    count = 0;
    maxpool = 2 * MEMORY_SIZE;

    record = new char*[size];
    memset(record, 0, size * sizeof(char*));

    ppool = pool = new char[3 * MEMORY_SIZE];
}
	
/////////////////////////////////////////////////////////////////////////////
Inverter::~Inverter()
{
	delete []record;
	delete []pool;
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::insert(const char *term, uint32_t docid)
{
	uint32_t i = lookup(term);
	
	if (record[i] == NULL) {
		alloc(i, term);
		*PLIST(record[i])++ = docid;
		count++;
		return;
	}
	
	if (docid > PLIST(record[i])[-1]) {
		if (PLIST(record[i]) >= PEND(record[i]) - 1)
			realloc(i);
		*PLIST(record[i])++ = docid;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::alloc(uint32_t i, const char *term)
{
	char *p = ppool + 2 * sizeof(uint32_t *);
	char *pterm = p;

	while (*pterm++ = *term++);

	ppool = pterm + INITIAL_SIZE;

	PLIST(p) = (uint32_t *) pterm;
	PEND(p) = (uint32_t *) ppool;

	record[i] = p;
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::realloc(uint32_t i)
{
	uint32_t p1 = 1 + (100 * (ppool-pool)) / maxpool;
	uint32_t p2 = 1 + (100 * count) / maxcount;

	uint32_t oldsize = (char *) PLIST(record[i]) - record[i];
	uint32_t newsize = (150 * oldsize) / MAX(p1, p2);

	char *p = ppool + 2 * sizeof(uint32_t *);
	ppool = p + newsize;

	memcpy(p, record[i], oldsize);

	PLIST(p) = (uint32_t *) (p + oldsize);
	PEND(p) = (uint32_t *) (p + newsize);

	record[i] = p;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Inverter::write(FILE *fp)
{
	compact();
    radixsort(record, 0, count - 1, 0);

    for (uint32_t i = 0; i < count; i++) {
        *PLIST(record[i])++ = EMPTY;

        uint32_t size = (char*)PLIST(record[i]) - record[i];
        
		if (fwrite(&size, sizeof(uint32_t), 1, fp) != 1)
			return 0;	// can't write

		if (fwrite(record[i], size, 1, fp) != 1)
			return 0;	// can't write
    }
    clear();

    return 1;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Inverter::lookup(const char *term)
{
	const char *p = term;

	uint32_t i = 0;

	while (*p)
		i = 127 * i + *p++;

	i = i % size;

	while (record[i] && strcmp(record[i], term))
		i = ++i % size;

	return i;	
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::clear()
{
    memset(record, 0, size * sizeof(char*));
    ppool = pool;
    count = 0;
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::compact()
{
    for (int i = 0, j = 0; i < size; i++) {
        if (record[i])
            continue;
        for ( ; j < size; j++)
            if (j > i && record[j])
                break;
        if (j >= size)
            break;
        record[i] = record[j];
        record[j] = NULL;
    }
}
