/////////////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEV.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "outputdev.h"

//
// Constructor
//
OutputDevice::OutputDevice(LPMIDIOUTCAPS pmidicaps, UINT id)
{
    wMid = pmidicaps->wMid;
    wPid = pmidicaps->wPid;
    vDriverVersion = pmidicaps->vDriverVersion;
    strcpy(szPname, pmidicaps->szPname);
    wTechnology = pmidicaps->wTechnology;
    wVoices = pmidicaps->wVoices;
    wNotes = pmidicaps->wNotes;
    wChannelMask = pmidicaps->wChannelMask;
    dwSupport = pmidicaps->dwSupport;
    m_id = id;
}

//
// Destructor
//
OutputDevice::~OutputDevice()
{
}

//
// Close
//
MMRESULT OutputDevice::Close()
{
    // This is a no op
    return MMSYSERR_NOERROR;
}

//
// GetErrorText
//
CString OutputDevice::GetErrorText(MMRESULT error)
{
    CHAR buffer[MAXERRORLENGTH + 1];
    buffer[0] = '\0';

    ::midiOutGetErrorText(error, buffer, sizeof(buffer));

    return buffer;

}