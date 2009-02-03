/////////////////////////////////////////////////////////////////////////////
//
// ADFWARN.H : ADF warning handler 
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ADFWARN_H__
#define __ADFWARN_H__

#include "adfhandle.h"

/////////////////////////////////////////////////////////////////////////////
// IADFWarningHandler interface
class IADFWarningHandler : public IADFHandler {
};

/////////////////////////////////////////////////////////////////////////////
class ADFWarningRegistrar 
{
private:
	ADFWarningRegistrar();
public:	
	static void Register(IADFWarningHandler *pHandler);
};

/////////////////////////////////////////////////////////////////////////////
class ADFWarningDispatcher
{
private:
	ADFWarningDispatcher();
public:	
	static void dispatch(const string &s);
};

#endif // __ADFWARN_H__
