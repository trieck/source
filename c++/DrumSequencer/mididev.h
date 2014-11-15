/////////////////////////////////////////////////////////////////////////////
//
//	MIDIDEV.H : MIDI Device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIDEV_H__
#define __MIDIDEV_H__

#include "midicommon.h"

/////////////////////////////////////////////////////////////////////////////
class MidiDevice {
protected:
    // Construction / Destruction
    MidiDevice();
public:
    virtual ~MidiDevice();

    // Interface
    virtual MMRESULT Open() = 0;
    virtual MMRESULT Close() = 0;
    inline UINT GetDeviceID() const {
        return m_id;
    }

protected:
    // Implementation
    HANDLE m_handle;
    UINT m_id;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIDEV_H__