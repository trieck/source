/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEV.H : MIDI output device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __OUTPUTDEV_H__
#define __OUTPUTDEV_H__

#include "mididev.h"

/////////////////////////////////////////////////////////////////////////////
class OutputDevice : public MidiDevice, private MIDIOUTCAPS
{
    friend class OutputDevices;

protected:
    // Construction / Destruction
    OutputDevice(LPMIDIOUTCAPS, UINT);
public:
    virtual ~OutputDevice();

    // Interface
    inline WORD GetMid() const
    {
        return wMid;
    }
    inline WORD GetPid() const
    {
        return wPid;
    }
    inline MMVERSION GetVersion() const
    {
        return vDriverVersion;
    }
    inline CString GetProduct () const
    {
        return szPname;
    }
    inline WORD GetTechnology() const
    {
        return wTechnology;
    }
    inline WORD GetVoices() const
    {
        return wVoices;
    }
    inline WORD GetNotes() const
    {
        return wNotes;
    }
    inline WORD GetChannelMask() const
    {
        return wChannelMask;
    }
    inline DWORD GetSupport() const
    {
        return dwSupport;
    }
    inline BOOL IsOpen() const
    {
        return m_handle != NULL;
    }

    static CString GetErrorText(MMRESULT);

    virtual MMRESULT Open() = 0;
    virtual MMRESULT Close();

    // Implementation
protected:
};
/////////////////////////////////////////////////////////////////////////////

#endif // __OUTPUTDEV_H__