#include "StdAfx.h"

#include "MidiBuffer.h"
#include "midimessage.h"
#include "miditime.h"

ANON_BEGIN
MIDISHORTEVENT* Tempo(int bpm);
MIDISHORTEVENT* NoteOn(BYTE data, BYTE velocity);
MIDISHORTEVENT* NoteOff(BYTE data);
void PutEvent(LPSTR *ppdata, const MIDISHORTEVENT*);
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
		* sizeof(MIDISHORTEVENT)
		+ sizeof(MIDISHORTEVENT);	// tempo
	
	if (size > m_header.dwBufferLength) {
		Alloc(size);	
	}

	LPSTR pdata = m_header.lpData;
	PutEvent(&pdata, Tempo(100));
	
	m_header.dwBytesRecorded = sizeof(MIDISHORTEVENT);

	BYTE instrument;
	for (int i = 0; i < Sequence::NSUBS; i++) {
		for (int j = 0; j < Sequence::NINSTRUMENTS; j++) {
			instrument = seq.GetInstrument(j);
			if (seq.GetBeat(i, j)) {
				PutEvent(&pdata, NoteOn(instrument, 127));				
			} else {
				PutEvent(&pdata, NoteOn(instrument, 0));				
			}
			m_header.dwBytesRecorded += sizeof(MIDISHORTEVENT);
		}

		for (int j = 0; j < Sequence::NINSTRUMENTS; j++) {
			instrument = seq.GetInstrument(j);
			PutEvent(&pdata, NoteOff(instrument));
			m_header.dwBytesRecorded += sizeof(MIDISHORTEVENT);
		}
	}
}

// Helper functions

ANON_BEGIN

MIDISHORTEVENT* Tempo(int bpm)
{
	static MIDISHORTEVENT event;
	memset(&event, 0, sizeof(MIDISHORTEVENT));

	DWORD microseconds = MidiTime::BPMToMicroseconds(bpm);

	event.delta = 0;
	event.id = 0;
	event.event = TEMPO_CHANGE(microseconds);

	return &event;
}

MIDISHORTEVENT* NoteOn(BYTE data, BYTE velocity)
{
	static MIDISHORTEVENT event;
	memset(&event, 0, sizeof(MIDISHORTEVENT));

	MidiMessage message;
	message.SetData(data);
	message.SetStatus(NOTEON(0));
	message.SetVelocity(velocity);

	event.delta = 0;
	event.id = 0;
	event.event = message;

	return &event;
}

MIDISHORTEVENT* NoteOff(BYTE data)
{
	static MIDISHORTEVENT event;
	memset(&event, 0, sizeof(MIDISHORTEVENT));

	MidiMessage message;
	message.SetData(data);
	message.SetStatus(NOTEOFF(0));
	message.SetVelocity(0);

	event.delta = 20;
	event.id = 0;
	event.event = message;

	return &event;
}

void PutEvent(LPSTR *ppdata, const MIDISHORTEVENT *event)
{
	ASSERT(*ppdata != NULL);
	ASSERT(event != NULL);

	memcpy(*ppdata, event, sizeof(MIDISHORTEVENT));
	*ppdata += sizeof(MIDISHORTEVENT);
}

ANON_END

