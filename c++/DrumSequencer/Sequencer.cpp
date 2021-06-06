#include "StdAfx.h"
#include "midicommon.h"
#include "miditime.h"
#include "outputdevs.h"
#include "resource.h"
#include "Sequencer.h"
#include "LockGuard.h"

Sequencer::Sequencer() : m_workerThread(nullptr), m_pStream(nullptr), m_state(Stopped)
{
}

Sequencer::~Sequencer()
{
    Close();
}

BOOL Sequencer::Initialize()
{
    ASSERT(m_pStream == NULL);

    m_workerThread = AfxBeginThread(ThreadProc, this);
    auto dwRet = WaitForSingleObject(m_threadEvent, INFINITE);
    // wait forever to setup
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

    const auto result = m_pStream->Open(m_workerThread->m_nThreadID,
                                        reinterpret_cast<DWORD_PTR>(this), CALLBACK_THREAD);
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

void Sequencer::Close()
{
    if (m_pStream != nullptr) {
        LockGuard lock(m_cs);
        m_pStream->Close();
        delete m_pStream;
        m_pStream = nullptr;
    }

    if (m_workerThread != nullptr) {
        WaitForSingleObject(m_workerThread->m_hThread, INFINITE); // wait forever to shutdown
        m_workerThread = nullptr;
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

    MSG msg;
    PeekMessage(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE); // force creation of message queue

    SetEvent(pThis->m_threadEvent); // indicate we are ready

    auto completed = 0;
    auto running = true;

    while (running && GetMessage(&msg, nullptr, MM_MOM_OPEN, MM_MOM_DONE) > 0) {
        LockGuard lock(pThis->m_cs);
        switch (msg.message) {
        case MM_MOM_DONE:
            if (pThis->m_pStream != nullptr) {
                pThis->m_pStream->Unprepare(reinterpret_cast<LPMIDIHDR>(msg.lParam));

                // front or back buffer?
                if (completed++ % 2 == 0) {
                    pThis->m_pStream->Out(pThis->m_front);
                } else {
                    pThis->m_pStream->Out(pThis->m_back);
                }
            }
            break;
        case MM_MOM_CLOSE:
            running = false;
        default:
            break;
        }
    }

    return 0;
}
