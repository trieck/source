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

typedef void (*PFNCALLBACK)(HMIDISTRM, UINT, DWORD, DWORD, DWORD);
typedef CList<PFNCALLBACK, PFNCALLBACK> HookChain;

class Sequencer;	// forward declarations

/////////////////////////////////////////////////////////////////////////////
class MidiStream : public OutputDevice {
    friend class OutputDevices;

protected:
    // Construction / Destruction
    MidiStream(LPMIDIOUTCAPS, UINT);
public:
    virtual ~MidiStream();

    // Interface
    virtual MMRESULT Open();
    virtual MMRESULT Close();

    MMRESULT Position(LPMMTIME) const;
    MMRESULT Property(LPBYTE, DWORD) const;
    MMRESULT Out(LPMIDIHDR);
    MMRESULT Restart();
    MMRESULT Stop() const;
    MMRESULT ShortMessage(const MidiMessage &) const;

    BOOL RegisterHook(PFNCALLBACK);
    BOOL RevokeHook(PFNCALLBACK);

    void SetSequencer(Sequencer *pSeq);
    Sequencer *GetSequencer() const;

protected:
    static void CALLBACK MidiStreamProc(
        HMIDISTRM hMidiStream,
        UINT uMsg,
        DWORD dwInstance,
        DWORD dwParam1,
        DWORD dwParam2
    );

    operator HMIDISTRM() const {
        return (HMIDISTRM) m_handle;
    }
    HMIDIOUT GetOutputHandle() const {
        return (HMIDIOUT) m_handle;
    }

    HookChain m_HookChain;
    Sequencer *m_pSequencer;	// sequencer that owns stream
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDISTREAM_H__