// ear.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "baseinc.h"
#include "ear.h"
#include "earDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int defaultVelocity = 127;
int defaultChannel = 0;
int loNote = 60;
int hiNote = 72;

static void StreamProc(HMIDISTRM, UINT, DWORD, DWORD, DWORD);

/////////////////////////////////////////////////////////////////////////////
// EarApp
BEGIN_MESSAGE_MAP(EarApp, CWinApp)
    //{{AFX_MSG_MAP(EarApp)
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// EarApp construction
EarApp::EarApp()
{
    m_pStream = NULL;
    m_Intervals = INTERVAL_ALL;
    m_instrument = 0;
}
EarApp::~EarApp()
{
    if (m_pStream != NULL)
        delete [] m_pStream;
}
/////////////////////////////////////////////////////////////////////////////
// The one and only EarApp object
EarApp theApp;
/////////////////////////////////////////////////////////////////////////////
// EarApp initialization
BOOL EarApp::InitInstance()
{
    srand(GetTickCount());
    if (!InitializeStream())
        return FALSE;
    EarDlg dlg;
    m_pMainWnd = &dlg;

    dlg.DoModal();

    return FALSE;
}
int EarApp::ExitInstance()
{
    if (m_pStream != NULL && m_pStream->IsOpen()) {
        m_pStream->Stop();
        m_pStream->Close();
    }
    return CWinApp::ExitInstance();
}
//
// InitializeStream
//
BOOL EarApp::InitializeStream()
{
    ASSERT(m_pStream == NULL);
    // Set the output stream to the midi mapper
    m_pStream = (MidiStream *)OutputDevices().GetStream(-1);
    if (m_pStream == NULL) {
        AfxMessageBox(IDS_COULDNOTOPENMIDIMAPPER);
        return FALSE;
    }
    m_pStream->RegisterHook(StreamProc);
    // Open the output device
    MMRESULT result = m_pStream->Open();
    if (result != MMSYSERR_NOERROR) {
        AfxMessageBox(OutputDevice::GetErrorText(result));
        return FALSE;
    }
    // Set the time division
    MIDIPROPTIMEDIV prop;
    prop.cbStruct = sizeof(MIDIPROPTIMEDIV);
    prop.dwTimeDiv = DEFAULT_PPQN;
    if (m_pStream->Property((LPBYTE)&prop, MIDIPROP_SET | MIDIPROP_TIMEDIV) != MMSYSERR_NOERROR) {
        AfxMessageBox(IDS_COULDNOTSETTIMEDIVISION);
        return FALSE;
    }
    // Set the default instrument
    return SetInstrument(m_instrument);
}
BOOL EarApp::Play(MidiBuffer *pbuff)
{
    MMRESULT result;
    result = m_pStream->Stop();
    if (result != MMSYSERR_NOERROR)
        return FALSE;
    result = m_pStream->Out(*pbuff);
    if (result != MMSYSERR_NOERROR)
        return FALSE;
    result = m_pStream->Restart();
    if (result != MMSYSERR_NOERROR)
        return FALSE;
    return TRUE;
}
BOOL EarApp::Stop()
{
    if (m_pStream == NULL)
        return FALSE;
    return m_pStream->Stop() == MMSYSERR_NOERROR;
}
void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD dwInstance,
                DWORD dwParam1, DWORD dwParam2)
{
    if (uMsg != MOM_DONE)
        return;
    // Unprepare the midi header
    ::midiOutUnprepareHeader(
        (HMIDIOUT)hMidiStream,
        (LPMIDIHDR)dwParam1,
        sizeof(MIDIHDR));
}
int EarApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
    return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

BOOL EarApp::SetInstrument(BYTE b)
{
    ASSERT(m_pStream != NULL);
    ASSERT(m_pStream->IsOpen());
    MidiMessage msg;
    msg.SetStatus(PROGRAM_CHANGE(defaultChannel));
    msg.SetData(b);
    if (m_pStream->ShortMessage(msg) == MMSYSERR_NOERROR) {
        m_instrument = b;
        return TRUE;
    }
    return FALSE;
}

