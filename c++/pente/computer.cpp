/////////////////////////////////////////////////////////////////////////////
//
//	COMPUTER.CPP : Computer Player Class
//
#include "stdafx.h"
#include "computer.h"
#include "board.h"
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
	memset((POINT*)&pt, 0, sizeof(POINT));
	randomPos(pt);
	return true;
}
/////////////////////////////////////////////////////////////////////////////
void Computer::randomPos(CPoint & pt)
{
	const int trys = 100;
	int x, y;
	CPoint extent = Board::getBoardSize();
	for (int i = 0; i < trys; i++) {
		x = rand() % extent.x;
		y = rand() % extent.y;
		ASSERT(Board::isValidPiece(x, y));
		if (!findPiece(x, y) && 
			!opponent->findPiece(x, y)) {
			pt = CPoint(x, y);
			break;
		}
	}
}
