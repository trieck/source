/////////////////////////////////////////////////////////////////////////////
//
//	MAIN.CPP
//
//	Copyright (c) 2001 KnowX.com, All Rights Reserved
//

#include "common.h"
#include "server.h"

#define HTTP_PORT 8080

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
	HttpServer server(HTTP_PORT);

	try {
		server.run();
	}catch(const Exception &E) {
		cerr << E.getDescription() << endl;
		return 1;
	}

	return 0;
}
