/////////////////////////////////////////////////////////////////////////////
//
//	GAME.H : Pente Game
//
#ifndef __GAME_H__
#define __GAME_H__

#include "PenteBoard.h"
#include "player.h"

typedef std::vector<CPoint> PointVec;
// forward declarations
class Computer;

/////////////////////////////////////////////////////////////////////////////
class PenteGame : public CObject
{
public:
	typedef enum {
		turnPlayerOne = 0,
		turnPlayerTwo = 1
	} Turn;
	
// Construction / Destruction
	PenteGame();
	virtual ~PenteGame();
// Interface
	PenteBoard *getBoard();
	const Player *getPlayerOne() const;
	const Player *getPlayerTwo() const;
	void clear();
	void render(CDC *pDC, const CRect & rc);
	Turn getTurn() const;
	bool findPiece(int x, int y) const;
	bool addPiece(int x, int y, PointVec &pts);
	void Serialize(CArchive& ar);
	static WORD getFileMagicNumber();

// Implementation	
protected:
private:
	typedef struct {
		CPoint start;
		CPoint end;
	} Capture;
	typedef std::vector<Capture> CaptureVec;
	void changeTurns();
	void closeCaptures(int x, int y, CaptureVec & captures);
	bool isCapture(const CPoint & op1, const CPoint & op2, 
		const CPoint & end) const;
	void addCapture(const CPoint & start, const CPoint & end, 
		CaptureVec & captures) const;
	void makePlayers();
	PenteBoard board;
	PlayerPtr playerOne;
	PlayerPtr playerTwo;
	Turn currentTurn;
	static WORD magicNumber;
	friend class Computer;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
inline WORD PenteGame::getFileMagicNumber() {
	return magicNumber;
}
/////////////////////////////////////////////////////////////////////////////
inline PenteBoard * PenteGame::getBoard() {
	return &board;
}
/////////////////////////////////////////////////////////////////////////////
inline const Player *PenteGame::getPlayerOne() const {
	return playerOne.get();
}
/////////////////////////////////////////////////////////////////////////////
inline const Player *PenteGame::getPlayerTwo() const {
	return playerTwo.get();
}
/////////////////////////////////////////////////////////////////////////////
inline PenteGame::Turn PenteGame::getTurn() const {
	return currentTurn;
}
#endif // __GAME_H__
