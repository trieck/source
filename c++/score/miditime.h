/////////////////////////////////////////////////////////////////////////////
//
//	MIDITIME.H
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDITIME_H__
#define __MIDITIME_H__

#include "common.h"

/////////////////////////////////////////////////////////////////////////////
namespace MidiTime {
DWORD BPMToMicroseconds(DWORD bpm);
DWORD MicrosecondsToBPM(DWORD microseconds);
BYTE DurationToTicks(Duration duration);
Duration TicksToDuration(BYTE Ticks);
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDITIME_H__