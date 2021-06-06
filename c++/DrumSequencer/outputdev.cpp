/////////////////////////////////////////////////////////////////////////////
//
//  OUTPUTDEV.CPP : Output device module
//
//  Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "outputdev.h"

/////////////////////////////////////////////////////////////////////////////
OutputDevice::OutputDevice(LPMIDIOUTCAPS pmidicaps, UINT id) : MIDIOUTCAPS{}
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
CString OutputDevice::GetErrorText(MMRESULT error)
{
    TCHAR buffer[MAXERRORLENGTH + 1]{};

    midiOutGetErrorText(error, buffer, sizeof(buffer));

    return buffer;
}
