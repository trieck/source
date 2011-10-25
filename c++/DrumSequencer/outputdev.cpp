/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEV.CPP : Output device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "outputdev.h"

/////////////////////////////////////////////////////////////////////////////
OutputDevice::OutputDevice(LPMIDIOUTCAPS pmidicaps, UINT id)
{
	wMid = pmidicaps->wMid;
	wPid = pmidicaps->wPid;
	vDriverVersion = pmidicaps->vDriverVersion;
	_tcscpy(szPname, pmidicaps->szPname);
	wTechnology = pmidicaps->wTechnology;
	wVoices = pmidicaps->wVoices;
	wNotes = pmidicaps->wNotes;
	wChannelMask = pmidicaps->wChannelMask;
	dwSupport = pmidicaps->dwSupport;
	m_id = id;
}

/////////////////////////////////////////////////////////////////////////////
OutputDevice::~OutputDevice()
{
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT OutputDevice::Close()
{
	// This is a no op
	return MMSYSERR_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
CString OutputDevice::GetErrorText(MMRESULT error)
{
	TCHAR buffer[MAXERRORLENGTH + 1];
	buffer[0] = '\0';

	::midiOutGetErrorText(error, buffer, sizeof(buffer));

	return buffer;
}
