/////////////////////////////////////////////////////////////////////////////
//
//	MIDIOUT.H : MIDI Output device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIOUT_H__
#define __MIDIOUT_H__

#include "OutputDev.h"
#include "MidiMessage.h"

/////////////////////////////////////////////////////////////////////////////
class MidiOutput : public OutputDevice
{
    friend class OutputDevices;

protected:
    // Construction / Destruction
    MidiOutput(LPMIDIOUTCAPS, UINT);
public:
    virtual ~MidiOutput();

    MMRESULT Open() override;
    MMRESULT Close() override;

    MMRESULT ShortMessage(const MidiMessage &);
    MMRESULT LongMessage(LPSTR, UINT);
    MMRESULT GetVolume(LPDWORD);
    MMRESULT SetVolume(DWORD);

    operator HMIDIOUT() const
    {
        return static_cast<HMIDIOUT>(m_handle);
    }

protected:
    // Implementation

    static void CALLBACK MidiOutProc(
        HMIDIOUT hMidiOut,
        UINT wMsg,
        DWORD_PTR dwInstance,
        DWORD_PTR dwParam1,
        DWORD_PTR dwParam2);
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIOUT_H__