/////////////////////////////////////////////////////////////////////////////
//
//	STACK.CPP	data stack implementation
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "stack.h"
#include "except.h"

//
// Constructor
//
Stack::Stack()
{
    stackp = data;
}

//
// Destructor
//
Stack::~Stack()
{
}

//
// pop
//
Datum Stack::pop()
{
    if (stackp == data)
        throw Error(E_STACKUNDERRUN);

    return *--stackp;
}

//
// push
//
void Stack::push(const Datum & datum)
{
    if (stackp >= &data[NSTACK])
        throw Error(E_STACKTOODEEP);

    *stackp++ = datum;
}

//
// reset
//
void Stack::reset()
{
    stackp = data;
}
