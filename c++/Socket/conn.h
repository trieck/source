/////////////////////////////////////////////////////////////////////////////
//
// CONN.H : TCP/IP connection class
//
// Copyright (c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __CONN_H__
#define __CONN_H__

#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
class Connection
{
public:
// Construction / Destruction
    Connection();
    Connection(SOCKET s);
    virtual ~Connection();

    // take ownership
    Connection(Connection &rhs);
    Connection &operator = (Connection &rhs);

// Interface
public:

    bool connect(const char *host, int port);
    bool send(const char *str) const;
    int receive(char *buffer, size_t size) const;
    bool bind();
    bool listen(int port, int backlog = 100);
    int pendingBytes() const;
    bool setBlockingMode(bool block) const;
    int select(bool read, bool write, bool error, timeval *timeout);
    Connection accept() const;
    SOCKET release()
    {
        own = false;
        return m_socket;
    }
    SOCKET getSock() const
    {
        return m_socket;
    }
    bool valid() const
    {
        return m_socket != INVALID_SOCKET;
    }

// Implementation
private:
    bool gethost(const char *host, int port);
    void close();
    SOCKET m_socket;
    SOCKADDR_IN m_server;
    bool own;
};
/////////////////////////////////////////////////////////////////////////////

typedef Connection *LPCONNECTION;

#endif // __CONN_H__