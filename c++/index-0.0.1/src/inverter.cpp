/////////////////////////////////////////////////////////////////////////////
//
// INVERTER.CPP
//
// Inverted list of term locations in memory
// Copyright (c) 2008 Thomas A. Rieck
//

#include "global.h"
#include "inverter.h"

// maximum size of internal index in terms
#define MEMORY_SIZE		(2000000)

// maximum number of terms allowed
#define MAX_COUNT 		(MEMORY_SIZE / sizeof(entry*))

#define FILL_FACTOR		(0.72)

/////////////////////////////////////////////////////////////////////////////
Inverter::Inverter() : numentries(0)
{
	totalblocks = tablesize(MAX_COUNT);
	maxblocks = (uint32_t)(totalblocks * FILL_FACTOR);
	
	blocks = new entry*[totalblocks];
	memset(blocks, 0, totalblocks * sizeof(entry*));
}
	
/////////////////////////////////////////////////////////////////////////////
Inverter::~Inverter()
{
	delete []blocks;
}

/////////////////////////////////////////////////////////////////////////////
void Inverter::insert(const char *term, uint32_t docid)
{
	uint32_t i = lookup(term);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Inverter::lookup(const char *term)
{
	const char *p = term;

	uint32_t i = 0;

	while (*p)
		i = 127 * i + *p++;

	i = i % totalblocks;

	while (blocks[i] && strcmp(blocks[i]->term, term))
		i = ++i % totalblocks;

	return i;	
}

////////////////////////////////////////////////////////////////////////////
// return a suitable prime number size for a hash table
uint32_t Inverter::tablesize(uint32_t size)
{
	static const uint32_t primes [] = {
		19, 29, 41, 59, 79, 107, 149, 197, 263, 347, 457, 599, 787, 1031,
		1361, 1777, 2333, 3037, 3967, 5167, 6719, 8737, 11369, 14783,
		19219, 24989, 32491, 42257, 54941, 71429, 92861, 120721, 156941,
		204047, 265271, 344857, 448321, 582821, 757693, 985003, 1280519,
		1664681, 2164111, 2813353, 3657361, 4754591, 6180989, 8035301,
		10445899, 13579681, 17653589, 22949669, 29834603, 38784989,
		50420551, 65546729, 85210757, 110774011, 144006217, 187208107,
		243370577, 316381771, 411296309, 534685237, 695090819, 903618083,
		1174703521, 1527114613, 1985248999, 2580823717UL, 3355070839UL
	};

	int low, high, count = sizeof(primes) / sizeof(uint32_t);

	for (low = 0, high = count - 1; high - low > 1;) {
		int mid = (low + high) / 2;
		if (primes [mid] < size)
			low = mid;
		else
			high = mid;
    }

	return primes [high];
}
