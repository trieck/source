// score.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "MainFrm.h"
#include "ScoreDoc.h"
#include "ScoreView.h"
#include "SettingsDlg.h"
#include "OutputDevs.h"
#include "MidiMessage.h"
#include "regkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PUMP_INTERVAL 100

// Helper functions
static CString GetRegistryKey();
static CString GetRealKey(LPCSTR pkey);
static BYTE GetVelocity();
static BYTE GetDefaultChannel();

BYTE defaultVelocity = GetVelocity();
BYTE defaultChannel = GetDefaultChannel();
static const float appVersion = 1.00;
static LPCSTR pRegKey = "SOFTWARE\\Rieck Enterprises\\Score\\%.2f";

/////////////////////////////////////////////////////////////////////////////
// ScoreApp

BEGIN_MESSAGE_MAP(ScoreApp, CWinApp)
	//{{AFX_MSG_MAP(ScoreApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScoreApp construction

ScoreApp::ScoreApp()
{
	m_pSequencer = NULL;
	m_pStream = NULL;
	m_instrument = 0;
}

ScoreApp :: ~ScoreApp()
{
	if (m_pSequencer != NULL)
		delete m_pSequencer;
	if (m_pStream != NULL)
		delete m_pStream;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only ScoreApp object

ScoreApp theApp;

/////////////////////////////////////////////////////////////////////////////
// ScoreApp initialization

BOOL ScoreApp :: InitInstance()
{
	// Initialize the MIDI stream
	if (!InitializeStream())
		return FALSE;

	ASSERT(m_pStream != NULL);

	// Create the sequencer object
	m_pSequencer = new Sequencer(m_pStream);
	if (m_pSequencer == NULL)
		return FALSE;

	// Set the time division
	MIDIPROPTIMEDIV prop;
	prop.cbStruct = sizeof(MIDIPROPTIMEDIV);
	prop.dwTimeDiv = DEFAULT_PPQN;
	if (m_pStream->Property((LPBYTE)&prop, MIDIPROP_SET | MIDIPROP_TIMEDIV) != MMSYSERR_NOERROR) {
		AfxMessageBox(IDS_COULDNOTSETTIMEDIVISION);
		return FALSE;
	}

	LoadStdProfileSettings();	// load standard INI file options (including MRU)
	LoadSettings();				// load registry settings

	// Register document templates
	CSingleDocTemplate* pDocTemplate = new CSingleDocTemplate(
	    IDR_MAINFRAME,
	    RUNTIME_CLASS(ScoreDoc),
	    RUNTIME_CLASS(MainFrame),
	    RUNTIME_CLASS(ScoreView));
	AddDocTemplate(pDocTemplate);

	EnableShellOpen();
	RegisterShellFileTypes();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->DragAcceptFiles();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ScoreApp message handlers

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void ScoreApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// ScoreApp message handlers

//
// OnSettings
//
void ScoreApp :: OnSettings()
{
	SettingsDlg().DoModal();
}

//
// ExitInstance
//
int ScoreApp::ExitInstance()
{
	Stop();

	SaveSettings();

	return CWinApp::ExitInstance();
}

//
// Stop
//
BOOL ScoreApp :: Stop() const
{
	if (m_pSequencer != NULL)
		m_pSequencer->Stop();

	if (m_pStream != NULL && m_pStream->IsOpen())
		m_pStream->Stop();

	return TRUE;
}

//
// PlayNote
//
BOOL ScoreApp :: PlayNote(const Note * pNote) const
{
	ASSERT(pNote != NULL);
	ASSERT(m_pStream != NULL);
	ASSERT(m_pStream->IsOpen());

	MidiMessage msg;
	msg.SetVelocity(defaultVelocity);
	msg.SetData(pNote->GetData());
	msg.SetStatus(NOTEON(defaultChannel));

	return m_pStream->ShortMessage(msg) == MMSYSERR_NOERROR;
}

//
// ReleaseNote
//
BOOL ScoreApp :: ReleaseNote(const Note * pNote) const
{
	ASSERT(pNote != NULL);
	ASSERT(m_pStream != NULL);
	ASSERT(m_pStream->IsOpen());

	MidiMessage msg;
	msg.SetVelocity(defaultVelocity);
	msg.SetData(pNote->GetData());
	msg.SetStatus(NOTEOFF(defaultChannel));

	return m_pStream->ShortMessage(msg) == MMSYSERR_NOERROR;
}

//
// SetInstrument
//
BOOL ScoreApp :: SetInstrument (BYTE b)
{
	ASSERT(m_pStream != NULL);
	ASSERT(m_pStream->IsOpen());

	m_instrument = b;

	MidiMessage msg;
	msg.SetStatus(PROGRAM_CHANGE(defaultChannel));
	msg.SetData(b);

	return m_pStream->ShortMessage(msg) == MMSYSERR_NOERROR;
}

//
// PlayStaff
//
BOOL ScoreApp :: PlayStaff(const Staff * pStaff)
{
	ASSERT(m_pSequencer != NULL);
	ASSERT(pStaff != NULL);

	if (!m_pSequencer->PlayStaff(pStaff))
		return FALSE;

	while (m_pSequencer->IsPlaying()) {
		PumpMessages();
		Sleep(PUMP_INTERVAL);
	}

	return TRUE;
}

//
// PlayMeasure
//
BOOL ScoreApp :: PlayMeasure (const Measure * pMeasure)
{
	ASSERT(m_pSequencer != NULL);
	ASSERT(pMeasure != NULL);

	if (!m_pSequencer->PlayMeasure(pMeasure))
		return FALSE;

	while (m_pSequencer->IsPlaying()) {
		PumpMessages();
		Sleep(PUMP_INTERVAL);
	}

	return TRUE;
}

//
// IsPlaying
//
BOOL ScoreApp :: IsPlaying() const
{
	ASSERT(m_pSequencer != NULL);

	return m_pSequencer->IsPlaying();
}

//
// OnStop
//
void ScoreApp :: OnStop()
{
	ASSERT(m_pSequencer != NULL);

	m_pSequencer->Stop();
}

//
// PumpMessages
//
void ScoreApp :: PumpMessages()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!PumpMessage()) {
			::PostQuitMessage(0);
			break;
		}
	}
	// let MFC do its idle processing
	LONG lIdle = 0;
	while (OnIdle(lIdle++))
		;
}

