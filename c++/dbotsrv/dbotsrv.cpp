/////////////////////////////////////////////////////////////////////////////
//
// DBOTSRV.CPP : Databot server class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#include "common.h"
#include <winsock2.h>
#include "socket.h"
#include "srvsock.h"
#include "dbotsrv.h"
#include "options.h"
#include "protocol.h"

#define OPTION_PORT		"port"

/////////////////////////////////////////////////////////////////////////////
DatabotServer::DatabotServer()
 : nport(DEFAULT_PORT)
{
	const char *port;
	if ((port = optionval(OPTION_PORT)) != NULL) {
		nport = atoi(port);
	}
}

/////////////////////////////////////////////////////////////////////////////
DatabotServer::~DatabotServer()
{
	socket.close();
}

/////////////////////////////////////////////////////////////////////////////
void DatabotServer::listen()
{
	if (!socket.listen(nport))
		throw Exception(Socket::lasterror());	// can't listen

	SocketPtr remote;
	for (;;) {
		remote = socket.accept();
		dispatch(remote.get());
		remote->close();
	}
}

/////////////////////////////////////////////////////////////////////////////
void DatabotServer::dispatch(Socket *pRemote) const
{

	
}
