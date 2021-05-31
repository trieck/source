/////////////////////////////////////////////////////////////////////////////
//
//	MIDIDEVS.H : MIDI Devices module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIDEVS_H__
#define __MIDIDEVS_H__

#include "StdAfx.h"
#include "mididev.h"

/////////////////////////////////////////////////////////////////////////////
class MidiDevices
{
public:
    // Construction / Destruction
    MidiDevices() = default;
    virtual ~MidiDevices() = default;

    // Interface
    virtual UINT Count() const = 0;
    virtual MidiDevice* GetDevice(UINT) const = 0;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIDEVS_H__
