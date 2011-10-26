/////////////////////////////////////////////////////////////////////////////
//
//	MIDIOUT.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiOut.h"

//
// Constructor
//
MidiOutput::MidiOutput(LPMIDIOUTCAPS pmidicaps, UINT id)
		: OutputDevice(pmidicaps, id)
{
}

//
// Destructor
//
MidiOutput::~MidiOutput()
{
	Close();
}

//
// Open
//
MMRESULT MidiOutput::Open()
{
	Close();

	return ::midiOutOpen(
	           (HMIDIOUT*)&m_handle,
	           m_id,
	           (DWORD)MidiOutput::MidiOutProc,
	           (DWORD)this,
	           CALLBACK_FUNCTION);
}

//
// Close
//
MMRESULT MidiOutput::Close()
{
	MMRESULT result = MMSYSERR_INVALHANDLE;

	if (m_handle != NULL) {
		result = ::midiOutClose(*this);
		m_handle = NULL;
	}

	return result;
}

//
// MidiOutProc
//
void CALLBACK MidiOutput::MidiOutProc(
    HMIDIOUT hMidiOut,
    UINT wMsg,
    DWORD dwInstance,
    DWORD dwParam1,
    DWORD /*dwParam2*/)
{
	OutputDevice * This = (OutputDevice *)dwInstance;
	ASSERT(This != NULL);

	switch (wMsg) {
	case MOM_DONE:
		// Unprepare the midi header
		::midiOutUnprepareHeader(hMidiOut, (LPMIDIHDR)dwParam1, sizeof(MIDIHDR));
		break;
	default:
		break;
	}
}

//
// ShortMessage
//
MMRESULT MidiOutput::ShortMessage(const MidiMessage & message)
{
	ASSERT(*this != NULL);

	return ::midiOutShortMsg(*this, message);
}

//
// LongMessage
//
MMRESULT MidiOutput::LongMessage(LPSTR pdata, UINT cbSize)
{
	// BUGBUG -- not implemented

	return MMSYSERR_NOERROR;
}

//
// GetVolume
//
MMRESULT MidiOutput::GetVolume (LPDWORD pVolume)
{
	ASSERT(*this != NULL);
	ASSERT(pVolume != NULL);

	return ::midiOutGetVolume(*this, pVolume);
}

//
// SetVolume
//
MMRESULT MidiOutput::SetVolume(DWORD volume)
{
	ASSERT(*this != NULL);

	return ::midiOutSetVolume(*this, volume);
}


