/////////////////////////////////////////////////////////////////////////////
//
// INDEX.H : Hash table index
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

#ifndef __INDEX_H__
#define __INDEX_H__

/////////////////////////////////////////////////////////////////////////////
struct indexent {
	uint64_t bucket;	// number of hash bucket
	uint64_t offset;	// offset into concordance
};

/////////////////////////////////////////////////////////////////////////////
// Index Class Definition

class Index {
// Construction
public:
	Index();
	~Index();

// Interface
public:
	void insert(const char* key, uint64_t offset);

// Implementation
private:
	uint32_t blocksize; // in memory allocated size
	indexent* records;	// in memory index records
	uint64_t size;		// hash table size
	uint32_t next;		// next free record position
};

#endif	// __INDEX_H__
