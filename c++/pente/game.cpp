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
 : currentTurn(turnPlayerOne)
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
	currentTurn = turnPlayerOne;
}
/////////////////////////////////////////////////////////////////////////////
void PenteGame::render(CDC *pDC, const CRect & rc)
{
	board.render(pDC, rc);
	playerOne->render(pDC, rc);
	playerTwo->render(pDC, rc);
}
/////////////////////////////////////////////////////////////////////////////
void PenteGame::changeTurns()
{
	if (currentTurn == turnPlayerOne)
		currentTurn = turnPlayerTwo;
	else currentTurn = turnPlayerOne;
}
/////////////////////////////////////////////////////////////////////////////
bool PenteGame::addPiece(int x, int y, PointVec &pts)
{
	// ensure the piece is not already taken
	if (findPiece(x, y))
		return false;
	Player *player = currentTurn == turnPlayerOne ?
		playerOne.get() : playerTwo.get();
	
	if (!player->addPiece(x, y))
		return false;
	pts.push_back(CPoint(x, y));
	// process captures
	CaptureVec captures;
	closeCaptures(x, y, captures);
	CaptureVec::const_iterator it = captures.begin();
	for ( ; it != captures.end(); it++) {
		pts.push_back((*it).start);
		pts.push_back((*it).end);
	}
	changeTurns();
	// if this is a single player game against the computer
	// then this function is recursive
	player = currentTurn == turnPlayerOne ? 
		playerOne.get() : playerTwo.get();
	if (player->IsKindOf(RUNTIME_CLASS(Computer))) {
		Computer *comp = (Computer *)player;
		CPoint pt;
		comp->getMove(pt);
		addPiece(pt.x, pt.y, pts);
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////
bool PenteGame::findPiece(int x, int y) const
{
	if (playerOne->findPiece(x, y))
		return true;
	if (playerTwo->findPiece(x, y))
		return true;
	return false;
}
/////////////////////////////////////////////////////////////////////////////
void PenteGame::closeCaptures(int x, int y, CaptureVec & captures)
{
	captures.clear();
	CPoint opponent1, opponent2, captureEnd;
	// capture from the right
	opponent1 = CPoint(x - 1, y);
	opponent2 = CPoint(x - 2, y);
	captureEnd = CPoint(x - 3, y);
	if (isCapture(opponent1, opponent2, captureEnd))
		addCapture(opponent1, opponent2, captures);
	// capture from the bottom right
	opponent1 = CPoint(x - 1, y - 1);
	opponent2 = CPoint(x - 2, y - 2);
	captureEnd = CPoint(x - 3, y - 3);
	if (isCapture(opponent1, opponent2, captureEnd)) 
		addCapture(opponent1, opponent2, captures);
	
	// capture from the bottom
	opponent1 = CPoint(x, y - 1);
	opponent2 = CPoint(x, y - 2);
	captureEnd = CPoint(x, y - 3);
	if (isCapture(opponent1, opponent2, captureEnd)) 
		addCapture(opponent1, opponent2, captures);
	// capture from the bottom left
	opponent1 = CPoint(x + 1, y - 1);
	opponent2 = CPoint(x + 2, y - 2);
	captureEnd = CPoint(x + 3, y - 3);
	if (isCapture(opponent1, opponent2, captureEnd)) 
		addCapture(opponent1, opponent2, captures);
	// capture from the left
	opponent1 = CPoint(x + 1, y);
	opponent2 = CPoint(x + 2, y);
	captureEnd = CPoint(x + 3, y);
	if (isCapture(opponent1, opponent2, captureEnd)) 
		addCapture(opponent1, opponent2, captures);
	// capture from the top left
	opponent1 = CPoint(x + 1, y + 1);
	opponent2 = CPoint(x + 2, y + 2);
	captureEnd = CPoint(x + 3, y + 3);
	if (isCapture(opponent1, opponent2, captureEnd))
		addCapture(opponent1, opponent2, captures);
	// capture from the top
	opponent1 = CPoint(x, y + 1);
	opponent2 = CPoint(x, y + 2);
	captureEnd = CPoint(x, y + 3);
	if (isCapture(opponent1, opponent2, captureEnd))
		addCapture(opponent1, opponent2, captures);
	// capture from the top right
	opponent1 = CPoint(x - 1, y + 1);
	opponent2 = CPoint(x - 2, y + 2);
	captureEnd = CPoint(x - 3, y + 3);
	if (isCapture(opponent1, opponent2, captureEnd))
		addCapture(opponent1, opponent2, captures);
}
/////////////////////////////////////////////////////////////////////////////
bool PenteGame::isCapture(const CPoint & op1, const CPoint & op2,
 const CPoint & end) const
{
	Player *current = currentTurn == turnPlayerOne ?
		playerOne.get() : playerTwo.get();
	Player *opponent = current == playerOne.get() ? 
		playerTwo.get() : playerOne.get();
	if (!PenteBoard::isValidPiece(op1.x, op1.y))
		return false;
	if (!PenteBoard::isValidPiece(op2.x, op2.y))
		return false;
	if (!PenteBoard::isValidPiece(end.x, end.y))
		return false;
	if (!opponent->findPiece(op1.x, op1.y))
		return false;
	if (!opponent->findPiece(op2.x, op2.y))
		return false;
	if (!current->findPiece(end.x, end.y))
		return false;
	return true;
}
/////////////////////////////////////////////////////////////////////////////
void PenteGame::addCapture(const CPoint & start, const CPoint & end, 
 CaptureVec & captures) const
{
	Player *player = currentTurn == turnPlayerOne ? 
		playerOne.get() : playerTwo.get();
	Player *opponent = player == playerOne.get() ? 
		playerTwo.get() : playerOne.get();
	Capture capture;
	capture.start = start;
	capture.end = end;
	captures.push_back(capture);
	
	opponent->removePiece(start.x, start.y);
	opponent->removePiece(end.x, end.y);
	player->addCapture();
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