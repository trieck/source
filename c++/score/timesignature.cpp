///////////////////////////////////////////////////////////////////////
//
//	TIMESIGNATURE.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "TimeSignature.h"

//
// Constructor
//
TimeSignature :: TimeSignature()
{
	m_beats = 0;
	m_length = EmptyLength;
}

//
// Constructor
//
TimeSignature :: TimeSignature(int beats, BeatLength length)
{
	m_beats = beats;
	m_length = length;
}

//
// Destructor
//
TimeSignature :: ~TimeSignature()
{
}

//
// SetTimeSignature
//
void TimeSignature :: SetTimeSignature(int beats, BeatLength length)
{
    m_beats = beats;
    m_length = length;
}

//
// GetTimeSignature
//
void TimeSignature :: GetTimeSignature(int & beats, BeatLength & length) const
{
    beats = m_beats;
    length = m_length;
}

//
// GetDuration
//
float TimeSignature :: GetDuration() const
{
    if (m_length == EmptyLength)
        return 0;

    return m_beats * float(1) / m_length;
}