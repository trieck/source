/////////////////////////////////////////////////////////////////////////////
//
// MAKEPOOLHANDLER.H : Pool creation handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __MAKEPOOLHANDLER_H__
#define __MAKEPOOLHANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class MakePoolHandler : public IHandler {
// Construction / Destruction
public:
	MakePoolHandler();
	virtual ~MakePoolHandler();

// Interface
	void Call(LPDICTIONARY request, LPDICTIONARY response);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif //__MAKEPOOLHANDLER_H__