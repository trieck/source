/////////////////////////////////////////////////////////////////////////////
//
// GLOBAL.CPP : Global definitions
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"

extern int vsnprintf(char *, size_t n, char const *, va_list);

/*
 * The delta table generates primes just less than a power of two.  A prime
 * number is calculated by subtracting its delta value from its 
 * corresponding power of two.
 */

static uint8_t delta[] = {
	0, 0, 1, 3, 3, 1, 3, 1, 5, 3,
	3, 9, 3, 1, 3, 19, 15, 1, 5, 1,
	3, 9, 3, 15, 3, 39, 5, 39, 57, 3,
	35, 1, 5, 9, 41, 31, 5,
	25, 45, 7,
	87, 21, 11, 57, 17, 55, 21, 115, 59, 81,
	27,
	129, 47, 111, 33, 55, 5, 13, 27, 55,
	93, 1, 57, 25, 59
};

/*
 * error routine 
 */
void error(const char *fmt, ...)
{
	va_list arglist;
	char msg[BSIZE];

	va_start(arglist, fmt);
	vsnprintf(msg, BSIZE, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "%s\n", msg);

	exit(1);
}

/*
 * 64-bit Fowler/Noll/Vo double-hash function 
 */
uint64_t doublehash(const void *key, uint32_t len)
{
	uint32_t i;
	uint64_t hash;

	const uint8_t *k = (const uint8_t *) key;

	for (hash = 0, i = 0; i < len; ++i) {
		hash *= PLATFORM_S64(1099511628211);
		hash ^= k[i];
	}

	k = (const uint8_t *) &hash;

	for (i = 0; i < sizeof(uint64_t); ++i) {
		hash *= PLATFORM_S64(1099511628211);
		hash ^= k[i];
	}

	return hash;
}


/*
 * Compute the largest prime less than a specified power of two
 */
uint64_t prime(uint64_t i)
{
	uint32_t j = 1;

	while (i >>= 1)
		j++;

	return (PLATFORM_S64(1) << j) - delta[j];
}
