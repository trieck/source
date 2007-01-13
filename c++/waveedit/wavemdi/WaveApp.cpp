//////////////////////////////////////
// Module Name	:	WaveApp.cpp		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave App 		//
//					Implementations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#include "WaveApp.h"
#include "WaveDoc.h"
#include "WaveView.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CWaveApp, CWinApp)
	ON_COMMAND(IDM_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWaveApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWaveApp::OnFileOpen)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CWaveApp construction/destruction

CWaveApp::CWaveApp()
{
	m_pDSound		= NULL;
	m_pMainFrame	= NULL;
	m_szDefPath		= _T("");
}

CWaveApp :: ~CWaveApp()
{
}

INT CWaveApp :: ExitInstance()
{
	ReleaseInterface(m_pDSound);

	return CWinApp :: ExitInstance();
}

VOID CWaveApp :: OnFileOpen()
{
	CString			strNewName, strMessage;
	HMMIO			hmmio;      
	MMCKINFO		mmckinfoParent;     // parent chunk information 
    MMCKINFO		mmckinfoSubchunk;   // subchunk information structure 
    DWORD			dwFmtSize;          // size of "FMT" chunk 
    DWORD			dwDataSize;         // size of "DATA" chunk 
    LPWAVEFORMATEX	pFormat;			// address of "FMT" chunk 
    HPSTR			lpData;             // address of "DATA" chunk 

	ASSERT(m_pDSound);
	
	// Set default directory from .INI file
	::SetCurrentDirectory(m_szDefPath);

	if (!DoPromptFileName(strNewName, AFX_IDS_OPENFILE,
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return; // open cancelled

	SetCapture(m_pMainFrame->GetSafeHwnd());
	SetCursor(::LoadCursor(NULL, IDC_WAIT));

	// Open the file for reading with buffered I/O 
    // by using the default internal buffer 
    if(!(hmmio = mmioOpen(strNewName.GetBuffer(0), NULL, 
        MMIO_READ | MMIO_ALLOCBUF))) 
    { 
        AfxMessageBox(IDS_FILEERROR);
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return; 
    }

	// Locate a "RIFF" chunk with a "WAVE" form type to make 
    // sure the file is a waveform-audio file. 
    mmckinfoParent.fccType = mmioStringToFOURCC(_T("WAVE"), 0); 
    if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, NULL, 
        MMIO_FINDRIFF)) 
    { 
        AfxMessageBox(IDS_INVALIDFILE);
		mmioClose(hmmio, 0);
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return; 
    }

	 // Find the "FMT" chunk (form type "FMT"); it must be 
    // a subchunk of the "RIFF" chunk. 
    mmckinfoSubchunk.ckid = mmioStringToFOURCC(_T("fmt "), 0); 
    if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, 
        MMIO_FINDCHUNK)) 
    { 
		AfxMessageBox(IDS_NOFMTCHUNK);
		mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	}

	// Get the size of the "FMT" chunk. Allocate 
    // and lock memory for it. 
    dwFmtSize = mmckinfoSubchunk.cksize;
	pFormat = (LPWAVEFORMATEX)LocalAlloc(LMEM_FIXED, dwFmtSize);
	if (!pFormat)
	{
		AfxMessageBox(IDS_OUTOFMEMORY);
		mmioClose(hmmio, 0);
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	}

	// Read the "FMT" chunk. 
    if (mmioRead(hmmio, (HPSTR) pFormat, dwFmtSize) != (LONG)dwFmtSize)
	{ 
    	AfxMessageBox(IDS_FILEREADERROR);
		LocalFree(pFormat);
        mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
		return;
	}

	// Ensure it's a PCM file.
	if (pFormat->wFormatTag != WAVE_FORMAT_PCM)
	{
		AfxMessageBox(IDS_NOTPCMFILE);
		LocalFree(pFormat);
        mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
		return;
	}
 
    // Ascend out of the "FMT" subchunk. 
    mmioAscend(hmmio, &mmckinfoSubchunk, 0); 

	// Find the data subchunk. The current file position should be at 
    // the beginning of the data chunk; however, we should not make 
    // this assumption. Use mmioDescend to locate the data chunk. 
    mmckinfoSubchunk.ckid = mmioStringToFOURCC(_T("data"), 0); 
    if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, 
        MMIO_FINDCHUNK)) 
    { 
        AfxMessageBox(IDS_NODATACHUNK);
		LocalFree(pFormat);
        mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
		return;
    }

	// Get the size of the data subchunk. 
    dwDataSize = mmckinfoSubchunk.cksize; 
    if (dwDataSize == 0L)
	{ 
	    AfxMessageBox(IDS_DATACHUNKNODATA);
		LocalFree(pFormat);
        mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
		return;
	}

	// Allocate and lock memory for the waveform-audio data. 
    lpData = (HPSTR)LocalAlloc(LMEM_FIXED, dwDataSize); 
    if (!lpData)
	{
		AfxMessageBox(IDS_OUTOFMEMORY);
		LocalFree(pFormat);
        mmioClose(hmmio, 0); 
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	}
 
    // Read the waveform-audio data subchunk. 
    if(mmioRead(hmmio, (HPSTR) lpData, dwDataSize) != (LONG)dwDataSize)
	{ 
		AfxMessageBox(IDS_ERRORREADDATA);
		LocalFree(pFormat);
		LocalFree(lpData);
        mmioClose(hmmio, 0);
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	} 

	mmioClose(hmmio, 0); 

	DSBUFFERDESC		dsbd;
	LPDIRECTSOUNDBUFFER	pBuffer = NULL;

	dsbd.dwSize			= sizeof(DSBUFFERDESC);
	dsbd.dwFlags		= DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes	= dwDataSize;
	dsbd.dwReserved		= 0;
	dsbd.lpwfxFormat	= pFormat;

	// Create the DirectSound Buffer.
	HRESULT hr = m_pDSound->CreateSoundBuffer(&dsbd, &pBuffer, NULL);
	if (FAILED(hr))
	{
		AfxMessageBox(IDS_CANTCREATESOUNDBUFFER);
		LocalFree(pFormat);
		LocalFree(lpData);
        SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	}

	// Lock the buffer and set the data
	HPSTR	pData1, pData2;
	DWORD	dwSize1, dwSize2;
	hr = pBuffer->Lock(0, dwDataSize, (PPVOID)&pData1, &dwSize1,
						(PPVOID)&pData2, &dwSize2, DSBLOCK_FROMWRITECURSOR);
	if (FAILED(hr))
	{
		AfxMessageBox(IDS_CANTLOCKSOUNDBUFFER);
		LocalFree(pFormat);
		LocalFree(lpData);
        SetCursor(::LoadCursor(NULL, IDC_ARROW));
		ReleaseCapture();
        return;
	}

	// Copy the data into the buffer
	memcpy(pData1, lpData, dwSize1);
	if (dwSize1 < dwDataSize)
		memcpy(pData2, lpData + dwSize1, dwSize2);

	// Unlock the buffer
	pBuffer->Unlock(pData1, dwSize1, pData2, dwSize2);

	// Create the document object
	CWaveDoc* pDoc = (CWaveDoc*)OpenDocumentFile(strNewName);
	ASSERT_VALID(pDoc);
	
	pDoc->SetBuffer(pBuffer);						// Set the DirectSound Buffer to the document
	pDoc->SetRate(pFormat->nAvgBytesPerSec);		// Set the Average bytes per second, used during playback.
	pDoc->UpdateAllViews(NULL);

	LocalFree(pFormat);
	LocalFree(lpData);
	
	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	ReleaseCapture();
}

