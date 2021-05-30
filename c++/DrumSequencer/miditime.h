/////////////////////////////////////////////////////////////////////////////
//
//	MIDITIME.H : MIDI time module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDITIME_H__
#define __MIDITIME_H__

/////////////////////////////////////////////////////////////////////////////
// Duration enumeration
enum Duration {
    EmptyNote = 0,
    WholeNote = 1,
    HalfNote = 2,
    QuarterNote = 4,
    EigthNote = 8,
    SixteenthNote = 16,
    ThirtySecondNote = 32
};

/////////////////////////////////////////////////////////////////////////////
namespace MidiTime
{
DWORD BPMToMicroseconds(DWORD bpm);
DWORD MicrosecondsToBPM(DWORD microseconds);
DWORD DurationToTicks(Duration duration);
Duration TicksToDuration(BYTE Ticks);
};

/////////////////////////////////////////////////////////////////////////////
#endif // __MIDITIME_H__