//
// OnFileNew
//
void ScoreApp :: OnFileNew()
{
	Stop();

	CWinApp::OnFileNew();
}

//
// OnFileOpen
//
void ScoreApp :: OnFileOpen()
{
	CWinApp::OnFileOpen();
}

//
// OpenDocumentFile
//
CDocument* ScoreApp :: OpenDocumentFile(LPCTSTR lpszFileName)
{
	Stop();

	return CWinApp::OpenDocumentFile(lpszFileName);
}

//
// InitializeStream
//
BOOL ScoreApp :: InitializeStream()
{
	ASSERT(m_pStream == NULL);

	// Set the output stream to the midi mapper
	m_pStream = (MidiStream *)OutputDevices().GetStream(-1);
	if (m_pStream == NULL) {
		AfxMessageBox(IDS_COULDNOTOPENMIDIMAPPER);
		return FALSE;
	}

	// Open the output device
	MMRESULT result = m_pStream->Open();
	if (result != MMSYSERR_NOERROR) {
		AfxMessageBox(OutputDevice::GetErrorText(result));
		return FALSE;
	}

	return TRUE;
}

//
// LoadSettings
//
void ScoreApp :: LoadSettings()
{
	BYTE instrument;
	GetRegValue("midi", "instrument", (LPDWORD)&instrument);
	SetInstrument(instrument);
}

//
// SaveSettings
//
void ScoreApp :: SaveSettings() const
{
	SetRegValue("midi", "instrument", m_instrument);
}

// Helper functions

//
// GetVelocity
//
BYTE GetVelocity()
{
	DWORD velocity;

	GetRegValue("midi", "velocity", &velocity);

	return (BYTE)velocity;
}

//
// GetDefaultChannel
//
BYTE GetDefaultChannel()
{
	DWORD channel;

	GetRegValue("midi", "channel", &channel);

	return (BYTE)channel;
}

//
// GetRegistryKey
//
CString GetRegistryKey()
{
	CString key;
	key.Format(pRegKey, appVersion);

	return key;
}

//
// GetRealKey
//
CString GetRealKey(LPCSTR pkey)
{
	ASSERT(pkey != NULL);

	CString keyname;
	keyname.Format("%s\\%s", GetRegistryKey(), pkey);

	return keyname;
}

//
// GetRegValue
//
CString GetRegValue(LPCTSTR pkey, LPCTSTR pvalue)
{
	CRegKey key;

	ASSERT(pkey != NULL);
	ASSERT(pvalue != NULL);

	CString keyname = GetRealKey(pkey);

	// Open the specified key
	if (key.Open(HKEY_LOCAL_MACHINE, keyname, KEY_READ) != ERROR_SUCCESS)
		return "";

	// Determine the size of the needed buffer
	DWORD dwCount = 0;
	if (key.GetValue((LPTSTR)NULL, pvalue, &dwCount) != ERROR_SUCCESS)
		return "";

	// Now grab the data
	CString value;
	key.GetValue(value.GetBuffer(dwCount), pvalue, &dwCount);

	value.ReleaseBuffer(dwCount);

	return value;
}

//
// GetRegValue
//
LONG GetRegValue(LPCTSTR pkey, LPCTSTR pvalue, LPDWORD pdwValue)
{
	CRegKey key;

	ASSERT(pkey != NULL);
	ASSERT(pvalue != NULL);
	ASSERT(pdwValue != NULL);

	*pdwValue = 0L;

	CString keyname = GetRealKey(pkey);

	// Open the specified key
	LONG lRtn = key.Open(HKEY_LOCAL_MACHINE, keyname, KEY_READ);
	if (lRtn != ERROR_SUCCESS)
		return lRtn;

	return key.GetValue(pdwValue, pvalue);
}

//
// SetRegValue
//
LONG SetRegValue(LPCTSTR pkey, LPCTSTR pvaluename, LPCTSTR pvalue)
{
	CRegKey key;

	ASSERT(pkey != NULL);
	ASSERT(pvaluename != NULL);
	ASSERT(pvalue != NULL);

	CString keyname = GetRealKey(pkey);

	// Open the specified key
	LONG lRtn = key.Open(HKEY_LOCAL_MACHINE, keyname, KEY_SET_VALUE);
	if (lRtn != ERROR_SUCCESS)
		return lRtn;

	return key.SetValue(pvalue, pvaluename);
}

//
// SetRegValue
//
LONG SetRegValue(LPCTSTR pkey, LPCTSTR pvaluename, DWORD value)
{
	CRegKey key;

	ASSERT(pkey != NULL);
	ASSERT(pvaluename != NULL);

	CString keyname = GetRealKey(pkey);

	// Open the specified key
	LONG lRtn = key.Open(HKEY_LOCAL_MACHINE, keyname, KEY_SET_VALUE);
	if (lRtn != ERROR_SUCCESS)
		return lRtn;

	return key.SetValue(value, pvaluename);
}


