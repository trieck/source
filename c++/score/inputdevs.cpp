///////////////////////////////////////////////////////////////////////
//
//	INPUTDEVS.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "inputdevs.h"
#include "inputdev.h"

//
// Constructor
//
InputDevices :: InputDevices()
{
}

//
// Destructor
//
InputDevices :: ~InputDevices()
{
}

//
// Count
//
UINT InputDevices :: Count() const
{
	return ::midiInGetNumDevs();
}

//
// GetDevice
//
MidiDevice * InputDevices :: GetDevice(UINT device) const
{
	MIDIINCAPS caps;
	MMRESULT result = ::midiInGetDevCaps(device, &caps, sizeof(MIDIINCAPS));
	if (result != MMSYSERR_NOERROR)
		return NULL;

	return new InputDevice(&caps, device);

}