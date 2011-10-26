/////////////////////////////////////////////////////////////////////////////
//
//	SEQUENCE.CPP
//
//	MIDI Sequencer class
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

/////////////////////////////////////////////////////////////////////////////
// Sequencer state enumeration
typedef enum {
	Stopped,
	Playing
} SequencerState;

/////////////////////////////////////////////////////////////////////////////
class Sequencer {
public:
	// Construction / Destruction
	Sequencer(MidiStream *);
	virtual ~Sequencer();

	// Interface
	BOOL PlayStaff(const Staff *);
	BOOL PlayMeasure(const Measure *);
	BOOL Stop();

	inline BOOL IsPlaying() const {
		return m_state == Playing;
	}

	// Implementation
protected:
	MidiStream * m_pStream;         // Stream device for playback
	SequencerState m_state;         // Current sequencer state
	MeasureQueue m_MeasureQueue;    // Queue of measures waiting to be played
	DoubleBuffer m_Buffers;         // Double buffers for playback
	UINT m_nBuffers;                // Number of buffers to process
	UINT m_nCurrentBuffer;          // Current buffer

	static void StreamProc(HMIDISTRM, UINT, DWORD, DWORD, DWORD);
};
/////////////////////////////////////////////////////////////////////////////


#endif // __SEQUENCE_H__