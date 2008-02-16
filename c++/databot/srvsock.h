/////////////////////////////////////////////////////////////////////////////
//
// SRVSOCK.H : TCP/IP Server Socket class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#ifndef __SRVSOCK_H__
#define __SRVSOCK_H__

/////////////////////////////////////////////////////////////////////////////
class ServerSocket : public Socket
{
// Construction / Destruction
public:
	ServerSocket();
	virtual ~ServerSocket();

// Interface
	bool listen(uint16_t port);
	SocketPtr accept() const;

// Implementation
private:	
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SRVSOCK_H__