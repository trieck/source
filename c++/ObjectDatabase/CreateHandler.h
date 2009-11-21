/////////////////////////////////////////////////////////////////////////////
//
// CREATEHANDLER.H : Object creation handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __CREATEHANDLER_H__
#define __CREATEHANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class CreateHandler : public IHandler {
// Construction / Destruction
public:
	CreateHandler();
	virtual ~CreateHandler();

// Interface
	void Call(LPDICTIONARY request, LPDICTIONARY response);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif //__CREATEHANDLER_H__