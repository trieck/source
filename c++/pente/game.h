/////////////////////////////////////////////////////////////////////////////
//
//	GAME.H : Pente Game
//
#ifndef __GAME_H__
#define __GAME_H__

#include "PenteBoard.h"
#include "player.h"
#include "libpente.h"

typedef std::vector<CPoint> PointVec;

/////////////////////////////////////////////////////////////////////////////
class PenteGame : public CObject {
public:
	DECLARE_SERIAL(PenteGame);

// Construction / Destruction
	PenteGame();
	virtual ~PenteGame();

// Interface
	PenteBoard *getBoard();
	const Player *getPlayerOne() const;
	const Player *getPlayerTwo() const;
	void clear();
	void render(CDC *pDC, const CRect & rc);
	uint32_t getTurn() const;
	bool findPiece(int x, int y) const;
	bool addPiece(int x, int y, CaptureVec &captures);
	bool move(CPoint &pt, CaptureVec &captures);
	void Serialize(CArchive& ar);
	static WORD getFileMagicNumber();
	const Vector *winner(uint32_t &nplayer);

// Implementation
private:
	void getCaptures(const CPoint &pt, CaptureVec &captures);
	void changeTurns();
	void makePlayers();
	Player *getCurrentPlayer() const;

	PenteBoard board;
	PlayerPtr playerOne;
	PlayerPtr playerTwo;
	uint32_t currentTurn;
	static WORD magicNumber;
};

/////////////////////////////////////////////////////////////////////////////
inline WORD PenteGame::getFileMagicNumber()
{
	return magicNumber;
}

/////////////////////////////////////////////////////////////////////////////
inline PenteBoard * PenteGame::getBoard()
{
	return &board;
}

/////////////////////////////////////////////////////////////////////////////
inline const Player *PenteGame::getPlayerOne() const
{
	return playerOne.get();
}

/////////////////////////////////////////////////////////////////////////////
inline const Player *PenteGame::getPlayerTwo() const
{
	return playerTwo.get();
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t PenteGame::getTurn() const
{
	return currentTurn;
}

#endif // __GAME_H__
