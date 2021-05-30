/////////////////////////////////////////////////////////////////////////////
//
//	MIDITIME.CPP : MIDI time module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiTime.h"
#include "MidiCommon.h"

/////////////////////////////////////////////////////////////////////////////
DWORD MidiTime::BPMToMicroseconds(DWORD bpm)
{
    if (bpm == 0) {
        return 0;
    }

    // Convert from Beats Per Minute
    // to Microseconds Per Quarter Note
    return 60000000 / bpm;
}

/////////////////////////////////////////////////////////////////////////////
DWORD MidiTime::MicrosecondsToBPM(DWORD microseconds)
{
    if (microseconds == 0) {
        return 0;
    }

    // Convert from Microseconds Per Quarter Note
    // to Beats Per Minute
    return 60000000 / microseconds;
}

/////////////////////////////////////////////////////////////////////////////
DWORD MidiTime::DurationToTicks(Duration duration)
{
    if (duration == EmptyNote) {
        return 0;
    }

    auto result = (DEFAULT_PPQN * 4) / duration;

    return result;
}
