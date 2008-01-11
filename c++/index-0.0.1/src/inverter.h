/////////////////////////////////////////////////////////////////////////////
//
// INVERTER.H
//
// Inverted list of term locations in memory
// Copyright (c) 2008 Thomas A. Rieck
//

#ifndef __INVERTER_H__
#define __INVERTER_H__

/////////////////////////////////////////////////////////////////////////////
class Inverter
{
// Construction / Destruction
public:
	Inverter();
	~Inverter();

// Implementation
private:
	struct entry {
		const char *term;	// term for entry
		docentry *docvec;	// document vector
		uint32_t ndocs;		// number of docs in vector
	};
	
	void insert(const char *term, uint32_t docid);
	uint32_t lookup(const char *term);
	uint32_t tablesize(uint32_t size);
		
	uint32_t numentries;	// number of entries
	uint32_t maxblocks;		// maximum number of blocks
	uint32_t totalblocks;	// total blocks in table
	
	entry **blocks;			// array of pointers to document lists
};

#endif // __INVERTER_H__
