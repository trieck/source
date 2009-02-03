/////////////////////////////////////////////////////////////////////////////
//
// ADFHANDLE.CPP : ADF disk definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adfhandle.h"

HandlerRegistrarPtr HandlerRegistrar::instance(
	HandlerRegistrar::getInstance());

/////////////////////////////////////////////////////////////////////////////
HandlerRegistrar::HandlerRegistrar()
{
}

/////////////////////////////////////////////////////////////////////////////
HandlerRegistrar::~HandlerRegistrar()
{
}

/////////////////////////////////////////////////////////////////////////////
HandlerRegistrar *HandlerRegistrar::getInstance()
{
	if (instance.get() == NULL) {
		instance = HandlerRegistrarPtr(new HandlerRegistrar());
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void HandlerRegistrar::add(IADFHandler *pHandler)
{
	handlers.push_back(pHandler);
}

/////////////////////////////////////////////////////////////////////////////
HandlerRegistrar::IADFHandlerIterator HandlerRegistrar::iterator()
{
	return handlers.begin();
}

/////////////////////////////////////////////////////////////////////////////
HandlerRegistrar::IADFHandlerIterator HandlerRegistrar::end()
{
	return handlers.end();
}
