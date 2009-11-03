/////////////////////////////////////////////////////////////////////////////
//
//	PLAYER.CPP : Pente Player Abstraction
//
#include "stdafx.h"
#include "player.h"
#include "PenteBoard.h"

IMPLEMENT_DYNAMIC(Player, CObject)
/////////////////////////////////////////////////////////////////////////////
Player::Player()
 : captures(0), hPiece(NULL)
{
}
/////////////////////////////////////////////////////////////////////////////
Player::Player(const Player & player)
{
	*this = player;
}
/////////////////////////////////////////////////////////////////////////////
Player & Player::operator = (const Player & player)
{
	if (this != &player) {
		captures = player.captures;
		pieces = player.pieces;
		hPiece = player.hPiece;
	}
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
Player::~Player()
{
	if (hPiece != NULL) {
		DestroyIcon(hPiece);
	}
}
/////////////////////////////////////////////////////////////////////////////
void Player::render(CDC *pDC, const CRect & rc)
{
	renderPieces(pDC, rc);
}
/////////////////////////////////////////////////////////////////////////////
void Player::renderPieces(CDC *pDC, const CRect & rc) const
{
	PiecesVec::const_iterator it = pieces.begin();
	for ( ; it != pieces.end(); it++)
		renderPiece(pDC, *it);
}
/////////////////////////////////////////////////////////////////////////////
void Player::renderPiece(CDC *pDC, const Piece & piece) const
{
	ASSERT(hPiece != NULL);
	CPoint pt = PenteBoard::mapIndexToPoint(piece.location);
	
	DrawIconEx(*pDC, pt.x, pt.y, hPiece, cxIcon, cyIcon, 0, NULL, DI_NORMAL);
}
/////////////////////////////////////////////////////////////////////////////
bool Player::addPiece(int x, int y)
{
	if (findPiece(x, y))
		return false;
	Piece piece;
	piece.location = CPoint(x, y);
	pieces.push_back(piece);
	return true;
}
/////////////////////////////////////////////////////////////////////////////
bool Player::removePiece(int x, int y)
{
	PiecesVec::iterator it = pieces.begin();
	for ( ; it != pieces.end(); it++) {
		if ((*it).location == CPoint(x, y)) {
			pieces.erase(it);
			return true;
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////
bool Player::findPiece(int x, int y) const
{
	PiecesVec::const_iterator it = pieces.begin();
	for ( ; it != pieces.end(); it++) {
		if ((*it).location.x == x && (*it).location.y == y)
			return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////
Player::Piece::Piece()
 : location(-1, -1)
{
}
/////////////////////////////////////////////////////////////////////////////
Player::Piece::Piece(const Piece & piece)
{
	*this = piece;
}
/////////////////////////////////////////////////////////////////////////////
Player::Piece::~Piece()
{
}
/////////////////////////////////////////////////////////////////////////////
Player::Piece & Player::Piece::operator = (const Player::Piece & piece)
{
	if (this != &piece) {
		location = piece.location;
	}
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
void Player::Serialize(CArchive & ar)
{
	short count;
	BYTE index;
	if (ar.IsStoring()) {
		ar << captures;
		ar << (short)pieces.size();
		PiecesVec::const_iterator it = pieces.begin();
		for ( ; it != pieces.end(); it++) {
			ar << (BYTE)(*it).location.x;
			ar << (BYTE)(*it).location.y;
		}
	} else {
		ar >> captures;
		ar >> count;
		pieces.resize(count);
		for (int i = 0; i < count; i++) {
			ar >> index;
			pieces[i].location.x = index;
			ar >> index;
			pieces[i].location.y = index;
		}
	}
}