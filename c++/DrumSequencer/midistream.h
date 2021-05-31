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

typedef void (*PFNCALLBACK)(HMIDISTRM, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);
typedef CList<PFNCALLBACK, PFNCALLBACK> HookChain;

class Sequencer; // forward declarations

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
    MMRESULT Open() override;
    MMRESULT Close() override;

    MMRESULT Position(LPMMTIME) const;
    MMRESULT Property(LPBYTE, DWORD) const;
    MMRESULT Out(LPMIDIHDR);
    MMRESULT Restart();
    MMRESULT Stop() const;
    MMRESULT ShortMessage(const MidiMessage&) const;

    BOOL RegisterHook(PFNCALLBACK);
    BOOL RevokeHook(PFNCALLBACK);

    void SetSequencer(Sequencer* pSeq);
    Sequencer* GetSequencer() const;

protected:
    static void CALLBACK MidiStreamProc(
        HMIDISTRM hMidiStream,
        UINT uMsg,
        DWORD_PTR dwInstance,
        DWORD_PTR dwParam1,
        DWORD_PTR dwParam2
    );

    operator HMIDISTRM() const
    {
        return static_cast<HMIDISTRM>(m_handle);
    }

    HMIDIOUT GetOutputHandle() const
    {
        return static_cast<HMIDIOUT>(m_handle);
    }

    HookChain m_HookChain;
    Sequencer* m_pSequencer; // sequencer that owns this stream
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MIDISTREAM_H__
