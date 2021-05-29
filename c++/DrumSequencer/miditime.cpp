/////////////////////////////////////////////////////////////////////////////
//
//	MIDITIME.CPP : MIDI time module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiTime.h"
#include "MidiCommon.h"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
DWORD MidiTime::BPMToMicroseconds(DWORD bpm)
{
    // Convert from Beats Per Minute
    // to Microseconds Per Quarter Note

    const auto result = float(60000000) / bpm;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
DWORD MidiTime::MicrosecondsToBPM(DWORD microseconds)
{
    // Convert from Microseconds Per Quarter Note
    // to Beats Per Minute
    return (DWORD)(1 / (microseconds / 1000000 / 60));
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

