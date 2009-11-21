/////////////////////////////////////////////////////////////////////////////
//
// PAYFLOW.H : PayFlow Pro object wrapper
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __PAYFLOW_H__
#define __PAYFLOW_H__

/////////////////////////////////////////////////////////////////////////////
class PayFlow {
public:
	PayFlow(const string &host, int port, int timeout);
	~PayFlow();

	static int init();
	static void cleanup();
	static string version();

	stringmap SubmitTransaction(const string &params);
private:
	static stringmap ParseResponse(const char *response);
	int CreateContext();
	int DestroyContext();
	string host;
	int port, timeout, context;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __PAYFLOW_H__