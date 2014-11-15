/////////////////////////////////////////////////////////////////////////////
//
//	PLAYRONE.H : Player One Class
//
#ifndef __PLAYRONE_H__
#define __PLAYRONE_H__

#include "player.h"
/////////////////////////////////////////////////////////////////////////////
class PlayerOne : public Player {
// Construction / Destruction
public:
    PlayerOne();
    ~PlayerOne();
// Interface

// Implementation
protected:
private:
    DECLARE_DYNAMIC(PlayerOne)
};
#endif // __PLAYRONE_H__