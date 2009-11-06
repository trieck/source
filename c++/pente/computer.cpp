/////////////////////////////////////////////////////////////////////////////
//
//	COMPUTER.CPP : Computer Player Class
//
#include "stdafx.h"
#include "computer.h"
#include "PenteBoard.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(Computer, PlayerTwo)

/////////////////////////////////////////////////////////////////////////////
Computer::Computer(Player *popponent)
: opponent(popponent)
{
	ASSERT_VALID(opponent);
}

/////////////////////////////////////////////////////////////////////////////
Computer::~Computer()
{
}

/////////////////////////////////////////////////////////////////////////////
bool Computer::getMove(CPoint & pt)
{
	POINT aPoint = machine.move();
	if (!isNilMove(aPoint)) {
		pt = aPoint;
		return true;
	}

	return false;
}

