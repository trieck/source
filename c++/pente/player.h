/////////////////////////////////////////////////////////////////////////////
//
//	PLAYER.H : Pente Player Abstraction
//
#ifndef __PLAYER_H__
#define __PLAYER_H__

/////////////////////////////////////////////////////////////////////////////
class Player : public CObject {
// Construction / Destruction
public:
	Player();
	Player(const Player &);
	virtual ~Player();

// Interface
	Player & operator = (const Player &);

	unsigned getCaptures() const;
	bool addCapture();
	bool addCaptures(uint8_t ncaptures);

	void Serialize(CArchive & ar);
	bool isWinner() const;

	enum { MAX_CAPTURES = 5 };

// Implementation
private:
	uint8_t captures;
	DECLARE_DYNAMIC(Player)
};

/////////////////////////////////////////////////////////////////////////////
typedef std::auto_ptr<Player> PlayerPtr;

/////////////////////////////////////////////////////////////////////////////
inline bool Player::isWinner() const
{
	return captures == MAX_CAPTURES;
}

/////////////////////////////////////////////////////////////////////////////
inline unsigned Player::getCaptures() const
{
	return captures;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Player::addCapture()
{
	if (captures == MAX_CAPTURES)
		return false;
	++captures;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Player::addCaptures(uint8_t ncaptures)
{
	if (captures == MAX_CAPTURES)
		return false;

	captures = (captures + ncaptures) % (MAX_CAPTURES+1);

	return true;
}

#endif // __PLAYER_H__
