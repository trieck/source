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

IMPLEMENT_SERIAL(PenteGame, CObject, VERSIONABLE_SCHEMA | 1)

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
	currentTurn = ~currentTurn & (ET_PLAYER_TWO+1);
}

/////////////////////////////////////////////////////////////////////////////
bool PenteGame::addPiece(int x, int y, CaptureVec &captures)
{
	// ensure the piece is not already taken
	if (!board.addPiece(x, y, currentTurn))
		return false;

	getCaptures(CPoint(x, y), captures);

	changeTurns();

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool PenteGame::move(CPoint &pt, CaptureVec &captures)
{
	if (currentTurn != ET_PLAYER_TWO)
		return false;

	Player *player = playerTwo.get();
	if (!player->IsKindOf(RUNTIME_CLASS(Computer)))
		return false;

	Computer *comp = (Computer *)player;
	if (!comp->getMove(pt))
		return false;

	getCaptures(pt, captures);

	changeTurns();

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

	PenteApp *pApp = (PenteApp*)AfxGetApp();
	uint8_t twoPlayer;

	if (ar.IsStoring()) {
		twoPlayer = pApp->isTwoPlayerGame() ? 1 : 0;
		ar << magicNumber;
		ar << twoPlayer;
		ar << (BYTE)currentTurn;
	} else {
		ar >> num;
		ar >> twoPlayer;
		ar.Read(&currentTurn, sizeof(BYTE));
		pApp->setTwoPlayerGame(twoPlayer ? true : false);
		makePlayers();
	}

	// captures
	playerOne->Serialize(ar);
	playerTwo->Serialize(ar);

	board.Serialize(ar);
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

/////////////////////////////////////////////////////////////////////////////
const Vector *PenteGame::winner(uint32_t &nplayer) const
{
	return board.winner(nplayer);
}

/////////////////////////////////////////////////////////////////////////////
void PenteGame::getCaptures(const CPoint &pt, CaptureVec &captures)
{
	board.getCaptures(pt, captures);

	Player *player = getCurrentPlayer();

	player->addCaptures(captures.size());
}

/////////////////////////////////////////////////////////////////////////////
Player *PenteGame::getCurrentPlayer() const
{
	Player *player = currentTurn == ET_PLAYER_ONE ?
	                 playerOne.get() : playerTwo.get();
	return player;
}
