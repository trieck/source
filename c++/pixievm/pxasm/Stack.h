/////////////////////////////////////////////////////////////////////////////
//
// STACK.H : machine stack
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STACK_H__
#define __STACK_H__

#include "SymbolTable.h"

/////////////////////////////////////////////////////////////////////////////
typedef union {
	word value;
	LPSYMBOL sym;
} Datum;

/////////////////////////////////////////////////////////////////////////////
class Stack
{
public:
	Stack();
	~Stack();

	Datum pop();
	void push(LPSYMBOL s);
	void push(word w);
	void push(const Datum &d);
	
	void reset();

private:
// Implementation
	enum { NSTACK = 1024 };

	Datum m_data[NSTACK];
	Datum *m_stackp;
};

#endif // __STACK_H__