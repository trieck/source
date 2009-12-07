///////////////////////////////////////////////////////////////////////////////
//
// HANDLER.H : Handler interface
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __HANDLER_H__
#define __HANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class Handler {

// Construction / Destruction
public:
	Handler();
	virtual ~Handler();

// Interface
	virtual void handle() = 0;

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

typedef Handler *LPHANDLER;

#endif // __HANDLER_H__
