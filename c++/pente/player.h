/////////////////////////////////////////////////////////////////////////////
//
//	PLAYER.H : Pente Player Abstraction
//
#ifndef __PLAYER_H__
#define __PLAYER_H__

/////////////////////////////////////////////////////////////////////////////
class Player : public CObject
{
private:
	typedef struct Piece {
		Piece();
		Piece(const Piece &);
		Piece & operator = (const Piece &);
		~Piece();
		CPoint location;
	};
// Construction / Destruction
public:
	Player();
	Player(const Player &);
	virtual ~Player();
// Interface
	Player & operator = (const Player &);
	bool isWinner() const;
	unsigned getCaptures() const;
	bool findPiece(int x, int y) const;
	bool addPiece(int x, int y);
	bool addCapture();
	bool removePiece(int x, int y);
	void render(CDC *pDC, const CRect & rc);
	void Serialize(CArchive & ar);
	static getMaxCaptures();
// Implementation
protected:
	void renderPieces(CDC *pDC, const CRect & rc) const;
	void renderPiece(CDC *pDC, const Piece & piece) const;
	HICON hPiece;
private:
	enum { maxcaptures = 5 };
	enum { cxIcon = 16 };
	enum { cyIcon = 16 };
	BYTE captures;
	typedef std::vector<Piece> PiecesVec;
	PiecesVec pieces;
	DECLARE_DYNAMIC(Player)
};
/////////////////////////////////////////////////////////////////////////////
typedef std::auto_ptr<Player> PlayerPtr;
/////////////////////////////////////////////////////////////////////////////
inline bool Player::isWinner() const {
	return captures == maxcaptures;
}
/////////////////////////////////////////////////////////////////////////////
inline unsigned Player::getCaptures() const {
	return captures;
}
/////////////////////////////////////////////////////////////////////////////
inline bool Player::addCapture() {
	if (captures == maxcaptures)
		return false;
	++captures;
	return true;
}
/////////////////////////////////////////////////////////////////////////////
inline Player::getMaxCaptures() {
	return maxcaptures;
}
#endif // __PLAYER_H__