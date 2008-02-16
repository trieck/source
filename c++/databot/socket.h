/////////////////////////////////////////////////////////////////////////////
//
// SOCKET.H : TCP/IP Socket class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#ifndef __SOCKET_H__
#define __SOCKET_H__

/////////////////////////////////////////////////////////////////////////////
class Socket 
{
// Construction / Destruction
public:
	Socket();
	Socket(SOCKET s);
	virtual ~Socket();

// Interface
	bool connect(LPCSTR host, uint16_t port);
	void close();	
	int read(void *buf, int nlen);
	int write(const void *buf, int nlen);

	static string lasterror();

// Implementation
protected:
	bool mksock();
	SOCKET getSock() const { return sock; }
private:
	bool gethost(LPCSTR host, uint16_t port, SOCKADDR_IN *addr);
	SOCKET sock;
};
/////////////////////////////////////////////////////////////////////////////

typedef auto_ptr<Socket> SocketPtr;

#endif // __SOCKET_H__