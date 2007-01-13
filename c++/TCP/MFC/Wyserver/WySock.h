/*--------------------------------------
	Module:	WYSOCK.H
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/
#ifndef __WYSOCK_H__
#define __WYSOCK_H__

#include <afxwin.h>
#include <afxsock.h>
#include "..\..\merlin.h"

// max number connections
#define MAXCONN			5

#define DEFAULT_PORT	1024

// socket states
#define FREE			0
#define LISTENING		1
#define CONNECTED		2

#define NOTFOUND		-1

class CWySock : public CAsyncSocket
{
protected:
	REQUEST Request;
public:
	UINT	State;
	TCHAR	IPAddress[16];
	CWySock();
	~CWySock();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};
#endif //__WYSOCK_H__