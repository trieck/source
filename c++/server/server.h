/////////////////////////////////////////////////////////////////////////////
//
// SERVER.H
//
// Copyright (c) 2001 KnowX.com, All Rights Reserved
//

#ifndef __SERVER_H__
#define __SERVER_H__

#include "conn.h"

#define DEFAULT_HTTP_PORT 80

/////////////////////////////////////////////////////////////////////////////
class HttpServer {
public:
    HttpServer(int port = DEFAULT_HTTP_PORT);
    ~HttpServer();

// Interface
    bool run();

// Implementation
private:
    bool service(Connection *request);
    Connection conn;
    int port;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SERVER_H__