/////////////////////////////////////////////////////////////////////////////
//
// PAYFLOW.CPP : PayFlow Pro object wrapper
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#include "stdafx.h"
#include "common.h"
#include "payflow.h"
#include <pfpro.h>

/////////////////////////////////////////////////////////////////////////////
PayFlow::PayFlow(const string &shost, int nport, int ntimeout)
		: host(shost), port(nport), timeout(ntimeout), context(0)
{
	CreateContext();
}

/////////////////////////////////////////////////////////////////////////////
PayFlow::~PayFlow()
{
	DestroyContext();
}

/////////////////////////////////////////////////////////////////////////////
int PayFlow::init()
{
	return pfproInit();
}

/////////////////////////////////////////////////////////////////////////////
void PayFlow::cleanup()
{
	return pfproCleanup();
}

/////////////////////////////////////////////////////////////////////////////
int PayFlow::CreateContext()
{
	return pfproCreateContext(&context,
	                          const_cast<char*>(host.c_str()),
	                          port,
	                          timeout,
	                          NULL,
	                          NULL,
	                          NULL,
	                          NULL);
}

/////////////////////////////////////////////////////////////////////////////
int PayFlow::DestroyContext()
{
	return pfproDestroyContext(context);
}

/////////////////////////////////////////////////////////////////////////////
stringmap PayFlow::SubmitTransaction(const string &params)
{
	stringmap M;

	char *buf = 0;

	pfproSubmitTransaction(context,
	                       const_cast<char*>(params.c_str()),
	                       (LONG)params.length(),
	                       &buf);

	if (buf == 0)
		return M;

	M = ParseResponse(buf);
	pfproCompleteTransaction(buf);

	return M;
}

/////////////////////////////////////////////////////////////////////////////
stringmap PayFlow::ParseResponse(const char *response)
{
	stringmap M;

	CString name;
	CString value;

	const char* pin = response;
	CString* pout = &name;

	for (;;) {
		switch (*pin) {
		case '\0':
			if (*name != '\0')
				M[(LPCSTR)name] = value;
			return M;
		case '&':
			if (name != "")
				M[(LPCSTR)name] = value;
			name = "";
			value = "";
			pout = &name;
			pin++;
			while (isspace(*pin))
				pin++;
			break;
		case '=':
			value = "";
			pout = &value;
			pin++;
			break;
		default:
			*pout += *pin++;
		}
	}

	return M;
}

