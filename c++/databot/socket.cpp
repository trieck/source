/////////////////////////////////////////////////////////////////////////////
//
// SOCKET.CPP : TCP/IP Socket class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#include "common.h"
#include <winsock2.h>
#include "socket.h"

struct _sockinit {
	_sockinit() { WSAStartup(0x202, &data); }
    ~_sockinit() { WSACleanup(); }
	WSADATA data;
} sockinit;

/////////////////////////////////////////////////////////////////////////////
Socket::Socket()
 : sock(INVALID_SOCKET)
{
}

/////////////////////////////////////////////////////////////////////////////
Socket::~Socket() 
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Socket::close()
{
	if (sock != INVALID_SOCKET) {
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool Socket::connect(LPCSTR host, uint16_t port)
{
	close();

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) 
		== INVALID_SOCKET)
		return false;

	SOCKADDR_IN addr;
	if (!gethost(host, port, &addr))
		return false;

	int n = ::connect(sock, (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN));

	return n != SOCKET_ERROR;
}

/////////////////////////////////////////////////////////////////////////////
bool Socket::gethost(LPCSTR host, uint16_t port, SOCKADDR_IN *addr)
{
    memset(&addr, 0, sizeof(SOCKADDR_IN));
    
    // host may be specified in dotted IP address format
    // or it may be specified as a host name.
    LPHOSTENT ph;
    if (isalpha(host[0])) {
        ph = gethostbyname(host);
    } else {
		uint32_t iaddr = inet_addr(host);
        ph = gethostbyaddr((LPCSTR)iaddr, sizeof(uint32_t), AF_INET);
    }

    if (ph != NULL) {
        memcpy(&(addr->sin_addr), ph->h_addr, ph->h_length);
        addr->sin_family = ph->h_addrtype;
        addr->sin_port = htons(port);
    }

	return ph != NULL;
}

/////////////////////////////////////////////////////////////////////////////
int Socket::read(void *buf, int nlen)
{
	 return recv(sock, (char*)buf, nlen, 0);
}

/////////////////////////////////////////////////////////////////////////////
int Socket::write(const void *buf, int nlen)
{
	int n, nwritten = 0;

	const char *pbuf = (char*)buf;

    while (nlen) {
        n = send(sock, pbuf, nlen, 0);
        if (n == SOCKET_ERROR)
            return SOCKET_ERROR;
        
		pbuf += n; 
		nlen -= n;
    }

	return nwritten;
}

/////////////////////////////////////////////////////////////////////////////
string Socket::lasterror()
{
	string output;

	char *pmsg = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&pmsg, 0, NULL);
	
	if (pmsg != NULL) {
		int N = strlen(pmsg);
        if (N > 1 && pmsg[N - 1] == '\n')
			pmsg[N - 1] = '\0';
 
		if (N > 1 && pmsg[N - 2] == '\r')
			pmsg[N - 2] = '\0';

		output = pmsg;

		LocalFree(pmsg);
	}

    return output;                
}
