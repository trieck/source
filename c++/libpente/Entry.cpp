/////////////////////////////////////////////////////////////////////////////
//
// ENTRY.CPP : Pente board entry
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Entry.h"
#include "Board.h"

/////////////////////////////////////////////////////////////////////////////
Entry::Entry() : type(ET_EMPTY)
{
	memset(&pt, 0, sizeof(POINT));
}

/////////////////////////////////////////////////////////////////////////////
Entry::Entry(const POINT &aPoint, uint32_t ntype)  
{
	pt.x = aPoint.x % BOARD_SIZE; 
	pt.y = aPoint.y % BOARD_SIZE;
	type = ntype % (ET_PLAYER_TWO+1);
}

/////////////////////////////////////////////////////////////////////////////
Entry::~Entry()
{
}
