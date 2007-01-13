/////////////////////////////////////////////////////////////////////////////
//
// CONN.H : TCP/IP connection class
// 
// Copyright (c) 2001 KnowX.com, All Rights Reserved
//

#ifndef __CONN_H__
#define __CONN_H__

/////////////////////////////////////////////////////////////////////////////
class Connection
{
public:
	// Construction / Destruction
	Connection();
protected:
	Connection(SOCKET s);
public:
	virtual ~Connection();

	// Interface
	bool connect(const char *host, int port);
	bool send(const char *str) const;
	int receive(char *buffer, size_t size) const;
    bool bind();
    bool listen(int port, int backlog = 5);
	int pendingBytes() const;

	typedef auto_ptr<Connection> ConnectionPtr;
    ConnectionPtr accept() const;
	
    inline operator SOCKET() const { return m_socket; }

	static string getSocketError();

	// Implementation
private:
	bool gethost(const char *host, int port);
	void close();
	SOCKET m_socket;
	SOCKADDR_IN m_server;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CONN_H__