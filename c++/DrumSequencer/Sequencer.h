#pragma once

#include "midistream.h"
#include "MidiBuffer.h"
#include "Sequence.h"

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
    MidiStream* m_pStream;
    MidiBuffer m_buffer;
    SequencerState m_state;

    static void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1,
                           DWORD_PTR dwParam2);
};

inline BOOL Sequencer::IsPlaying() const
{
    return m_state == Playing;
}
