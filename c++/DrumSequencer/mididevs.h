/////////////////////////////////////////////////////////////////////////////
//
//	MIDIDEVS.H : MIDI Devices module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIDEVS_H__
#define __MIDIDEVS_H__

#include "midicommon.h"
#include "mididev.h"

/////////////////////////////////////////////////////////////////////////////
class MidiDevices {
public:
	// Construction / Destruction
	MidiDevices();
	virtual ~MidiDevices();

	// Interface
	virtual UINT Count() const = 0;
	virtual MidiDevice * GetDevice(UINT) const = 0;

protected:
	// Implementation
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIDEVS_H__