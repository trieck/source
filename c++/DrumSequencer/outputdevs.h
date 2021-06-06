/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEVS.H : MIDI output devices module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __OUTPUTDEVS_H__
#define __OUTPUTDEVS_H__

#include "mididevs.h"

/////////////////////////////////////////////////////////////////////////////
class OutputDevices : public MidiDevices
{
public:
    // Construction / Destruction
    OutputDevices() = default;
    virtual ~OutputDevices() = default;

    // Interface
    UINT Count() const override;
    MidiDevice* GetDevice(UINT) const override;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __OUTPUTDEVS_H__
