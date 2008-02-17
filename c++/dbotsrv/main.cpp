/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Application entry point
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include <winsock2.h>
#include "socket.h"
#include "srvsock.h"
#include "dbotsrv.h"

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	DatabotServer server;
	server.listen();

	return 0;
}