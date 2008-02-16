/////////////////////////////////////////////////////////////////////////////
//
// SRVSOCK.CPP : TCP/IP Server ServerSocket class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#include "common.h"
#include <winsock2.h>
#include "socket.h"
#include "srvsock.h"

/////////////////////////////////////////////////////////////////////////////
ServerSocket::ServerSocket()
{
}

/////////////////////////////////////////////////////////////////////////////
ServerSocket::~ServerSocket() 
{
}

/////////////////////////////////////////////////////////////////////////////
bool ServerSocket::listen(uint16_t port)
{
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));

	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

	// allocate socket
	if (!mksock())
		return false;
	
	// bind socket to port
	if (bind(getSock(), (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN))
		== SOCKET_ERROR)
		return false;

	// place the socket in a listening state
	if (::listen(getSock(), SOMAXCONN) == SOCKET_ERROR)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
SocketPtr ServerSocket::accept() const
{
     // Accept incoming connections
    SOCKET remote = ::accept(getSock(), NULL, 0);

	return new Socket(remote);
}