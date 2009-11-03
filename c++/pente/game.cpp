/////////////////////////////////////////////////////////////////////////////
//
//	GAME.CPP : Pente Game
//
#include "stdafx.h"
#include "game.h"
#include "pente.h"
#include "playrone.h"
#include "playrtwo.h"
#include "computer.h"
#include "resource.h"

WORD PenteGame::magicNumber = MAKEWORD('P', 'T');

/////////////////////////////////////////////////////////////////////////////
PenteGame::PenteGame()
 : currentTurn(ET_PLAYER_ONE)
{
	makePlayers();
}

/////////////////////////////////////////////////////////////////////////////
PenteGame::~PenteGame()
{
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::clear()
{
	makePlayers();
	board.clear();
	currentTurn = ET_PLAYER_ONE;
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::render(CDC *pDC, const CRect & rc)
{
	board.render(pDC, rc);
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::changeTurns()
{
	if (currentTurn == ET_PLAYER_ONE)
		currentTurn = ET_PLAYER_TWO;
	else currentTurn = ET_PLAYER_ONE;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteGame::addPiece(int x, int y, PointVec &pts)
{
	// ensure the piece is not already taken
	if (!board.addPiece(x, y, currentTurn))
		return false;

	pts.push_back(CPoint(x, y));

	Player *player = currentTurn == ET_PLAYER_ONE ?
		playerOne.get() : playerTwo.get();
	
	changeTurns();

	player = currentTurn == ET_PLAYER_ONE ? 
		playerOne.get() : playerTwo.get();
	if (player->IsKindOf(RUNTIME_CLASS(Computer))) {
		Computer *comp = (Computer *)player;
		CPoint pt;
		if (!comp->getMove(pt))
			return false;
		pts.push_back(pt);
		changeTurns();
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteGame::findPiece(int x, int y) const
{
	return board.getPiece(x, y) != ET_EMPTY;
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::Serialize(CArchive& ar)
{	
	WORD num;
	
	if (ar.IsStoring()) {
		ar << magicNumber;
		ar << (BYTE)currentTurn;
	} else {
		ar >> num;
		ar.Read(&currentTurn, sizeof(BYTE));
		makePlayers();
	}
	playerOne->Serialize(ar);
	playerTwo->Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::makePlayers()
{
	PenteApp *pApp = (PenteApp*)AfxGetApp();
	ASSERT_VALID(pApp);
	playerOne = PlayerPtr(new PlayerOne());
	
	if (pApp->isTwoPlayerGame())
		playerTwo = PlayerPtr(new PlayerTwo());
	else playerTwo = PlayerPtr(new Computer(playerOne.get()));
}
