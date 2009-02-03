/////////////////////////////////////////////////////////////////////////////
//
// ADFWARN.CPP : ADF warning handler 
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adfwarn.h"

HandlerRegistrar *pRegistrar = HandlerRegistrar::getInstance();

/////////////////////////////////////////////////////////////////////////////
void ADFWarningRegistrar::Register(IADFWarningHandler *pHandler)
{
	pRegistrar->add(pHandler);
}

/////////////////////////////////////////////////////////////////////////////
void ADFWarningDispatcher::dispatch(const string &s)
{
	HandlerRegistrar::IADFHandlerIterator it = pRegistrar->iterator();
	for ( ; it != pRegistrar->end(); it++) {
		IADFWarningHandler *pHandler = 
			dynamic_cast<IADFWarningHandler*>(*it);
		if (pHandler == NULL) continue;	// not a warning handler
		pHandler->handle(s);
	}
}