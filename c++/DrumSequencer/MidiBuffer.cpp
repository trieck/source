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
	Alloc();
}

MidiBuffer::~MidiBuffer()
{
	Free();
}

void MidiBuffer::Alloc()
{
	Free();

	// Determine the size of the buffer needed
	UINT size = 0;

	m_header.dwBufferLength = m_header.dwBytesRecorded = size;
	m_header.lpData = new CHAR[size];
}

void MidiBuffer::Free()
{
	if (m_header.lpData)
		delete [] m_header.lpData;
	memset(&m_header, 0, sizeof(MIDIHDR));
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

void putevent(LPSTR *ppdata, const shortEvent *event)
{
	ASSERT(*ppdata != NULL);
	ASSERT(event != NULL);

	memcpy(*ppdata, event, sizeof(shortEvent));
	*ppdata += sizeof(shortEvent);
}

ANON_END
