/////////////////////////////////////////////////////////////////////////////
//
// SERVER.CPP
//
// Copyright (c) 2001 KnowX.com, All Rights Reserved
//

#include "common.h"
#include "server.h"

/////////////////////////////////////////////////////////////////////////////
HttpServer::HttpServer(int lport)
		: port(lport)
{
}

/////////////////////////////////////////////////////////////////////////////
HttpServer::~HttpServer()
{
}

/////////////////////////////////////////////////////////////////////////////
bool HttpServer::run()
{
	if (!conn.listen(port))
		throw Exception(Connection::getSocketError().c_str());

	for (;;) {
		Connection::ConnectionPtr request = conn.accept();
		if (request.get() == NULL)
			continue;

		service(request.get());
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool HttpServer::service(Connection *request)
{
	int pending = request->pendingBytes();
	if (pending == 0)
		return false;

	char *pbuff = new char[pending + 1];
	if (pbuff == NULL)
		return false;

	int n = request->receive(pbuff, pending);
	if (n == SOCKET_ERROR || n == 0) {
		delete [] pbuff;
		return false;
	}

	pbuff[n] = '\0';

	cout << pbuff << endl;

	delete [] pbuff;

	static char response [] =
	    "HTTP/1.0 302 Moved Temporarily\n"
	    "Location: http://www.java.sun.com\n"
	    "Date: Sun, 21 Apr 1996 02:20:42 GMT\n"
	    "Server: Tom Rieck's Web Server/1.0\n"
	    "Content-Length: 0\n\n";

	// send response
	return request->send(response);
}