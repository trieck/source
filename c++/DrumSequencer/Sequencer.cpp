#include "StdAfx.h"
#include "midicommon.h"
#include "miditime.h"
#include "outputdevs.h"
#include "resource.h"
#include "Sequencer.h"

Sequencer::Sequencer() : m_pStream(nullptr), m_state(Stopped), m_workerThread(nullptr)
{
}

Sequencer::~Sequencer()
{
    Close();
    if (m_pStream != nullptr) {
        delete m_pStream;
        m_pStream = nullptr;
    }
}

BOOL Sequencer::Initialize()
{
    ASSERT(m_pStream == NULL);

    CWaitCursor cursor;
    m_workerThread = AfxBeginThread(ThreadProc, this);
    auto dwRet = WaitForSingleObject(m_threadEvent, INFINITE); // wait forever to setup
    if (dwRet != WAIT_OBJECT_0) {
        AfxMessageBox(IDS_COULDNOTCREATETHREAD);
        return FALSE;
    }

    // Set the output stream to the midi mapper
    m_pStream = dynamic_cast<MidiStream*>(OutputDevices().GetDevice(MIDI_MAPPER));
    if (m_pStream == nullptr) {
        AfxMessageBox(IDS_COULDNOTOPENMIDIMAPPER);
        return FALSE;
    }

    // Open the output device
    const auto result = m_pStream->Open(StreamProc, this);
    if (result != MMSYSERR_NOERROR) {
        AfxMessageBox(OutputDevice::GetErrorText(result));
        return FALSE;
    }

    // Set the time division
    MIDIPROPTIMEDIV prop;
    prop.cbStruct = sizeof(MIDIPROPTIMEDIV);
    prop.dwTimeDiv = DEFAULT_PPQN;
    if (m_pStream->Property(reinterpret_cast<LPBYTE>(&prop), MIDIPROP_SET | MIDIPROP_TIMEDIV) != MMSYSERR_NOERROR) {
        AfxMessageBox(IDS_COULDNOTSETTIMEDIVISION);
        return FALSE;
    }

    return TRUE;
}

void Sequencer::Close() const
{
    if (m_pStream != nullptr) {
        SetEvent(m_shutdownEvent);
        WaitForSingleObject(m_workerThread, INFINITE); // wait forever to shutdown
        m_pStream->Close();
    }
}

BOOL Sequencer::Play(const Sequence& sequence)
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());

    m_front.Encode(sequence);
    m_back.Encode(sequence);

    auto result = m_pStream->Stop();
    if (result != MMSYSERR_NOERROR) {
        return FALSE;
    }

    result = m_pStream->Out(m_front);
    if (result != MMSYSERR_NOERROR) {
        return FALSE;
    }

    result = m_pStream->Out(m_back);
    if (result != MMSYSERR_NOERROR) {
        return FALSE;
    }

    result = m_pStream->Restart();
    if (result != MMSYSERR_NOERROR) {
        return FALSE;
    }

    m_state = Playing;

    return TRUE;
}

BOOL Sequencer::Stop()
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());

    if (m_pStream->Stop() != MMSYSERR_NOERROR) {
        return FALSE;
    }

    m_state = Stopped;

    return TRUE;
}

short Sequencer::Tempo() const
{
    // Get the Tempo property
    MIDIPROPTEMPO prop{};
    prop.cbStruct = sizeof(MIDIPROPTEMPO);

    if (m_pStream->Property(reinterpret_cast<LPBYTE>(&prop),
                            MIDIPROP_GET | MIDIPROP_TEMPO) != MMSYSERR_NOERROR) {
        AfxMessageBox(IDS_COULDNOTGETTEMPO);
    }

    auto bpm = static_cast<short>(MidiTime::MicrosecondsToBPM(prop.dwTempo));

    return bpm;
}

void Sequencer::SetTempo(short bpm)
{
    // Set the Tempo property
    MIDIPROPTEMPO prop;
    prop.cbStruct = sizeof(MIDIPROPTEMPO);
    prop.dwTempo = MidiTime::BPMToMicroseconds(bpm);

    if (m_pStream->Property(reinterpret_cast<LPBYTE>(&prop),
                            MIDIPROP_SET | MIDIPROP_TEMPO) !=
        MMSYSERR_NOERROR) {
        AfxMessageBox(IDS_COULDNOTSETTEMPO);
    }
}

bool Sequencer::HasStream()
{
    return m_pStream != nullptr;
}

UINT Sequencer::ThreadProc(LPVOID pParam)
{
    auto pThis = reinterpret_cast<Sequencer*>(pParam);
    ASSERT(pThis);

    SetEvent(pThis->m_threadEvent); // initialized

    HANDLE handles[] = {pThis->m_frontEvent, pThis->m_backEvent, pThis->m_shutdownEvent};

    auto bRunning = true;
    while (bRunning) {
        auto result = WaitForMultipleObjects(3, handles, FALSE, INFINITE);
        switch (result) {
        case WAIT_OBJECT_0 + 0:
            pThis->m_pStream->Out(pThis->m_front);
            break;
        case WAIT_OBJECT_0 + 1:
            pThis->m_pStream->Out(pThis->m_back);
            break;
        case WAIT_OBJECT_0 + 2:
            bRunning = false;
            break;
        default:
            break;
        }
    }

    return 0;
}

void Sequencer::StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD_PTR dwInstance,
                           DWORD_PTR pMidiHdr, DWORD_PTR dwParam2)
{
    if (uMsg != MOM_DONE) {
        return;
    }

    // DO NOT call any multimedia functions from this function

    const auto pThis = reinterpret_cast<Sequencer*>(dwInstance);
    ASSERT(pThis != NULL);

    // Unprepare the midi header
    midiOutUnprepareHeader(
        reinterpret_cast<HMIDIOUT>(hMidiStream),
        reinterpret_cast<LPMIDIHDR>(pMidiHdr),
        sizeof(MIDIHDR));

    if (pThis->m_state == Playing) {
        // Queue more data if still playing
        // Determine whether we need to use the front or back buffer
        auto result = InterlockedIncrement(&pThis->m_completed);

        if (result % 2 != 0) {
            pThis->m_frontEvent.SetEvent();
        } else {
            pThis->m_backEvent.SetEvent();
        }
    }
}
