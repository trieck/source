/////////////////////////////////////////////////////////////////////////////
//
//	MIDISTREAM.H : MIDI stream module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDISTREAM_H__
#define __MIDISTREAM_H__

#include "OutputDev.h"
#include "MidiMessage.h"

/////////////////////////////////////////////////////////////////////////////
class MidiStream : public OutputDevice
{
    friend class OutputDevices;

protected:
    // Construction / Destruction
    MidiStream(LPMIDIOUTCAPS, UINT);
public:
    virtual ~MidiStream();

    // Interface
    MMRESULT Open(DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen) override;
    MMRESULT Close() override;

    MMRESULT Position(LPMMTIME);
    MMRESULT Property(LPBYTE, DWORD);
    MMRESULT Out(LPMIDIHDR);
    MMRESULT Unprepare(LPMIDIHDR);
    MMRESULT Restart();
    MMRESULT Reset();
    MMRESULT Stop();
    MMRESULT ShortMessage(const MidiMessage&);

    operator HMIDISTRM() const
    {
        return static_cast<HMIDISTRM>(m_handle);
    }

    HMIDIOUT GetOutputHandle() const
    {
        return static_cast<HMIDIOUT>(m_handle);
    }

private:
    CCriticalSection m_cs;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDISTREAM_H__
