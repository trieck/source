/////////////////////////////////////////////////////////////////////////////
//
//  MIDISTREAM.CPP : MIDI stream module
//
//  Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "midistream.h"

#include "LockGuard.h"

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
MMRESULT MidiStream::Open(DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    LockGuard lock(m_cs);

    Close();

    auto result = midiStreamOpen(
        reinterpret_cast<HMIDISTRM*>(&m_handle),
        &m_id,
        1 /* reserved */,
        dwCallback,
        dwInstance,
        fdwOpen);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Close()
{
    LockGuard lock(m_cs);

    MMRESULT result = MMSYSERR_INVALHANDLE;

    if (m_handle != nullptr) {
        (void)Stop();
        result = midiStreamClose(*this);
        m_handle = nullptr;
    }

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Position(LPMMTIME pmmt)
{
    ASSERT(*this != NULL);
    ASSERT(pmmt != NULL);

    LockGuard lock(m_cs);
    auto result = midiStreamPosition(*this, pmmt, sizeof(MMTIME));

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Property(LPBYTE ppropdata, DWORD property)
{
    ASSERT(*this != NULL);
    ASSERT(ppropdata != NULL);

    LockGuard lock(m_cs);

    auto result = midiStreamProperty(*this, ppropdata, property);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Out(LPMIDIHDR pMidiHdr)
{
    ASSERT(*this != NULL);
    ASSERT(pMidiHdr != NULL);

    LockGuard lock(m_cs);

    // Prepare the header
    auto result = midiOutPrepareHeader(static_cast<HMIDIOUT>(m_handle), pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR) {
        return result;
    }

    // Output the header
    result = midiStreamOut(*this, pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR) {
        Unprepare(pMidiHdr);
        return result;
    }

    return MMSYSERR_NOERROR;
}

MMRESULT MidiStream::Unprepare(LPMIDIHDR pMidiHdr)
{
    ASSERT(*this != NULL);
    ASSERT(pMidiHdr != NULL);

    LockGuard lock(m_cs);

    auto result = midiOutUnprepareHeader(static_cast<HMIDIOUT>(m_handle), pMidiHdr, sizeof(MIDIHDR));

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Restart()
{
    ASSERT(*this != NULL);

    LockGuard lock(m_cs);

    auto result = midiStreamRestart(*this);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Stop()
{
    ASSERT(*this != NULL);

    LockGuard lock(m_cs);

    auto result = midiStreamStop(*this);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::ShortMessage(const MidiMessage& message)
{
    ASSERT(*this != NULL);

    LockGuard lock(m_cs);

    auto result = midiOutShortMsg(GetOutputHandle(), message);

    return result;
}
