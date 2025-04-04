/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEVS.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "outputdevs.h"
#include "MidiOut.h"
#include "MidiStream.h"

//
// Constructor
//
OutputDevices::OutputDevices()
{
}

//
// Destructor
//
OutputDevices::~OutputDevices()
{
}

//
// Count
//
UINT OutputDevices::Count() const
{
    return ::midiOutGetNumDevs();
}

//
// GetDevice
//
MidiDevice * OutputDevices::GetDevice(UINT device) const
{
    MIDIOUTCAPS caps;
    MMRESULT result = ::midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));
    if (result != MMSYSERR_NOERROR)
        return NULL;

    return new MidiOutput(&caps, device);
}

//
// GetStream
//
MidiDevice * OutputDevices::GetStream(UINT device) const
{
    MIDIOUTCAPS caps;
    MMRESULT result = ::midiOutGetDevCaps(device, &caps, sizeof(MIDIOUTCAPS));
    if (result != MMSYSERR_NOERROR)
        return NULL;

    return new MidiStream(&caps, device);

}