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
    MMRESULT Open(MidiCallback callback, LPVOID dwParam = nullptr) override;
    MMRESULT Close() override;

    MMRESULT Position(LPMMTIME) const;
    MMRESULT Property(LPBYTE, DWORD) const;
    MMRESULT Out(LPMIDIHDR);
    MMRESULT Restart();
    MMRESULT Stop() const;
    MMRESULT ShortMessage(const MidiMessage&) const;

protected:
    operator HMIDISTRM() const
    {
        return static_cast<HMIDISTRM>(m_handle);
    }

    HMIDIOUT GetOutputHandle() const
    {
        return static_cast<HMIDIOUT>(m_handle);
    }
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDISTREAM_H__
