#pragma once

#include "midistream.h"
#include "Sequence.h"
#include "MidiBuffer.h"

enum SequencerState
{
    Stopped,
    Playing
};

class Sequencer
{
public:
    Sequencer();
    ~Sequencer();

    BOOL Initialize();
    BOOL IsPlaying() const;

    void Close() const;
    BOOL Play(const Sequence& sequence);
    BOOL Stop();

    short Tempo() const;
    void SetTempo(short bpm);
    bool HasStream();

private:
    MidiBuffer m_front, m_back;
    CEvent m_threadEvent, m_shutdownEvent, m_doneEvent;
    CWinThread* m_workerThread;
    MidiStream* m_pStream;
    SequencerState m_state;

    static void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR pMidiHdr,
                           DWORD_PTR dwParam2);

    static UINT __cdecl ThreadProc(LPVOID pParam);
};

inline BOOL Sequencer::IsPlaying() const
{
    return m_state == Playing;
}
