/////////////////////////////////////////////////////////////////////////////
//
//	MIDIMESSAGE.CPP : MIDI message module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiMessage.h"

/////////////////////////////////////////////////////////////////////////////
MidiMessage::MidiMessage()
{
    m_velocity = 0;
    m_data = 0;
    m_status = 0;
}

/////////////////////////////////////////////////////////////////////////////
MidiMessage::MidiMessage(DWORD data)
{
    m_velocity = LOBYTE(HIWORD(data));
    m_data = HIBYTE(LOWORD(data));
    m_status = LOBYTE(LOWORD(data));
}

/////////////////////////////////////////////////////////////////////////////
MidiMessage::~MidiMessage()
{
}

/////////////////////////////////////////////////////////////////////////////
MidiMessage::operator DWORD() const
{
    DWORD data = m_velocity << 16;  // velocity
    data |= m_data << 8;            // midi data
    data |= m_status;               // status

    return data;
}
