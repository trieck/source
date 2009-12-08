///////////////////////////////////////////////////////////////////////////////
//
// TRAP.H : Implementation of traps
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __TRAP_H__
#define __TRAP_H__

/////////////////////////////////////////////////////////////////////////////
class TrapHandler {
// Construction / Destruction
public:
	TrapHandler() {}
	virtual ~TrapHandler() {}

// Interface
	virtual void trap(void *data) = 0;

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

typedef TrapHandler *LPTRAPHANDLER;

#endif // __TRAP_H__
