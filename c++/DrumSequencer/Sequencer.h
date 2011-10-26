#pragma once

#include "midistream.h"
#include "MidiBuffer.h"
#include "Sequence.h"

typedef enum SequencerState {
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
	BOOL Play(const Sequence &sequence);
	BOOL Stop();

private:
	MidiStream *m_pStream;
	MidiBuffer m_buffer;
	SequencerState m_state;
};

inline BOOL Sequencer::IsPlaying() const {
	return m_state == Playing;
}
