/////////////////////////////////////////////////////////////////////////////
//
// BOARD.CPP : Pente board
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "entry.h"
#include "board.h"

namespace  	// anonymous
{

uint32_t key(uint32_t row, uint32_t col);

}

Board::BoardPtr Board::This;

/////////////////////////////////////////////////////////////////////////////
Board::Board()
{
}

/////////////////////////////////////////////////////////////////////////////
Board::~Board()
{
}

/////////////////////////////////////////////////////////////////////////////
Board::BoardPtr Board::instance()
{
    if (This.get() == NULL) {
        This = BoardPtr(new Board());
    }

    return This;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Board::getEntry(uint32_t row, uint32_t col) const
{
    uint32_t k = key(row, col);

    UInt32Map::const_iterator it = rep.find(k);
    if (it == rep.end())
        return ET_EMPTY;

    return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
void Board::setEntry(uint32_t row, uint32_t col, uint32_t type)
{
    uint32_t k = key(row, col);
    rep[k] = type;
}

/////////////////////////////////////////////////////////////////////////////
void Board::remove(uint32_t row, uint32_t col)
{
    uint32_t k = key(row, col);

    UInt32Map::iterator it = rep.find(k);
    if (it != rep.end())
        rep.erase(it);
}

/////////////////////////////////////////////////////////////////////////////
void Board::clear()
{
    rep.clear();
}

/////////////////////////////////////////////////////////////////////////////
UInt32MapEnum Board::enumEntries()
{
    UInt32MapEnum e(rep.begin(), rep.end());
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

namespace  	// anonymous
{

/////////////////////////////////////////////////////////////////////////////
uint32_t key(uint32_t row, uint32_t col)
{
    return (row % BOARD_SIZE) * BOARD_SIZE + (col % BOARD_SIZE);
}

}
