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
	uint32_t tablesize(uint32_t size);
		
	uint32_t numentries;		// number of entries
	uint32_t maxblocks;			// maximum number of blocks
	uint32_t totalblocks;		// total blocks in table
};

#endif // __INVERTER_H__
