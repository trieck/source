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

private:
    MidiBuffer m_front, m_back;
    MidiStream* m_pStream;
    SequencerState m_state;
    UINT m_completed = 0;

    static void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1,
                           DWORD_PTR dwParam2);
};

inline BOOL Sequencer::IsPlaying() const
{
    return m_state == Playing;
}
