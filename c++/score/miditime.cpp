/////////////////////////////////////////////////////////////////////////////
//
//	MIDITIME.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiTime.h"
#include "MidiCommon.h"
#include <math.h>

//
// BPMToMicroseconds
//
DWORD MidiTime::BPMToMicroseconds(DWORD bpm)
{
    // Convert from Beats Per Minute
    // to Microseconds Per Quarter Note
    return DWORD(60000000 / float(bpm));
}

//
// MicrosecondsToBPM
//
DWORD MidiTime::MicrosecondsToBPM(DWORD microseconds)
{
    // Convert from Microseconds Per Quarter Note
    // to Beats Per Minute
    return (DWORD)(1 / (microseconds / pow(float(10), 6) / 60));
}

//
// DurationToTicks
//
BYTE MidiTime::DurationToTicks(Duration duration)
{
    return BYTE(DEFAULT_PPQN * 4 * float(1) / duration);
}

//
// TicksToDuration
//
//Duration TicksToDuration(BYTE Ticks)
//{

//}