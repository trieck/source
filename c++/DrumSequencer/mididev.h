/////////////////////////////////////////////////////////////////////////////
//
//	MIDIDEV.H : MIDI Device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIDEV_H__
#define __MIDIDEV_H__

using MidiCallback = void (*)(HMIDISTRM, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);

/////////////////////////////////////////////////////////////////////////////
class MidiDevice
{
protected:
    // Construction / Destruction
    MidiDevice();
public:
    virtual ~MidiDevice() = default;

    // Interface
    virtual MMRESULT Open(MidiCallback, LPVOID = nullptr) = 0;
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
