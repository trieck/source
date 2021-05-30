/////////////////////////////////////////////////////////////////////////////
//
//	MIDISTREAM.CPP : MIDI stream module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "midistream.h"

/////////////////////////////////////////////////////////////////////////////
MidiStream::MidiStream(LPMIDIOUTCAPS pmidicaps, UINT id)
    : OutputDevice(pmidicaps, id), m_pSequencer(nullptr)
{
}

/////////////////////////////////////////////////////////////////////////////
MidiStream::~MidiStream()
{
    Close();
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Open()
{
    Close();

    return midiStreamOpen(
        reinterpret_cast<HMIDISTRM*>(&m_handle),
        &m_id,
        1 /* reserved */,
        reinterpret_cast<DWORD_PTR>(MidiStreamProc),
        reinterpret_cast<DWORD_PTR>(this),
        CALLBACK_FUNCTION);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Close()
{
    MMRESULT result = MMSYSERR_INVALHANDLE;

    if (m_handle != nullptr) {
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
    MMRESULT result = midiOutPrepareHeader(static_cast<HMIDIOUT>(m_handle), pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR)
        return result;

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
void MidiStream::MidiStreamProc(HMIDISTRM hMidiStream, UINT uMsg, 
    DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    auto This = reinterpret_cast<MidiStream*>(dwInstance);
    ASSERT(This != NULL);

    // Iterate through the hook chain
    auto pos = This->m_HookChain.GetHeadPosition();
    while (pos != nullptr) {
        const auto pfnCallBack = This->m_HookChain.GetNext(pos);
        ASSERT(pfnCallBack != NULL);

        (*pfnCallBack)(hMidiStream, uMsg, dwInstance, dwParam1, dwParam2);
    }
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::ShortMessage(const MidiMessage& message) const
{
    ASSERT(*this != NULL);

    return midiOutShortMsg(GetOutputHandle(), message);
}

/////////////////////////////////////////////////////////////////////////////
BOOL MidiStream::RegisterHook(PFNCALLBACK pfnCallBack)
{
    ASSERT(pfnCallBack != NULL);
    ASSERT_VALID(&m_HookChain);

    // Don't allow duplicates in the hook chain
    if (m_HookChain.Find(pfnCallBack) != nullptr)
        return FALSE;

    return m_HookChain.AddTail(pfnCallBack) != nullptr;
}

/////////////////////////////////////////////////////////////////////////////
BOOL MidiStream::RevokeHook(PFNCALLBACK pfnCallBack)
{
    ASSERT(pfnCallBack != NULL);
    ASSERT_VALID(&m_HookChain);

    auto pos = m_HookChain.GetHeadPosition();
    while (pos != nullptr) {
        if (m_HookChain.GetAt(pos) == pfnCallBack) {
            m_HookChain.RemoveAt(pos);
            return TRUE;
        }
        m_HookChain.GetNext(pos);
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
void MidiStream::SetSequencer(Sequencer* pSeq)
{
    m_pSequencer = pSeq;
}

/////////////////////////////////////////////////////////////////////////////
Sequencer* MidiStream::GetSequencer() const
{
    return m_pSequencer;
}
