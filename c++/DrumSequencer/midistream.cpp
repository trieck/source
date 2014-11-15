/////////////////////////////////////////////////////////////////////////////
//
//	MIDISTREAM.CPP : MIDI stream module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "midistream.h"

/////////////////////////////////////////////////////////////////////////////
MidiStream::MidiStream(LPMIDIOUTCAPS pmidicaps, UINT id)
    : OutputDevice(pmidicaps, id), m_pSequencer(NULL)
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

    return ::midiStreamOpen(
               (HMIDISTRM *)&m_handle,
               &m_id,
               1 /* reserved */,
               (DWORD)MidiStream::MidiStreamProc,
               (DWORD) this,
               CALLBACK_FUNCTION);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Close()
{
    MMRESULT result = MMSYSERR_INVALHANDLE;

    if (m_handle != NULL) {
        result = ::midiStreamClose(*this);
        m_handle = NULL;
    }

    return result;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Position(LPMMTIME pmmt) const
{
    ASSERT(*this != NULL);
    ASSERT(pmmt != NULL);

    return ::midiStreamPosition(*this, pmmt, sizeof(MMTIME));
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Property (LPBYTE ppropdata, DWORD property) const
{
    ASSERT(*this != NULL);
    ASSERT(ppropdata != NULL);

    return ::midiStreamProperty(*this, ppropdata, property);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Out(LPMIDIHDR pMidiHdr)
{
    ASSERT(*this != NULL);
    ASSERT(pMidiHdr != NULL);

    // Prepare the header
    MMRESULT result = ::midiOutPrepareHeader((HMIDIOUT)m_handle, pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR)
        return result;

    // Output the header
    result = ::midiStreamOut(*this, pMidiHdr, sizeof(MIDIHDR));
    if (result != MMSYSERR_NOERROR) {
        ::midiOutUnprepareHeader((HMIDIOUT)m_handle, pMidiHdr, sizeof(MIDIHDR));
        return result;
    }

    // The midi header will be unprepared in the MidiStreamProc callback function

    return MMSYSERR_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Restart()
{
    ASSERT(*this != NULL);

    return ::midiStreamRestart(*this);
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::Stop() const
{
    ASSERT(*this != NULL);

    return ::midiStreamStop(*this);
}

/////////////////////////////////////////////////////////////////////////////
void CALLBACK MidiStream::MidiStreamProc(
    HMIDISTRM hMidiStream,
    UINT uMsg,
    DWORD dwInstance,
    DWORD dwParam1,
    DWORD dwParam2
)
{
    MidiStream * This = (MidiStream *)dwInstance;
    ASSERT(This != NULL);

    // Iterate through the hook chain
    POSITION pos = This->m_HookChain.GetHeadPosition();
    while (pos != NULL) {
        PFNCALLBACK pfnCallBack = This->m_HookChain.GetNext(pos);
        ASSERT(pfnCallBack != NULL);

        (*pfnCallBack)(hMidiStream, uMsg, dwInstance, dwParam1, dwParam2);
    }
}

/////////////////////////////////////////////////////////////////////////////
MMRESULT MidiStream::ShortMessage(const MidiMessage & message) const
{
    ASSERT(*this != NULL);

    return ::midiOutShortMsg(GetOutputHandle(), message);
}

/////////////////////////////////////////////////////////////////////////////
BOOL MidiStream::RegisterHook(PFNCALLBACK pfnCallBack)
{
    ASSERT(pfnCallBack != NULL);
    ASSERT_VALID(&m_HookChain);

    // Don't allow duplicates in the hook chain
    if (m_HookChain.Find(pfnCallBack) != NULL)
        return FALSE;

    return m_HookChain.AddTail(pfnCallBack) != NULL;
}

/////////////////////////////////////////////////////////////////////////////
BOOL MidiStream::RevokeHook(PFNCALLBACK pfnCallBack)
{
    ASSERT(pfnCallBack != NULL);
    ASSERT_VALID(&m_HookChain);

    POSITION pos = m_HookChain.GetHeadPosition();
    while (pos != NULL) {
        if (m_HookChain.GetAt(pos) == pfnCallBack) {
            m_HookChain.RemoveAt(pos);
            return TRUE;
        }
        m_HookChain.GetNext(pos);
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
void MidiStream::SetSequencer(Sequencer *pSeq)
{
    m_pSequencer = pSeq;
}

/////////////////////////////////////////////////////////////////////////////
Sequencer *MidiStream::GetSequencer() const
{
    return m_pSequencer;
}
