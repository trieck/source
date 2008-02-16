/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Main application entry point
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "message.h"
#include "array.h"

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	Array v;
	v.add(1.0f);
	v.add(3.4f);
	v.add(0.0009f);
	
	Message message;
	message.put("client", 123456i64);
	message.put("command", "login");
	message.put("total-time", 0.995f);
	message.put("results", v);
	
	cout << message.toString() << endl;

	return 0;
}