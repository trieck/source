/////////////////////////////////////////////////////////////////////////////
//
// GETHANDLER.H : Object value retrieval handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __GETHANDLER_H__
#define __GETHANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class GetHandler : public IHandler
{
// Construction / Destruction
public:
	GetHandler();
	virtual ~GetHandler();

// Interface
	void Call(LPDICTIONARY request, LPDICTIONARY response);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif //__GETHANDLER_H__