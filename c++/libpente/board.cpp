/////////////////////////////////////////////////////////////////////////////
//
// BOARD.CPP : Pente board
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"

#include "entry.h"
#include "board.h"

ANON_BEGIN
uint32_t key(uint32_t row, uint32_t col);
ANON_END

Board::BoardPtr Board::This;

/////////////////////////////////////////////////////////////////////////////
Board::Board()
{
	generate();
}

/////////////////////////////////////////////////////////////////////////////
Board::~Board()
{
}

/////////////////////////////////////////////////////////////////////////////
Board *Board::instance()
{
	if (This.get() == NULL) {
		This = BoardPtr(new Board());
	}

	return This.get();
}

/////////////////////////////////////////////////////////////////////////////
void Board::generate()
{
	uint32_t i, j, m, n;
	Vector v;

	// generate all initially feasible vectors 

	for (i = 0; i < BOARD_ENTRIES; i++) {
		m = i / BOARD_SIZE;
		n = i % BOARD_SIZE;
		
		// check for horizontal vector
		if (VSIZE + n <= BOARD_SIZE) {
			v.clear();
			for (j = 0; j < VSIZE; j++) {
				v.setEntry(j, m, n+j);
			}
			vectors.push_back(v);
		}

		// check for vertical vector
		if (VSIZE + m <= BOARD_SIZE) {
			v.clear();
			for (j = 0; j < VSIZE; j++) {
				v.setEntry(j, m+j, n);
			}
			vectors.push_back(v);
		}

		// check for a "diagonal down" vector
		if (VSIZE + m <= BOARD_SIZE && VSIZE + n <= BOARD_SIZE) {
			v.clear();
			for (j = 0; j < VSIZE; j++) {
				v.setEntry(j, m+j, n+j);
			}
			vectors.push_back(v);
		}

		// check for a "diagonal up" vector
		if (m >= VSIZE - 1 && VSIZE + n <= BOARD_SIZE) {
			v.clear();
			for (j = 0; j < VSIZE; j++) {
				v.setEntry(j, m-j, n+j);
			}
			vectors.push_back(v);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Board::getEntry(uint32_t row, uint32_t col) const
{
	uint32_t k = key(row, col);

	UInt32EntryMap::const_iterator it = rep.find(k);
	if (it == rep.end())
		return ET_EMPTY;

	return (*it).second.getType();
}

/////////////////////////////////////////////////////////////////////////////
void Board::setEntry(uint32_t row, uint32_t col, uint32_t type)
{
	uint32_t k = key(row, col);

	POINT pt = { row, col };
	
	rep[k] = Entry(pt, type);
}

/////////////////////////////////////////////////////////////////////////////
void Board::remove(uint32_t row, uint32_t col)
{
	uint32_t k = key(row, col);

	UInt32EntryMap::iterator it = rep.find(k);
	if (it != rep.end())
		rep.erase(it);
}

/////////////////////////////////////////////////////////////////////////////
void Board::clear()
{
	rep.clear();
}

/////////////////////////////////////////////////////////////////////////////
UInt32EntryMapEnum Board::enumEntries()
{
	UInt32EntryMapEnum e(rep);
	return e;
}

/////////////////////////////////////////////////////////////////////////////
EntryVec Board::empty()
{
	EntryVec v;

	uint32_t i, j;
	
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (getEntry(i, j) == ET_EMPTY) {
				POINT pt = { i, j };
				Entry e(pt, ET_EMPTY);
				v.push_back(e);
			}
		}
	}
	
	return v;
}

/////////////////////////////////////////////////////////////////////////////
const Vector* Board::winner(uint32_t &nplayer) const
{
	uint32_t i, type, onecount, twocount;
	POINT pt;

	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		for (i = 0, onecount = 0, twocount = 0; i < VSIZE; i++) {
			pt = (*it).entry(i);
			type = getEntry(pt.x, pt.y);
			if (type == ET_PLAYER_ONE) { onecount++; }
			if (type == ET_PLAYER_TWO) { twocount++; }
		}

		if (onecount == VSIZE) {
			nplayer = ET_PLAYER_ONE;
			return &*it;
		}
		
		if (twocount == VSIZE) {
			nplayer = ET_PLAYER_TWO;
			return &*it;
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
void Board::getCaptures(uint32_t row, uint32_t col, CaptureVec &captures)
{
	uint32_t player = getEntry(row, col);
	if (player == ET_EMPTY)
		return;	// not taken

	uint32_t opponent = ~player & (ET_PLAYER_TWO+1);

}

ANON_BEGIN

/////////////////////////////////////////////////////////////////////////////
uint32_t key(uint32_t row, uint32_t col)
{
	return (row % BOARD_SIZE) * BOARD_SIZE + (col % BOARD_SIZE);
}

ANON_END

