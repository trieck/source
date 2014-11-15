/////////////////////////////////////////////////////////////////////////////
//
// FRAME.CPP	procedure / function call frame stack
//
// Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "frame.h"
#include "except.h"

//
// Constructor
//
FrameStack::FrameStack()
{
    framep = frame;
}

//
// Destructor
//
FrameStack::~FrameStack()
{
}

//
// pop
//
Frame FrameStack::pop()
{
    if (framep == frame)
        throw Error(E_FRAMEUNDERRUN);

    return *--framep;
}

//
// push
//
void FrameStack::push(const Frame & f)
{
    if (framep >= &frame[NFRAME])
        throw Error(E_CALLNESTEDTOODEEP);

    *++framep = f;
}

//
// reset
//
void FrameStack::reset()
{
    framep = frame;
}


