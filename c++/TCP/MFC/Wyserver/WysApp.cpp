/*--------------------------------------
	Module:	WYSAPP.CPP
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/

#include "WysApp.h"
#include "WysWnd.h"
#include "resource.h"

CWysApp :: CWysApp()
{
	for (INT i = 0; i < MAXCONN; i++)
		pSockets[i] = NULL;
}

BOOL CWysApp :: InitInstance()
{
	// initialize socket layer
	WSAData wsa;
	AfxSocketInit(&wsa);

	// create sockets
	for (INT i = 0; i < MAXCONN; i++) {
		pSockets[i] = new CWySock;
		ASSERT_VALID (pSockets[i]);
	}

	// allocate memory for main window
	CWysWnd* pWnd = new CWysWnd();

	// create main window
	this->m_pMainWnd = pWnd;

	pWnd->Create(NULL, _T("Wysock Server"), WS_OVERLAPPEDWINDOW,
	             CRect(0, 0, 450, 200), 0, MAKEINTRESOURCE(IDM_MAINMENU),
	             WS_EX_OVERLAPPEDWINDOW, NULL);

	// create the list box
	pWnd->CreateListBox();

	// create the font
	pWnd->CreateListFont();

	// show the main window
	pWnd->CenterWindow();
	pWnd->ShowWindow(m_nCmdShow);
	pWnd->UpdateWindow();

	// set the winsock description
	SCREENLINE sl;
	sl.uColor = COLOR_BLUE;
	sl.szText = wsa.szDescription;
	pWnd->AddListItem(&sl);

	// start listening
	AsyncListen();

	return (TRUE);
}

INT CWysApp :: ExitInstance()
{
	for (INT i = 0; i < MAXCONN; i++)
		if (pSockets[i]) delete pSockets[i];

	return (CWinApp :: ExitInstance());
}

DWORD CWysApp :: AsyncListen()
{
	INT i;
	SCREENLINE sl;

	CWysWnd* pWnd = (CWysWnd*)m_pMainWnd;
	ASSERT_VALID(pWnd);

	// create listen socket
	if ((i = GetSocket()) == NOTFOUND) {
		sl.uColor = COLOR_RED;
		sl.szText.LoadString(IDS_LISTENERR);
		pWnd->AddListItem(&sl);
		return (0);
	}

	// create the socket
	pSockets[i]->Create(DEFAULT_PORT, SOCK_STREAM,
	                    FD_ACCEPT | FD_READ | FD_CLOSE);

	// start listening
	if (!(pSockets[i]->Listen(MAXCONN))) {
		SCREENLINE sl;
		sl.uColor = COLOR_RED;
		sl.szText.LoadString(IDS_LISTENERR);
		pWnd->AddListItem(&sl);
		return (0);
	}

	pSockets[i]->State = LISTENING;

	return (1);
}

INT CWysApp :: GetSocket()
{
	for (INT i = 0; i < MAXCONN; i++)
		if (pSockets[i]->m_hSocket == INVALID_SOCKET)
			return(i);

	return (NOTFOUND);
}

INT CWysApp :: GetLoggingPath(CString& szLogPath)
{
	if (!m_bIsLogging) {
		szLogPath = "";
		return (-1);
	}

	szLogPath = m_szLogPath;
	return (0);
}

INT CWysApp :: SetLoggingPath(CString& szLogPath)
{
	if (!m_bIsLogging)
		return (-1);

	m_szLogPath = szLogPath;
	return (0);
}

BOOL CWysApp :: IsLogging()
{
	return (m_bIsLogging);
}

void CWysApp :: SetLogging (BOOL bLogging)
{
	m_bIsLogging = bLogging;
}

// create an instance of the CWysApp class
CWysApp TheApp;
