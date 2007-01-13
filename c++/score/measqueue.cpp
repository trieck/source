///////////////////////////////////////////////////////////////////////
//
//	MEASQUEUE.CPP : queue of measure pointers
//
//	This class implements a queue of measures
//	and is used in implementing a double buffering
//	scheme for streamed ouput
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"

//
// Constructor
//
MeasureQueue :: MeasureQueue()
{
}

//
// Destructor
//
MeasureQueue :: ~MeasureQueue()
{
}

//
// clear
//
void MeasureQueue :: clear()
{
    while (!empty())
        pop();
}
