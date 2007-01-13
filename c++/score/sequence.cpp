///////////////////////////////////////////////////////////////////////
//
//	SEQUENCE.CPP
//
//	MIDI Sequencer class
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"

#define PREALLOCSIZE 2

// Singleton instance
static Sequencer * This = NULL;

//
// Constructor
//
Sequencer :: Sequencer(MidiStream * pStream)
{
    ASSERT(pStream != NULL);
    ASSERT(pStream->IsOpen());

    This = this;
    m_pStream = pStream;
    m_pStream->RegisterHook(StreamProc);

	m_state = Stopped;
    m_nBuffers = 0;
    m_nCurrentBuffer = 0;
}

//
// Destructor
//
Sequencer :: ~Sequencer()
{
    if (m_pStream != NULL)
        m_pStream->RevokeHook(StreamProc);
}

//
// PlayMeasure
//
BOOL Sequencer :: PlayMeasure(const Measure * pMeasure)
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());
    ASSERT(pMeasure != NULL);
    
    if (!Stop())
        return FALSE;

    m_Buffers.SetFront(DataEngine(pMeasure));
    m_pStream->Out(m_Buffers.GetFront());

    m_nBuffers = 1;
    m_nCurrentBuffer = 0;

    if (m_pStream->Restart() != MMSYSERR_NOERROR) {
        m_nBuffers = 0;
        return FALSE;
    }

    m_state = Playing;

    return TRUE;
}

//
// PlayStaff
//
BOOL Sequencer :: PlayStaff(const Staff * pStaff)
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());
    ASSERT(pStaff != NULL);
    ASSERT(m_MeasureQueue.empty());

    if (!Stop())
        return FALSE;

    const MEASUREARRAY * pMeasures = pStaff->GetMeasures();
    ASSERT_VALID(pMeasures);

    int MeasureCount = pStaff->GetMeasureCount();
    if (MeasureCount >= PREALLOCSIZE) {
        m_Buffers.SetFront(DataEngine(pMeasures->GetAt(0)));
        m_Buffers.SetBack(DataEngine(pMeasures->GetAt(1)));
        m_pStream->Out(m_Buffers.GetFront());
        m_pStream->Out(m_Buffers.GetBack());
        m_nBuffers = PREALLOCSIZE;
    }
    
    for (int i = PREALLOCSIZE; i < MeasureCount; i++) {
        Measure * pMeasure = pMeasures->GetAt(i);
        if (pMeasure->HasData()) {
            m_MeasureQueue.push(pMeasure);
            m_nBuffers++;
        }
    }

    m_nCurrentBuffer = 0;

    if (m_pStream->Restart() != MMSYSERR_NOERROR) {
        m_nBuffers = 0;
        return FALSE;
    }

    m_state = Playing;
    
    return TRUE;
}

//
// Stop
//
BOOL Sequencer :: Stop()
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());
    
    m_MeasureQueue.clear();
    m_nBuffers = 0;
    m_nCurrentBuffer = 0;

    MMRESULT result = m_pStream->Stop();
    if (result != MMSYSERR_NOERROR)
        return FALSE;
    
    m_state = Stopped;

    return TRUE;
}

//
// StreamProc
//
void Sequencer :: StreamProc(
    HMIDISTRM hMidiStream, 
    UINT uMsg, 
    DWORD dwInstance, 
    DWORD dwParam1,   
    DWORD dwParam2)
{
    if (uMsg != MOM_DONE)
        return;

    ASSERT(This != NULL);
    MeasureQueue & queue = This->m_MeasureQueue;

    // Unprepare the midi header
    ::midiOutUnprepareHeader(
        (HMIDIOUT)hMidiStream, 
        (LPMIDIHDR)dwParam1, 
        sizeof(MIDIHDR));

    // Have all the buffers completed
    if (--This->m_nBuffers == 0) {
        This->m_state = Stopped;
        This->m_nCurrentBuffer = 0;
        return;
    }

    // Is there pending data on the queue
    if (queue.size() == 0)
        return;

    // Pull the next measure off the queue
    Measure * pNextMeasure = queue.front();

    // Determine whether we need to assign to the front or back
    if (This->m_nCurrentBuffer++ % 2 == 0) {
        This->m_Buffers.SetFront(DataEngine(pNextMeasure));
        This->m_pStream->Out(This->m_Buffers.GetFront());
    }
    else  {
        This->m_Buffers.SetBack(DataEngine(pNextMeasure));
        This->m_pStream->Out(This->m_Buffers.GetBack());
    }

    queue.pop();
}
