/////////////////////////////////////////////////////////////////////////////
//
// CONN.CPP : TCP/IP connection class
//
// Copyright (c) 2001 KnowX.com, All Rights Reserved
//

#include "common.h"
#include "conn.h"

struct _sockinit {
	_sockinit() {
		WSAStartup(0x202, &data);
	}
	~_sockinit() {
		WSACleanup();
	}
	WSADATA data;
} sockinit;

/////////////////////////////////////////////////////////////////////////////
Connection::Connection()
{
	memset(&m_server, 0, sizeof(SOCKADDR_IN));
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
}

/////////////////////////////////////////////////////////////////////////////
Connection::Connection(SOCKET s)
	: m_socket(s)
{
	memset(&m_server, 0, sizeof(SOCKADDR_IN));
}

/////////////////////////////////////////////////////////////////////////////
Connection::~Connection()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Connection::close()
{
	if (m_socket != INVALID_SOCKET) {
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool Connection::connect(const char* host, int port)
{
	if (m_socket == INVALID_SOCKET)
		return false;

	if (!gethost(host, port))
		return false;

	int n = ::connect(m_socket, (LPSOCKADDR)&m_server, sizeof(SOCKADDR_IN));

	return n != SOCKET_ERROR;
}

/////////////////////////////////////////////////////////////////////////////
bool Connection::send(const char *str) const
{
	size_t len = strlen(str);

	while (len > 0) {
		int n = ::send(m_socket, str, len, 0);
		if (n == SOCKET_ERROR)
			return false;

		str += n;
		len -= n;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
int Connection::receive(char *buffer, size_t size) const
{
	int read = recv(m_socket, buffer, size, 0);
	if (read == SOCKET_ERROR)
		return SOCKET_ERROR;

	buffer[read] = '\0';

	return read;
}

/////////////////////////////////////////////////////////////////////////////
bool Connection::gethost(const char *host, int port)
{
	memset(&m_server, 0, sizeof(SOCKADDR_IN));

	// Server may be specified in dotted IP address format
	// or it may be specified as a machine name.
	// If the server name is specified as a machine name,
	// we will do the DNS resolution here and use the
	// sockaddr_in structure format from here on out.
	LPHOSTENT ph;
	if (isalpha(host[0])) {
		ph = gethostbyname(host);
	} else {
		UINT addr = inet_addr(host);
		ph = gethostbyaddr((const char*)&addr, sizeof(UINT), AF_INET);
	}

	if (ph != NULL) {
		memcpy(&(m_server.sin_addr), ph->h_addr, ph->h_length);
		m_server.sin_family = ph->h_addrtype;
		m_server.sin_port = htons(port);
	}

	return ph != NULL;
}

/////////////////////////////////////////////////////////////////////////////
bool Connection::bind()
{
	if (m_socket == INVALID_SOCKET)
		return FALSE;

	int n = ::bind(m_socket, (LPSOCKADDR)&m_server, sizeof(SOCKADDR_IN));

	return n != SOCKET_ERROR;
}

/////////////////////////////////////////////////////////////////////////////
bool Connection::listen(int port, int backlog)
{
	m_server.sin_family = AF_INET;
	m_server.sin_addr.s_addr = INADDR_ANY;
	m_server.sin_port = htons(port);

	// bind a local address and port combination
	if (!bind())
		return false;

	// set socket to the listening state
	if (::listen(m_socket, backlog) == SOCKET_ERROR)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
Connection::ConnectionPtr Connection::accept() const
{
	SOCKADDR_IN remote;
	int len = sizeof(SOCKADDR_IN);

	// Accept incoming connections
	SOCKET remotesock = ::accept(m_socket, (LPSOCKADDR)&remote, &len);
	if (remotesock == INVALID_SOCKET)
		return NULL;

	// Create a new connection object based on the remote socket
	Connection *premote = new Connection(remotesock);
	if (premote != NULL) {
		memcpy(&premote->m_server, &remote, sizeof(SOCKADDR_IN));
	}

	return premote;
}

/////////////////////////////////////////////////////////////////////////////
string Connection::getSocketError()
{
	TCHAR buff[MAX_PATH];

	_stprintf(buff, _T("socket error (%d)"), WSAGetLastError());

	return buff;
}

/////////////////////////////////////////////////////////////////////////////
int Connection::pendingBytes() const
{
	unsigned long bytes;

	int n = ::ioctlsocket(m_socket, FIONREAD, &bytes);
	if (n == SOCKET_ERROR)
		return 0;

	return bytes;
}