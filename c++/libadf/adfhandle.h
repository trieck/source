/////////////////////////////////////////////////////////////////////////////
//
// ADFHANDLE.H : ADF handler 
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ADFHANDLE_H__
#define __ADFHANDLE_H__

/////////////////////////////////////////////////////////////////////////////
// IADFHandler interface
class IADFHandler {
public:
	virtual void handle(const string &) const = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Handler registration
class HandlerRegistrar;
typedef auto_ptr<HandlerRegistrar> HandlerRegistrarPtr;

class HandlerRegistrar
{
private:
	HandlerRegistrar();
public:
	virtual ~HandlerRegistrar();

	static HandlerRegistrar *getInstance();
	void add(IADFHandler *pHandler);

	typedef vector<IADFHandler*> IADFHandlerVec;
	typedef IADFHandlerVec::const_iterator IADFHandlerIterator;

	IADFHandlerIterator iterator();
	IADFHandlerIterator end();
private:
	static HandlerRegistrarPtr instance;
	
	
	IADFHandlerVec handlers;
};

#endif // __ADFHANDLE_H__