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
    WORD GetMid() const
    {
        return wMid;
    }

    WORD GetPid() const
    {
        return wPid;
    }

    MMVERSION GetVersion() const
    {
        return vDriverVersion;
    }

    CString GetProduct () const
    {
        return szPname;
    }

    WORD GetTechnology() const
    {
        return wTechnology;
    }

    WORD GetVoices() const
    {
        return wVoices;
    }

    WORD GetNotes() const
    {
        return wNotes;
    }

    WORD GetChannelMask() const
    {
        return wChannelMask;
    }

    DWORD GetSupport() const
    {
        return dwSupport;
    }

    BOOL IsOpen() const
    {
        return m_handle != nullptr;
    }

    static CString GetErrorText(MMRESULT);

    MMRESULT Open() override = 0;
    MMRESULT Close() override;

    // Implementation
};
/////////////////////////////////////////////////////////////////////////////

#endif // __OUTPUTDEV_H__