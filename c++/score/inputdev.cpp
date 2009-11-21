///////////////////////////////////////////////////////////////////////
//
//	INPUTDEV.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "inputdev.h"

//
// Constructor
//
InputDevice :: InputDevice(LPMIDIINCAPS pmidicaps, UINT id)
{
	wMid = pmidicaps->wMid;
	wPid = pmidicaps->wPid;
	vDriverVersion = pmidicaps->vDriverVersion;
	strcpy(szPname, pmidicaps->szPname);
	dwSupport = pmidicaps->dwSupport;

	m_id = id;
	m_handle = NULL;
}

//
// Destructor
//
InputDevice :: ~InputDevice()
{
	Close();
}

//
// Open
//
MMRESULT InputDevice :: Open()
{
	Close();

	return ::midiInOpen(
	           (HMIDIIN *)&m_handle,
	           m_id,
	           (DWORD)InputDevice::MidiInProc,
	           (DWORD)this,
	           CALLBACK_FUNCTION);
}

//
// Close
//
MMRESULT InputDevice :: Close()
{
	MMRESULT result = MMSYSERR_INVALHANDLE;

	if (*this != NULL) {
		result = ::midiInClose(*this);
		m_handle = NULL;
	}

	return result;
}

//
// GetErrorText
//
CString InputDevice :: GetErrorText(MMRESULT error)
{
	CHAR buffer[MAXERRORLENGTH + 1];
	buffer[0] = '\0';

	::midiInGetErrorText(error, buffer, sizeof(buffer));

	return buffer;
}

//
// MidiInProc
//
void CALLBACK InputDevice :: MidiInProc(
    HMIDIIN /*hMidiIn*/,
    UINT /*wMsg*/,
    DWORD dwInstance,
    DWORD /*dwParam1*/,
    DWORD /*dwParam2*/)
{
	InputDevice * This = (InputDevice *)dwInstance;
	ASSERT(This != NULL);
}

