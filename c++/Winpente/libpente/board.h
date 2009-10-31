/////////////////////////////////////////////////////////////////////////////
//
// BOARD.H : Pente board
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BOARD_H__
#define __BOARD_H__

#include "entry.h"
#include "enum.h"

// size of board 
#define BOARD_SIZE		(19)
#define BOARD_ENTRIES	(BOARD_SIZE*BOARD_SIZE)

typedef std::map<uint32_t, uint32_t> UInt32Map;
typedef std::pair<uint32_t, uint32_t> UInt32Pair;
typedef UInt32Map::const_iterator UInt32MapConstIter;
typedef Enumerator<UInt32Map> UInt32MapEnum;
typedef std::vector<Entry> EntryVec;

/////////////////////////////////////////////////////////////////////////////
class Board
{
// Construction / Destruction
public:
	Board();
	virtual ~Board();

// Interface
	uint32_t getEntry(uint32_t row, uint32_t col) const;
	void setEntry(uint32_t row, uint32_t col, uint32_t type);
	void remove(uint32_t row, uint32_t col);
	void clear();
	UInt32MapEnum enumEntries();
	EntryVec empty();

// Implementation
private:	
	UInt32Map rep;
};

#endif /* __BOARD_H__ */