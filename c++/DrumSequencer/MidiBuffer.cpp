#include "StdAfx.h"

#include "MidiBuffer.h"
#include "midimessage.h"
#include "miditime.h"

ANON_BEGIN
shortEvent* Tempo(int bpm);
shortEvent* NoteOn(BYTE data);
shortEvent* NoteOff(BYTE data);
void PutEvent(LPSTR *ppdata, const shortEvent*);
ANON_END

MidiBuffer::MidiBuffer()
{
	memset(&m_header, 0, sizeof(MIDIHDR));
}

MidiBuffer::~MidiBuffer()
{
	Free();
}

void MidiBuffer::Alloc(UINT nSize)
{
	Free();
	m_header.dwBufferLength = m_header.dwBytesRecorded = nSize;
	m_header.lpData = new CHAR[nSize];
	if (m_header.lpData == NULL)
		AfxThrowMemoryException();
}

void MidiBuffer::Free()
{
	if (m_header.lpData)
		delete [] m_header.lpData;
	memset(&m_header, 0, sizeof(MIDIHDR));
}

void MidiBuffer::Encode(const Sequence & seq)
{
	// Determine the size of the buffer needed
	UINT size = (Sequence::NINSTRUMENTS * Sequence::NSUBS)	/* notes */
		* 2	/* note-on + note-off */
		* sizeof(shortEvent)
		+ sizeof(shortEvent);	// tempo
	
	if (size > m_header.dwBufferLength) {
		Alloc(size);	
	}

	LPSTR pdata = m_header.lpData;
	PutEvent(&pdata, Tempo(100));
	
	BYTE instrument;
	for (int i = 0; i < Sequence::NSUBS; i++) {
		for (int j = 0; j < Sequence::NINSTRUMENTS; j++) {
			instrument = seq.GetInstrument(j);
			if (seq.GetBeat(i, j)) {
				PutEvent(&pdata, NoteOn(instrument));
				PutEvent(&pdata, NoteOff(instrument));
			} else {
				PutEvent(&pdata, NoteOff(instrument));
			}
		}		
	}
}

// Helper functions

ANON_BEGIN

shortEvent* Tempo(int bpm)
{
	static shortEvent event;
	memset(&event, 0, sizeof(shortEvent));

	DWORD microseconds = MidiTime::BPMToMicroseconds(bpm);

	event.delta = 0;
	event.id = 0;
	event.event = TEMPO_CHANGE(microseconds);

	return &event;
}

shortEvent* NoteOn(BYTE data)
{
	static shortEvent event;
	memset(&event, 0, sizeof(shortEvent));

	MidiMessage message;
	message.SetData(data);
	message.SetStatus(NOTEON(0));
	message.SetVelocity(127);

	event.delta = 0;
	event.id = 0;
	event.event = message;

	return &event;
}

shortEvent* NoteOff(BYTE data)
{
	static shortEvent event;
	memset(&event, 0, sizeof(shortEvent));

	MidiMessage message;
	message.SetData(data);
	message.SetStatus(NOTEOFF(0));
	message.SetVelocity(127);

	event.delta = 100;
	event.id = 0;
	event.event = message;

	return &event;
}

void PutEvent(LPSTR *ppdata, const shortEvent *event)
{
	ASSERT(*ppdata != NULL);
	ASSERT(event != NULL);

	memcpy(*ppdata, event, sizeof(shortEvent));
	*ppdata += sizeof(shortEvent);
}

ANON_END

