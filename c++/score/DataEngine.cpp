/////////////////////////////////////////////////////////////////////////////
//
//	DATAENGINE.CPP
//
//	This class is responsible for converting
//	a high level abstract measure object
//	into raw MIDI data suitable for playback
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "baseinc.h"
#include "neptune.h"

extern BYTE defaultVelocity;
extern BYTE defaultChannel;

//
// Constructor
//
DataEngine::DataEngine(const Measure * pMeasure)
{
	ASSERT(pMeasure != NULL);
	m_pData = NULL;
	xform(pMeasure);
}

//
// Destructor
//
DataEngine::~DataEngine()
{
	FREEMIDIDATA(m_pData);
}

//
// xform
//
BOOL DataEngine::xform(const Measure * pMeasure)
{
	ASSERT(pMeasure != NULL);

	if (!AllocBuffer(pMeasure))
		return FALSE;

	ASSERT(m_pData != NULL);
	ASSERT(m_pData->lpData != NULL);
	ASSERT(m_pData->dwBufferLength != 0);

	// Set the tempo
	SetTempo(pMeasure->GetTempo());

	int eventOffset = sizeof(shortEvent);
	PSTR pdata = m_pData->lpData + eventOffset;

	const Beats * pBeats = pMeasure->GetBeats();
	ASSERT_VALID(pBeats);

	POSITION pos = pBeats->GetHeadPosition();
	while (pos) {
		NoteList * pNoteList = pBeats->GetNext(pos);
		ASSERT_VALID(pNoteList);

		// Build the note on events
		POSITION notepos = pNoteList->GetHeadPosition();
		for (; notepos != NULL; pdata += eventOffset) {
			Note * pNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNote);

			Neptune::AfxCopyMemory(pdata, NoteOn(pNote), sizeof(shortEvent));
		}

		// Build the note off events
		notepos = pNoteList->GetHeadPosition();
		for (; notepos != NULL; pdata += eventOffset) {
			Note * pNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNote);

			Neptune::AfxCopyMemory(pdata,
			                       NoteOff(pNote, pNote == pNoteList->GetHead()),
			                       sizeof(shortEvent));
		}

	}

	return TRUE;
}

//
// NoteOn
//
shortEvent * DataEngine::NoteOn(const Note * pNote) const
{
	// Build a note on event
	static shortEvent event;
	memset(&event, 0, sizeof(shortEvent));

	ASSERT(pNote != NULL);

	MidiMessage message;
	message.SetData(pNote->GetData());
	message.SetStatus(NOTEON(defaultChannel));
	message.SetVelocity(defaultVelocity);

	event.delta = 0;
	event.id = 0;
	event.event = message;

	return &event;
}

//
// NoteOff
//
shortEvent * DataEngine::NoteOff(const Note * pNote, BOOL delay) const
{
	static shortEvent event;
	memset(&event, 0, sizeof(shortEvent));

	ASSERT(pNote != NULL);

	MidiMessage message;
	message.SetData(pNote->GetData());
	message.SetStatus(NOTEOFF(defaultChannel));
	message.SetVelocity(defaultVelocity);

	event.delta = delay ? MidiTime::DurationToTicks(pNote->GetDuration()) : 0;
	event.id = 0;
	event.event = message;

	return &event;
}

//
// SetTempo
//
void DataEngine::SetTempo(int bpm)
{
	ASSERT(m_pData->lpData != NULL);

	DWORD microseconds = MidiTime::BPMToMicroseconds(bpm);

	shortEvent event;
	event.delta = 0;
	event.id = 0;
	event.event = TEMPO_CHANGE(microseconds);

	Neptune::AfxCopyMemory(m_pData->lpData, &event, sizeof(shortEvent));
}

//
// AllocBuffer
//
BOOL DataEngine::AllocBuffer(const Measure * pMeasure)
{
	ASSERT_VALID(pMeasure);

	FREEMIDIDATA(m_pData);

	m_pData = new MIDIHDR;
	if (m_pData == NULL)
		return FALSE;

	memset(m_pData, 0, sizeof(MIDIHDR));

	// Determine the size of the buffer needed
	// and allocate a DWORD array based on this size
	UINT size =
	    (sizeof(shortEvent) * 2 * pMeasure->GetNoteCount()) // Note Data
	    + sizeof(shortEvent); // Tempo Data

	m_pData->dwBufferLength = m_pData->dwBytesRecorded = size;
	m_pData->lpData = new CHAR[size];
	if (m_pData->lpData == NULL) {
		FREEMIDIDATA(m_pData)
		return FALSE;
	}

	return TRUE;

}