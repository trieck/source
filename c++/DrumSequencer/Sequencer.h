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
	
	static void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, 
		DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
};

inline BOOL Sequencer::IsPlaying() const {
	return m_state == Playing;
}
