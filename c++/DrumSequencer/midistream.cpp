/////////////////////////////////////////////////////////////////////////////
//
//  MIDISTREAM.CPP : MIDI stream module
//
//  Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "midistream.h"

/////////////////////////////////////////////////////////////////////////////
MidiStream::MidiStream(LPMIDIOUTCAPS pmidicaps, UINT id)
    : OutputDevice(pmidicaps, id)
{
}

/////////////////////////////////////////////////////////////////////////////
MidiStream::~MidiStream()
{
    Close();
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Open(MidiCallback callback, LPVOID dwParam)
{
    Close();

    return midiStreamOpen(
        reinterpret_cast<HMIDISTRM*>(&m_handle),
        &m_id,
        1 /* reserved */,
        reinterpret_cast<DWORD_PTR>(callback),
        reinterpret_cast<DWORD_PTR>(dwParam),
        CALLBACK_FUNCTION);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Close()
{
    MMRESULT result = MMSYSERR_INVALHANDLE;

    if (m_handle != nullptr) {
        (void)Stop();
        result = midiStreamClose(*this);
        m_handle = nullptr;
    }

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Position(LPMMTIME pmmt) const
{
    ASSERT(*this != NULL);
    ASSERT(pmmt != NULL);

    return midiStreamPosition(*this, pmmt, sizeof(MMTIME));
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Property(LPBYTE ppropdata, DWORD property) const
{
    ASSERT(*this != NULL);
    ASSERT(ppropdata != NULL);

    return midiStreamProperty(*this, ppropdata, property);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Out(LPMIDIHDR pMidiHdr)
{
    ASSERT(*this != NULL);
    ASSERT(pMidiHdr != NULL);

    // Prepare the header
    auto result = midiOutPrepareHeader(static_cast<HMIDIOUT>(m_handle), pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR) {
        return result;
    }

    // Output the header
    result = midiStreamOut(*this, pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR) {
        midiOutUnprepareHeader(static_cast<HMIDIOUT>(m_handle), pMidiHdr, sizeof(MIDIHDR));
        return result;
    }

    // The midi header will be unprepared in the MidiStreamProc callback function

    return MMSYSERR_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Restart()
{
    ASSERT(*this != NULL);

    return midiStreamRestart(*this);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Stop() const
{
    ASSERT(*this != NULL);

    return midiStreamStop(*this);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::ShortMessage(const MidiMessage& message) const
{
    ASSERT(*this != NULL);

    return midiOutShortMsg(GetOutputHandle(), message);
}
