/////////////////////////////////////////////////////////////////////////////
//
//	MIDIDEV.H : MIDI Device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIDEV_H__
#define __MIDIDEV_H__

/////////////////////////////////////////////////////////////////////////////
class MidiDevice
{
protected:
    // Construction / Destruction
    MidiDevice();
public:
    virtual ~MidiDevice() = default;

    // Interface
    virtual MMRESULT Open(DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen) = 0;
    virtual MMRESULT Close() = 0;

    UINT GetDeviceID() const
    {
        return m_id;
    }

protected:
    // Implementation
    HANDLE m_handle;
    UINT m_id;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIDEV_H__
