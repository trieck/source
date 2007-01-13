///////////////////////////////////////////////////////////////////////
//
//	MIDIDEV.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "mididev.h"

//
// Constructor
//
MidiDevice :: MidiDevice()
{
    m_handle = NULL;
    m_id = 0;
}

//
// Destructor
//
MidiDevice :: ~MidiDevice()
{
}
