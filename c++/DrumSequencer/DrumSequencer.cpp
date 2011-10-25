
// DrumSequencer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "DrumSequencer.h"
#include "MainFrm.h"
#include "DrumSequencerDoc.h"
#include "DrumSequencerView.h"
#include "outputdevs.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ANON_BEGIN
void StreamProc(HMIDISTRM hMidiStream, UINT uMsg, DWORD dwInstance, 
	DWORD dwParam1, DWORD dwParam2);
ANON_END

#define PRG_SYNTH_DRUM	(118)

// CDrumSequencerApp

BEGIN_MESSAGE_MAP(CDrumSequencerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CDrumSequencerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_SEQUENCER_PLAY, &CDrumSequencerApp::OnSequencerPlay)
	ON_COMMAND(ID_SEQUENCER_STOP, &CDrumSequencerApp::OnSequencerStop)
END_MESSAGE_MAP()


// CDrumSequencerApp construction

CDrumSequencerApp::CDrumSequencerApp() : m_pStream(NULL)
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("DrumSequencer.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CDrumSequencerApp object

CDrumSequencerApp theApp;

CDrumSequencerApp::~CDrumSequencerApp()
{
	if (m_pStream != NULL) {
		delete m_pStream;
		m_pStream = NULL;
	}
}

// CDrumSequencerApp initialization

BOOL CDrumSequencerApp::InitInstance()
{
	// Initialize the MIDI stream
	if (!InitializeStream())
		return FALSE;

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDrumSequencerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDrumSequencerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

// CDrumSequencerApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CDrumSequencerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDrumSequencerApp customization load/save methods

void CDrumSequencerApp::PreLoadState()
{
}

void CDrumSequencerApp::LoadCustomState()
{
}

void CDrumSequencerApp::SaveCustomState()
{
}

// CDrumSequencerApp message handlers

int CDrumSequencerApp::ExitInstance()
{
	if (m_pStream != NULL) {
		m_pStream->Close();
	}

	return CWinAppEx::ExitInstance();
}

BOOL CDrumSequencerApp::InitializeStream(void)
{
	ASSERT(m_pStream == NULL);

	// Set the output stream to the midi mapper
	m_pStream = (MidiStream *)OutputDevices().GetStream(MIDI_MAPPER);
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

	// make a program change to synth drum
	MidiMessage msg;
	msg.SetStatus(PROGRAM_CHANGE(0));
	msg.SetData(PRG_SYNTH_DRUM);
	
	return (m_pStream->ShortMessage(msg) == MMSYSERR_NOERROR);
}

void CDrumSequencerApp::OnSequencerPlay()
{
}

void CDrumSequencerApp::OnSequencerStop()
{
}

ANON_BEGIN

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

ANON_END
