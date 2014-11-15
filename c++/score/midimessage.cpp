/////////////////////////////////////////////////////////////////////////////
//
//	MIDIMESSAGE.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiMessage.h"

//
// Constructor
//
MidiMessage::MidiMessage()
{
    m_velocity = 0;
    m_data = 0;
    m_status = 0;
}

//
// Constructor
//
MidiMessage::MidiMessage(DWORD data)
{
    m_velocity = LOBYTE(HIWORD(data));
    m_data = HIBYTE(LOWORD(data));
    m_status = LOBYTE(LOWORD(data));
}

//
// Destructor
//
MidiMessage::~MidiMessage()
{
}

//
// operator DWORD
//
MidiMessage::operator DWORD() const
{
    DWORD data = m_velocity << 16;  // velocity
    data |= m_data << 8;            // midi data
    data |= m_status;               // status

    return data;

}