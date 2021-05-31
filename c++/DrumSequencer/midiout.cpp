/////////////////////////////////////////////////////////////////////////////
//
//	MIDIOUT.CPP : MIDI output module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "MidiOut.h"

/////////////////////////////////////////////////////////////////////////////
MidiOutput::MidiOutput(LPMIDIOUTCAPS pmidicaps, UINT id)
    : OutputDevice(pmidicaps, id)
{
}

/////////////////////////////////////////////////////////////////////////////
MidiOutput::~MidiOutput()
{
    Close();
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiOutput::Open()
{
    Close();

    return ::midiOutOpen(
        reinterpret_cast<HMIDIOUT*>(&m_handle),
        m_id,
        reinterpret_cast<DWORD_PTR>(MidiOutProc),
        reinterpret_cast<DWORD_PTR>(this),
        CALLBACK_FUNCTION);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiOutput::Close()
{
    MMRESULT result = MMSYSERR_INVALHANDLE;

    if (m_handle != nullptr) {
        result = midiOutClose(*this);
        m_handle = nullptr;
    }

    return result;
}

/////////////////////////////////////////////////////////////////////////////
void MidiOutput::MidiOutProc(HMIDIOUT hMidiOut,
                             UINT wMsg,
                             DWORD_PTR dwInstance,
                             DWORD_PTR dwParam1,
                             DWORD_PTR /*dwParam2*/)
{
    const auto This = reinterpret_cast<OutputDevice*>(dwInstance);
    ASSERT(This != NULL);

    if (wMsg == MOM_DONE) {
        // Unprepare the midi header
        midiOutUnprepareHeader(hMidiOut, reinterpret_cast<LPMIDIHDR>(dwParam1), sizeof(MIDIHDR));
    }
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiOutput::ShortMessage(const MidiMessage& message)
{
    ASSERT(*this != NULL);

    return midiOutShortMsg(*this, message);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiOutput::LongMessage(LPSTR pdata, UINT cbSize)
{
    // BUGBUG -- not implemented

    return MMSYSERR_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiOutput::GetVolume(LPDWORD pVolume)
{
    ASSERT(*this != NULL);
    ASSERT(pVolume != NULL);

    return midiOutGetVolume(*this, pVolume);
}

//
// SetVolume
//
MMRESULT MidiOutput::SetVolume(DWORD volume)
{
    ASSERT(*this != NULL);

    return midiOutSetVolume(*this, volume);
}