///////////////////////////////////////////////////////////////////
// CWaveApp initialization

BOOL CWaveApp::InitInstance()
{
	if (!AfxOleInit())	// Initialize the OLE libraries.
		return FALSE;
	
	// Cache an object pointer
	HRESULT hr = ::DirectSoundCreate(NULL, &m_pDSound, NULL);
	if (FAILED(hr))
	{
		AfxMessageBox(IDS_BADOBJECT);
		return FALSE;
	}

	//Register the application's document template
	CMultiDocTemplate* pDocTemplate;
	
	pDocTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWaveDoc),
		RUNTIME_CLASS(CMDIChildWnd),    
		RUNTIME_CLASS(CWaveView));

	AddDocTemplate(pDocTemplate);

	// Create MDI Frame Window
	m_pMainFrame = new CMainFrame;
	if (!m_pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	m_pMainWnd = m_pMainFrame;
			      
	// Set Cooperative level for DirectSound object
	m_pDSound->SetCooperativeLevel(m_pMainWnd->GetSafeHwnd(), DSSCL_NORMAL);

	// Parse command line (this is required by doc/view)
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Read initializers from .INI file
	m_szDefPath = GetProfileString(_T("Application"), 
					_T("DefaultFilePath"));
	
	m_pMainFrame->ShowWindow(m_nCmdShow);
	m_pMainFrame->UpdateWindow();
	
	return TRUE;
}

VOID CWaveApp :: OnAppAbout()
{
	CDialog dlg(IDD_ABOUT);

	dlg.DoModal();
}
	
///////////////////////////////////////////////////////////////////
// Declare and initialize the sole CWaveApp object

CWaveApp MyApp;
