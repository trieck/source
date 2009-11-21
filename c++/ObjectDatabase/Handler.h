/////////////////////////////////////////////////////////////////////////////
//
// HANDLER.H : Service handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __HANDLER_H__
#define __HANDLER_H__

/////////////////////////////////////////////////////////////////////////////
// Handler interface
DECLARE_INTERFACE(IHandler)
{
public:
	virtual void Call(LPDICTIONARY request, LPDICTIONARY response) PURE;
};
typedef IHandler *PHANDLER;

/////////////////////////////////////////////////////////////////////////////
class Handler {
public:
	// Construction / Destruction
	Handler();
	~Handler();

// Interface
	typedef LPCONNECTION RequestType;

	BOOL Initialize(void* pv);
	void Execute(RequestType request, void* pv, OVERLAPPED* pOverlapped);
	void Terminate(void* pv);

// Implementation
private:
	LPBEOBJECT Receive(Connection &conn);
	LPBEOBJECT Dispatch(LPBEOBJECT request);
	BOOL Send(Connection &conn, LPBEOBJECT response);
	void CallHandler(LPINTEGER fnc, LPDICTIONARY req, LPDICTIONARY res);

	typedef map<INT, PHANDLER> HandlerMap;
	HandlerMap handler_map;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __HANDLER_H__