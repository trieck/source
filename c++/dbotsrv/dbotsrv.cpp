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

#define DEFAULT_PORT	(5009)
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
		return;	// can't listen

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
	char buf[20];

	// read the SHA1 message digest
	int nread = pRemote->read(buf, 20);	
	if (nread != 20) {
		;
	}

	// how many bytes remain?
	uint32_t size;
	nread = pRemote->read(&size, sizeof(uint32_t));
	if (nread != sizeof(uint32_t)) {
		;
	}

	// allocate a buffer to hold message
	uint8_t *pbuf = new uint8_t[size];

	// read message 
	nread = pRemote->read(pbuf, size);

	// cleanup
	delete []pbuf;
	
}
