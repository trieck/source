/////////////////////////////////////////////////////////////////////////////
//
// BOARD.CPP : Pente board
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"

#include "entry.h"
#include "board.h"

ANON_BEGIN
uint32_t key(uint32_t x, uint32_t y);
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
uint32_t Board::getEntry(uint32_t x, uint32_t y) const
{
	uint32_t k = key(x, y);

	UInt32EntryMap::const_iterator it = rep.find(k);
	if (it == rep.end())
		return ET_EMPTY;

	return (*it).second.getType();
}

/////////////////////////////////////////////////////////////////////////////
void Board::setEntry(uint32_t x, uint32_t y, uint32_t type)
{
	uint32_t k = key(x, y);

	POINT pt = { x, y };
	
	rep[k] = Entry(pt, type);
}

/////////////////////////////////////////////////////////////////////////////
void Board::remove(uint32_t x, uint32_t y)
{
	uint32_t k = key(x, y);

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
void Board::getCaptures(uint32_t x, uint32_t y, CaptureVec &captures)
{
	uint32_t player = getEntry(x, y);
	if (player == ET_EMPTY)
		return;	// not taken

	uint32_t opponent = ~player & (ET_PLAYER_TWO+1);

	POINT pts[2];

	// check for capture from below
	if (y >= 3) {
		if (getEntry(x, y-1) == opponent &&
			getEntry(x, y-2) == opponent &&
			getEntry(x, y-3) == player) {
			pts[0].x = x;
			pts[0].y = y - 1;
			pts[1].x = x;
			pts[1].y = y - 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for capture from above
	if (y <= BOARD_SIZE-4) {
		if (getEntry(x, y+1) == opponent &&
			getEntry(x, y+2) == opponent &&
			getEntry(x, y+3) == player) {
			pts[0].x = x;
			pts[0].y = y + 1;
			pts[1].x = x;
			pts[1].y = y + 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for capture from right
	if (x >=3) {
		if (getEntry(x-1, y) == opponent &&
			getEntry(x-2, y) == opponent &&
			getEntry(x-3, y) == player) {
			pts[0].x = x - 1;
			pts[0].y = y;
			pts[1].x = x - 2;
			pts[1].y = y;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for capture from left
	if (x <= BOARD_SIZE-4) {
		if (getEntry(x+1, y) == opponent &&
			getEntry(x+2, y) == opponent &&
			getEntry(x+3, y) == player) {
			pts[0].x = x + 1;
			pts[0].y = y;
			pts[1].x = x + 2;
			pts[1].y = y;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for diagonal capture from bottom left
	if (y >= 3 && x <= BOARD_SIZE-4) {
		if (getEntry(x+1, y-1) == opponent &&
			getEntry(x+2, y-2) == opponent &&
			getEntry(x+3, y-3) == player) {
			pts[0].x = x + 1;
			pts[0].y = y - 1;
			pts[1].x = x + 2;
			pts[1].y = y - 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for diagonal capture from bottom right
	if (y >= 3 && x >= 3) {
		if (getEntry(x-1, y-1) == opponent &&
			getEntry(x-2, y-2) == opponent &&
			getEntry(x-3, y-3) == player) {
			pts[0].x = x - 1;
			pts[0].y = y - 1;
			pts[1].x = x - 2;
			pts[1].y = y - 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for diagonal capture from top left
	if (y <= BOARD_SIZE-4 && x <= BOARD_SIZE-4) {
		if (getEntry(x+1, y+1) == opponent &&
			getEntry(x+2, y+2) == opponent &&
			getEntry(x+3, y+3) == player) {
			pts[0].x = x + 1;
			pts[0].y = y + 1;
			pts[1].x = x + 2;
			pts[1].y = y + 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	// check for diagonal capture from top right
	if (y <= BOARD_SIZE-4 && x >= 3) {
		if (getEntry(x-1, y+1) == opponent &&
			getEntry(x-2, y+2) == opponent &&
			getEntry(x-3, y+3) == player) {
			pts[0].x = x - 1;
			pts[0].y = y + 1;
			pts[1].x = x - 2;
			pts[1].y = y + 2;
			captures.push_back(Capture(pts[0], pts[1]));
		}
	}

	CaptureVec::const_iterator it = captures.begin();
	for ( ; it != captures.end(); it++) {
		const Capture &capture = *it;
		const POINT &pt1 = capture.getPoint1();
		const POINT &pt2 = capture.getPoint2();
		remove(pt1.x, pt1.y);
		remove(pt2.x, pt2.y);
	}

}

ANON_BEGIN

/////////////////////////////////////////////////////////////////////////////
uint32_t key(uint32_t x, uint32_t y)
{
	return (y % BOARD_SIZE) * BOARD_SIZE + (x % BOARD_SIZE);
}

ANON_END

