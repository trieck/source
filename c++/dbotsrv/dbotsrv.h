/////////////////////////////////////////////////////////////////////////////
//
// DBOTSRV.H : Databot server class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#ifndef __DBOTSRV_H__
#define __DBOTSRV_H__

/////////////////////////////////////////////////////////////////////////////
class DatabotServer
{
// Construction / Destruction
public:
	DatabotServer();
	virtual ~DatabotServer();

// Interface
	void listen();

// Implementation
private:
	void dispatch(Socket *pRemote) const;
	ServerSocket socket;
	uint16_t nport;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __DBOTSRV_H__