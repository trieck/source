/////////////////////////////////////////////////////////////////////////////
//
//	COMPUTER.H : Computer Player Class
//
//	Copyright (c) 2000, Rieck Enterprises
//
#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include "playrtwo.h"
/////////////////////////////////////////////////////////////////////////////
class Computer : public PlayerTwo
{
// Construction / Destruction
public:
	Computer(Player *popponent);
	~Computer();
// Interface
	bool getMove(CPoint & pt);
	
// Implementation
protected:
private:
	void randomPos(CPoint & pt);
	Player *opponent;
	DECLARE_DYNAMIC(Computer)
};
/////////////////////////////////////////////////////////////////////////////
#endif // _COMPUTER_H__