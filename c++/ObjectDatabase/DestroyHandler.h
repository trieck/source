/////////////////////////////////////////////////////////////////////////////
//
// DESTROYHANDLER.H : Object destruction handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DESTROYHANDLER_H__
#define __DESTROYHANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class DestroyHandler : public IHandler
{
// Construction / Destruction
public:
	DestroyHandler();
	virtual ~DestroyHandler();

// Interface
	void Call(LPDICTIONARY request, LPDICTIONARY response);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif //__DESTROYHANDLER_H__