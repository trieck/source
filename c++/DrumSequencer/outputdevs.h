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
class OutputDevices : public MidiDevices {
public:
    // Construction / Destruction
    OutputDevices();
    virtual ~OutputDevices();

    // Interface
    UINT Count() const;
    MidiDevice * GetDevice(UINT) const;
    MidiDevice * GetStream(UINT) const;

protected:
    // Implementation
};
/////////////////////////////////////////////////////////////////////////////

#endif // __OUTPUTDEVS_H__