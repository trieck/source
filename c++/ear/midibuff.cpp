///////////////////////////////////////////////////////////////////////
//
//	MIDIBUFF.CPP : midi data buffer
//
//	Copyright (c) 2000 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"
#include "midibuff.h"

extern int defaultVelocity;
extern int defaultChannel;

static shortEvent* Tempo(int bpm);
static shortEvent* NoteOn(BYTE data);
static shortEvent* NoteOff(BYTE data);
static void putevent(LPSTR *ppdata, const shortEvent*);

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
    UINT size = (sizeof(shortEvent) * 2 * 2)	// note data
                + sizeof(shortEvent);					// Tempo Data;

    m_header.dwBufferLength = m_header.dwBytesRecorded = size;
    m_header.lpData = new CHAR[size];
}

void MidiBuffer::Free()
{
    if (m_header.lpData)
        delete [] m_header.lpData;
    memset(&m_header, 0, sizeof(MIDIHDR));
}

void MidiBuffer::Transform(BYTE note1, BYTE note2)
{
    LPSTR pdata = m_header.lpData;

    putevent(&pdata, Tempo(100));
    putevent(&pdata, NoteOn(note1));
    putevent(&pdata, NoteOff(note1));
    putevent(&pdata, NoteOn(note2));
    putevent(&pdata, NoteOff(note2));
}

// Helper functions

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
    message.SetStatus(NOTEON(defaultChannel));
    message.SetVelocity(defaultVelocity);

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
    message.SetStatus(NOTEOFF(defaultChannel));
    message.SetVelocity(defaultVelocity);

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
