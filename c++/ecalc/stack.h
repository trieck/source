/////////////////////////////////////////////////////////////////////////////
//
//	STACK.H		data stack implementation
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __STACK_H__
#define __STACK_H__

#define NSTACK 1024

/////////////////////////////////////////////////////////////////////////////
class Stack
{
public:
// Construction / Destruction
	Stack();
	~Stack();

// Interface
	const Datum & top();
	Datum pop();
	void push (const Datum &);
	void reset();

	Datum * stackp;
protected:
// Implementation
	Datum data[NSTACK];
};

/////////////////////////////////////////////////////////////////////////////

#endif // __STACK_H__

