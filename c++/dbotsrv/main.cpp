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
#include "cominit.h"

#include "message.h"
#include "array.h"
#include "integer.h"
#include "float.h"
#include "mstring.h"

#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	COMInitializer coinit;
	DatabotServer server;

	try {
		//server.listen();

		Array array;
		array.add(new Integer(3));
		array.add(new Float(1.0));
		array.add(new String("Hello, World!"));

		Message message;
		message.put("foobar", "foobaz");
		message.put("foobat", array);

		Message message2(message.toString());
		
		cout << message.toString() << endl << endl;
		cout << message2.toString() << endl;

	} catch (const _com_error &e) {
		bstr_t desc = e.Description();
		if (desc.length() > 0) {
			cerr << (LPCSTR)desc << endl;
		} else {
			cerr << "ERROR: 0x" << std::hex << e.Error() << endl;
		}
		exit(1);
	} catch (const Exception &e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	return 0;
}