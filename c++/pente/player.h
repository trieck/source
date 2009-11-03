/////////////////////////////////////////////////////////////////////////////
//
//	PLAYER.H : Pente Player Abstraction
//
#ifndef __PLAYER_H__
#define __PLAYER_H__

/////////////////////////////////////////////////////////////////////////////
class Player : public CObject
{
// Construction / Destruction
public:
	Player();
	Player(const Player &);
	virtual ~Player();

// Interface
	Player & operator = (const Player &);
	
	unsigned getCaptures() const;
	bool addCapture();
	void Serialize(CArchive & ar);
	bool isWinner() const;
	
	static int getMaxCaptures();

// Implementation
protected:

private:
	enum { maxcaptures = 5 };
	BYTE captures;
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
inline int Player::getMaxCaptures() {
	return maxcaptures;
}

#endif // __PLAYER_H__
