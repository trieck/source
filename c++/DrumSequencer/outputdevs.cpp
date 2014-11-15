/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEVS.CPP : output devices module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "outputdevs.h"
#include "MidiOut.h"
#include "MidiStream.h"

/////////////////////////////////////////////////////////////////////////////
OutputDevices::OutputDevices()
{
}

/////////////////////////////////////////////////////////////////////////////
OutputDevices::~OutputDevices()
{
}

/////////////////////////////////////////////////////////////////////////////
UINT OutputDevices::Count() const
{
    return ::midiOutGetNumDevs();
}

/////////////////////////////////////////////////////////////////////////////
MidiDevice * OutputDevices::GetDevice(UINT device) const
{
    MIDIOUTCAPS caps;
    MMRESULT result = ::midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));
    if (result != MMSYSERR_NOERROR)
        return NULL;

    return new MidiOutput(&caps, device);
}

/////////////////////////////////////////////////////////////////////////////
MidiDevice * OutputDevices::GetStream(UINT device) const
{
    MIDIOUTCAPS caps;
    MMRESULT result = ::midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));
    if (result != MMSYSERR_NOERROR)
        return NULL;

    return new MidiStream(&caps, device);
}
