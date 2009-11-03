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

typedef std::map<uint32_t, Entry> UInt32EntryMap;
typedef std::pair<uint32_t, Entry> UInt32EntryPair;
typedef UInt32EntryMap::const_iterator UInt32EntryMapConstIter;
typedef Enumerator<UInt32EntryMap> UInt32EntryMapEnum;
typedef std::vector<Entry> EntryVec;

/////////////////////////////////////////////////////////////////////////////
class Board
{
// Construction / Destruction
private:
	Board();
public:
	virtual ~Board();

// Interface
	typedef std::auto_ptr<Board> BoardPtr;
	static Board *instance();

	uint32_t getEntry(uint32_t row, uint32_t col) const;
	void setEntry(uint32_t row, uint32_t col, uint32_t type);
	void remove(uint32_t row, uint32_t col);
	void clear();
	UInt32EntryMapEnum enumEntries();
	EntryVec empty();

// Implementation
private:	
	static BoardPtr This;
	UInt32EntryMap rep;
};

#endif /* __BOARD_H__ */