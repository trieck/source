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

    void Close();
    BOOL Play(const Sequence& sequence);
    BOOL OutFront(const Sequence& sequence);
    BOOL OutBack(const Sequence& sequence);
    BOOL Stop();

    short Tempo() const;
    void SetTempo(short bpm);
    bool HasStream();

private:
    CCriticalSection m_cs;
    CEvent m_threadEvent;
    CWinThread* m_workerThread;
    MidiBuffer m_front, m_back;
    MidiStream* m_pStream;
    SequencerState m_state;

    static UINT __cdecl ThreadProc(LPVOID pParam);
};

inline BOOL Sequencer::IsPlaying() const
{
    return m_state == Playing;
}
