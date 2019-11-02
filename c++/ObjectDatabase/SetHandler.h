/////////////////////////////////////////////////////////////////////////////
//
// SETHANDLER.H : Object value set handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __SETHANDLER_H__
#define __SETHANDLER_H__

/////////////////////////////////////////////////////////////////////////////
class SetHandler : public IHandler
{
// Construction / Destruction
public:
    SetHandler();
    virtual ~SetHandler();

// Interface
    void Call(LPDICTIONARY request, LPDICTIONARY response);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif //__SETHANDLER_H__