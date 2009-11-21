/////////////////////////////////////////////////////////////////////////////
//
// INDEX.CPP : Hash table index
//
// The index consists of hash table containing pointers into the document
// vector dat file.
//
// Index blocks are stored as pairs of numbers, with the first representing
// the offset of the entry in the final table and the second containing
// the table entry itself.
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"
#include "index.h"

#define INDEX_SIZE	(2000000)

/////////////////////////////////////////////////////////////////////////////
Index::Index()
{
	records = NULL;
	blocksize = INDEX_SIZE;
	size = next = 0;
}

/////////////////////////////////////////////////////////////////////////////
Index::~Index()
{
	delete [] records;
}

/////////////////////////////////////////////////////////////////////////////
void Index::insert(const char* term, uint64_t offset)
{
	uint64_t h = fnvhash(term, strlen(term)) % size;
}

