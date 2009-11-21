////////////////////////////////
//	Module:	SOCKHOST.C		  //
//	Author:	Thomas A. Rieck	  //
//	Date:	05/26/97		  //
////////////////////////////////

#include	"..\MERLIN.H"
#include	"SOCKHOST.H"
#include	"resource.h"

HINSTANCE		hInst;
SDSTRUCT		Sockets[MAXCONN];
LPCSTR			lpszClassName = "SocketHost";
LPLOGSTRUCT		pls = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, INT nCmdShow)
{
	MSG msg;

	if (!hPrevInstance)
		if (!InitApplication(hInstance))
			return (0);

	if (!InitInstance(hInstance, nCmdShow))
		return (0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;

#ifndef _DEBUG
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
#else
	wc.style			= CS_HREDRAW | CS_VREDRAW;
#endif
	wc.lpfnWndProc		= (WNDPROC)MainWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wc.hInstance		= hInstance;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName	= lpszClassName;

	return (RegisterClass(&wc));
}

BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow)
{
	static HWND	hWnd;

	hInst = hInstance;

	// disallow multiple instances
	if (FindWindow(lpszClassName, NULL))
		return (FALSE);

	// create the window
	hWnd = CreateWindowEx(
	           WS_EX_OVERLAPPEDWINDOW,			// Extended Window style
	           lpszClassName,					// Window Class
	           "Socket Host",					// Window Caption
	           WS_OVERLAPPEDWINDOW,			// Window style
	           CW_USEDEFAULT,				    // Default horizontal position.
	           CW_USEDEFAULT,					// Default vertical position.
	           450,				            // width.
	           200,							// height.
	           NULL,                           // Overlapped windows have no parent.
	           NULL,                           // Use the window class menu.
	           hInstance,                      // This instance owns this window.
	           NULL							// Pointer not needed.
	       );

	if (!hWnd)
		return (FALSE);

	// show the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return (TRUE);
}

LONG APIENTRY MainWndProc(HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
	static HWND				hWndList;
	static LOGFONT			lf;
	static HFONT			hFont;
	HFONT					hFontOld;
	SCREENLINE				sl;
	SOCKADDR_IN				acc_sin;
	SOCKET					sdTemp;
	INT						acc_sin_len, status, i;
	WSADATA					WSAData;
	CHAR					szBuffer[MAXMSGLEN];
	HDC						hDC;
	TEXTMETRIC				tm;
	LPMEASUREITEMSTRUCT		lpMIS;
	LPDRAWITEMSTRUCT		lpDIS;

	switch (message) {
	case WM_CREATE:
		// display splash screen
		DialogBox(hInst, MAKEINTRESOURCE(IDD_SPLASH),
		          hWnd, SplashProc);

		// initialize array of connection data structures
		for (i = 0; i < MAXCONN; i++) {
			Sockets[i].sdVal	= INVALID_SOCKET;
			Sockets[i].iState	= FREE;
		}

		// allocate memory for logging structure
		if (!(pls = malloc(sizeof(LOGSTRUCT)))) {
			LoadString(hInst, IDS_MEMERROR, szBuffer, MAXMSGLEN);
			MessageBox(hWnd, szBuffer, NULL, MB_ICONSTOP);
			return (-1);
		}

		// initialize application data
		InitAppData();

		// set default font
		hDC = GetDC(hWnd);

		lf.lfHeight			= -MulDiv(DEFAULT_FONTSIZE, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		lf.lfWidth			= 0;
		lf.lfEscapement		= 0;
		lf.lfOrientation	= 0;
		lf.lfWeight			= DEFAULT_WEIGHT;
		lf.lfItalic			= 0;
		lf.lfUnderline		= 0;
		lf.lfStrikeOut		= 0;
		lf.lfCharSet		= DEFAULT_CHARSET;
		lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
		lf.lfQuality		= DEFAULT_QUALITY;
		lf.lfPitchAndFamily	= DEFAULT_PITCH;
		strcpy(lf.lfFaceName, DEFAULT_FACENAME);

		hFont = CreateFontIndirect(&lf);

		// create list box
		hWndList = CreateListBox(hWnd);

		// set font for list box
		SendMessage(hWndList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

		ReleaseDC(hWnd, hDC);

		// start winsock services
		if ((status = WSAStartup(MAKEWORD(2,0),  &WSAData)) != 0)
			sl.uColor = COLOR_RED;
		else
			sl.uColor = COLOR_BLUE;

		strcpy(sl.szText, WSAData.szDescription);
		AddListItem(hWndList, &sl);

		// start listening
		AsyncListen(hWndList, ResolveServicePort());

		break;
	case WM_DESTROY:
		// free allocated memory
		if (pls) free(pls);

		// delete font
		DeleteObject(hFont);

		// close all sockets and
		// shutdown winsock services
		for (i = 0; i < MAXCONN; i++)
			if (Sockets[i].sdVal != INVALID_SOCKET) {
				closesocket(Sockets[i].sdVal);
				Sockets[i].sdVal = INVALID_SOCKET;
				Sockets[i].iState = FREE;
			}

		WSACleanup();

		// destroy list box
		DestroyWindow(hWndList);

		PostQuitMessage(0);
		break;
	case WM_WSAASYNC:
		// Find the index of the socket information data structure.
		if ((i = FindSocket(wParam)) == NOTFOUND)
			return(0);

		switch (WSAGETSELECTEVENT(lParam)) {
		case FD_ACCEPT:
			if (WSAGETSELECTERROR(lParam) == 0) { // success
				if (Sockets[i].iState != LISTENING)
					break;

				// find a free space in the array of connection data structures.
				if ((i = GetSocket()) == NOTFOUND) {
					// no space to accept this connection. however will accept
					// just using simple socket variable and close. Otherwise
					// client program will think it is connected.
					sdTemp = accept(wParam, NULL,NULL);
					closesocket(sdTemp);
					LoadString(hInst, IDS_NOMORESOCKETS, sl.szText, MAXMSGLEN);
					sl.uColor = COLOR_RED;
					AddListItem(hWndList, &sl);
					break;
				}

				// accept the incoming connection
				acc_sin_len = sizeof(acc_sin);
				Sockets[i].sdVal = accept(wParam, (LPSOCKADDR)&acc_sin,
				                          (LPINT)&acc_sin_len);

				if (Sockets[i].sdVal == INVALID_SOCKET) {
					LoadString(hInst, IDS_ACCEPTERR, szBuffer, MAXMSGLEN);
					sprintf(sl.szText, szBuffer, WSAGetLastError());
					sl.uColor = COLOR_RED;
					AddListItem(hWndList, &sl);
					break;
				} else {	// connected
					sl.uColor = COLOR_BLUE;
					LoadString(hInst, IDS_ACCEPTCONNECT, szBuffer, MAXMSGLEN);
					strcpy(Sockets[i].IPAddress, inet_ntoa(acc_sin.sin_addr));
					Sockets[i].iState = CONNECTED;
					sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
					AddListItem(hWndList, &sl);
				}
			} else {
				sl.uColor = COLOR_RED;
				LoadString(hInst, IDS_ACCEPTERR, szBuffer, MAXMSGLEN);
				sprintf(sl.szText, szBuffer, WSAGetLastError());
				AddListItem(hWndList, &sl);
			}
			break;
		case FD_READ:
			if (Sockets[i].iState != CONNECTED)
				break;

			// receive command
			ReceiveCmd(hWndList, i);

			break;
		case FD_CLOSE:
			sl.uColor = COLOR_RED;
			LoadString(hInst, IDS_CONNDROP, szBuffer, MAXMSGLEN);
			sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
			AddListItem(hWndList, &sl);

			// remove socket from array of connected sockets
			closesocket(Sockets[i].sdVal);
			Sockets[i].sdVal	= INVALID_SOCKET;
			Sockets[i].iState	= FREE;
			break;
		}
		break;
	case WM_SIZE:
		// resize listbox window
		MoveWindow(hWndList, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_MEASUREITEM:	// owner drawn list box
		lpMIS = (LPMEASUREITEMSTRUCT)lParam;

		hDC = GetDC(hWndList);

		hFontOld = SelectObject(hDC, hFont);

		GetTextMetrics(hDC, &tm);

		lpMIS->itemWidth	= tm.tmAveCharWidth;
		lpMIS->itemHeight	= tm.tmHeight + tm.tmExternalLeading;

		SelectObject(hDC, hFontOld);
		ReleaseDC(hWndList, hDC);

		break;
	case WM_DRAWITEM:		// owner drawn list box
		lpDIS = (LPDRAWITEMSTRUCT)lParam;

		if (lpDIS->itemID == -1)
			break;

		switch (lpDIS->itemAction) {
			INT y;
			CHAR tchBuffer[255];
			COLORREF uColor;
			HBRUSH hBrush, hBrushOld;

		case ODA_SELECT:
		case ODA_DRAWENTIRE:
			// get item text
			SendMessage(lpDIS->hwndItem, LB_GETTEXT,
			            lpDIS->itemID, (LPARAM) tchBuffer);

			// get item color
			uColor = SendMessage(lpDIS->hwndItem, LB_GETITEMDATA,
			                     lpDIS->itemID, 0);

			// retrieve position
			GetTextMetrics(lpDIS->hDC, &tm);
			y = (lpDIS->rcItem.bottom + lpDIS->rcItem.top -
			     tm.tmHeight) / 2;

			// check if item is selected
			if (lpDIS->itemState & ODS_SELECTED)
				// draw selected rectangle
				hBrush = CreateSolidBrush(COLOR_YELLOW);
			else	// draw default background
				hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

			hBrushOld = SelectObject(lpDIS->hDC, hBrush);
			FillRect(lpDIS->hDC, &(lpDIS->rcItem), hBrush);
			SelectObject(lpDIS->hDC, hBrushOld);
			DeleteObject(hBrush);

			// set background mode
			SetBkMode(lpDIS->hDC, TRANSPARENT);

			// set text item color
			SetTextColor(lpDIS->hDC, uColor);

			// display the text item
			TextOut(lpDIS->hDC,
			        0,
			        y,
			        tchBuffer,
			        strlen(tchBuffer));

			break;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			CHOOSEFONT	cf;
			INT			cyItem;
			HDC			hdcList;
			TEXTMETRIC	tmList;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT),
			          hWnd, AboutProc);
			break;
		case IDM_PREFERENCE:
			if (DialogBox(hInst, MAKEINTRESOURCE(IDD_PREFERENCES),
			              hWnd, PrefProc))
				UpdateInitData();
			break;
		case IDM_FONT:
			cf.lStructSize		= sizeof(cf);
			cf.hwndOwner		= hWnd;
			cf.hDC				= 0;
			cf.lpLogFont		= &lf;
			cf.Flags			= CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
			cf.rgbColors		= 0;
			cf.lCustData		= 0;
			cf.lpfnHook			= 0;
			cf.lpTemplateName	= 0;
			cf.hInstance		= 0;
			cf.lpszStyle		= 0;
			cf.nFontType		= 0;

			if (ChooseFont(&cf)) {
				// copy font returned from dialog
				memcpy(&lf, cf.lpLogFont, sizeof(LOGFONT));
				DeleteObject(hFont);
				hFont = CreateFontIndirect(&lf);
				hdcList = GetDC(hWndList);
				hFontOld = SelectObject(hdcList, hFont);

				// set the listbox item size and new font
				GetTextMetrics(hdcList, &tmList);
				cyItem = tmList.tmHeight + tmList.tmExternalLeading;
				SendMessage(hWndList, LB_SETITEMHEIGHT, 0, MAKELPARAM(cyItem, 0));
				SendMessage(hWndList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SelectObject(hdcList, hFontOld);
				ReleaseDC(hWndList, hdcList);
			}
			break;
		case IDM_ACTIVECONN:
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ACTIVECONN),
			               hWnd, ActiveConnProc, (LPARAM)hWndList);
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
}

//////////////////////////
// AddListItem Function
VOID AddListItem(HWND hWndList, LPSCREENLINE pSL)
{
	LONG lCount;

	// set list item text
	SendMessage(hWndList, LB_ADDSTRING, 0 ,(LPARAM)pSL->szText);

	// get a count of number of items
	lCount = SendMessage(hWndList, LB_GETCOUNT, 0, 0);

	// associate a color with a list item
	SendMessage(hWndList, LB_SETITEMDATA, (WPARAM)lCount-1, (LPARAM)pSL->uColor);

	// log entry
	if (pls->bIsLogging)
		WriteLogEntry(hWndList, pSL->szText);
}

/////////////////////////
// AsyncListen Function
DWORD AsyncListen(HWND hWndList, WORD wPort)
{
	SOCKADDR_IN local_sin;		// local socket address
	INT			status, i;
	CHAR		szBuffer[MAXMSGLEN];
	SCREENLINE	sl;

	// check for valid port
	if (wPort == 0) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_SERVERR, szBuffer, MAXMSGLEN);
		sprintf(sl.szText, szBuffer, SERVICE_NAME);
		AddListItem(hWndList, &sl);
		return (0);
	}

	// create listen socket
	if ((i = GetSocket()) == NOTFOUND) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_LISTENERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		return (0);
	}

	Sockets[i].sdVal = socket(PF_INET, SOCK_STREAM, 0);

	if (Sockets[i].sdVal == INVALID_SOCKET) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_SERVSOCKERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		return(0);
	}

	// retrieve IP address, TCP port
	local_sin.sin_family		= PF_INET;
	local_sin.sin_port			= wPort;
	local_sin.sin_addr.s_addr	= htonl(INADDR_ANY);

	// associate an address with a socket(bind)
	if (bind(Sockets[i].sdVal,(LPSOCKADDR)&local_sin, sizeof(local_sin))
	        == SOCKET_ERROR) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_BINDSOCKERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		closesocket(Sockets[i].sdVal);
		Sockets[i].sdVal = INVALID_SOCKET;
		return (0);
	}

	// listen
	if (listen(Sockets[i].sdVal, MAXCONN) < 0) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_LISTENERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		closesocket(Sockets[i].sdVal);
		Sockets[i].sdVal = INVALID_SOCKET;
		return (0);
	}

	if ((status = WSAAsyncSelect(Sockets[i].sdVal, GetParent(hWndList), WM_WSAASYNC, FD_ACCEPT | FD_READ | FD_CLOSE)) >0 ) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_ASYNCERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		closesocket(Sockets[i].sdVal);
		Sockets[i].sdVal = INVALID_SOCKET;
		return (0);
	}

	Sockets[i].iState = LISTENING;

	return (1);
}

////////////////////////////////
// ResolveServicePort Function
WORD ResolveServicePort()
{
	PSERVENT pse;

	if (!(pse = getservbyname(SERVICE_NAME, "tcp")))
		return (0);
	else
		return (pse->s_port);
}

///////////////////////
// AboutProc Function
BOOL WINAPI AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		CenterDialog(hDlg, TRUE);
		return (TRUE);
	case WM_COMMAND:
		switch (wParam) {
		case IDCANCEL:
		case IDOK:
			EndDialog(hDlg, TRUE);
			break;
		}
	default:
		break;
	}
	return (FALSE);
}

////////////////////////
// SplashProc Function
BOOL WINAPI SplashProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static UINT uTimer;
	static HFONT hFont;
	PAINTSTRUCT ps;
	CHAR szCaption[255];
	HDC	hDC;
	HWND hwndCaption;
	INT copyright = 169;

	switch (msg) {
	case WM_INITDIALOG:
		// center the dialog
		CenterDialog(hDlg, FALSE);

		// start the timer
		uTimer = SetTimer(hDlg, 1, 1500, NULL);

		// create the font
		hDC = GetDC(hDlg);
		hFont =  CreateFont(
		             -MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72),
		             0,
		             0,
		             0,
		             FW_BOLD,
		             FALSE,
		             FALSE,
		             FALSE,
		             DEFAULT_CHARSET,
		             OUT_DEFAULT_PRECIS,
		             CLIP_DEFAULT_PRECIS,
		             DEFAULT_QUALITY,
		             DEFAULT_PITCH,
		             "Comic Sans MS");

		ReleaseDC(hDlg, hDC);
		return (TRUE);
	case WM_COMMAND:
		break;
	case WM_TIMER:
		DeleteObject(hFont);
		KillTimer(hDlg, uTimer);
		EndDialog(hDlg, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hDlg, &ps);
		hwndCaption = GetDlgItem(hDlg, IDC_CAPTION);

		// set the font
		SendMessage(hwndCaption, WM_SETFONT, (WPARAM)hFont, (LPARAM)MAKELPARAM(FALSE, 0));

		// set the caption
		LoadString(hInst, IDS_DLGCAPTION, szCaption, 255);
		sprintf(szCaption, szCaption, (LPCSTR)&copyright);
		SetDlgItemText(hDlg, IDC_CAPTION, szCaption);

		EndPaint(hDlg, &ps);
	default:
		break;
	}
	return (FALSE);
}

///////////////////////////
// CenterDialog Function
VOID CenterDialog(HWND hDlg, BOOL bOwner)
{
	RECT rcDlg, rc, rcOwner;
	HWND hwndOwner;

	// Get the owner window and dialog box rectangles.
	if (bOwner)
		hwndOwner = GetParent(hDlg);
	else
		hwndOwner = GetDesktopWindow();

	GetWindowRect(hwndOwner, &rcOwner);
	GetWindowRect(hDlg, &rcDlg);
	CopyRect(&rc, &rcOwner);

	// Offset the owner and dialog box rectangles so that
	// right and bottom values represent the width and
	// height, and then offset the owner again to discard
	// space taken up by the dialog box.

	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
	OffsetRect(&rc, -rc.left, -rc.top);
	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

	// The new position is the sum of half the remaining
	// space and the owner's original position.

	SetWindowPos(hDlg,
	             HWND_TOP,
	             rcOwner.left + (rc.right / 2),
	             rcOwner.top + (rc.bottom / 2),
	             0, 0,          // ignores size arguments
	             SWP_NOSIZE);
}

//////////////////////
// PrefProc Function
BOOL WINAPI PrefProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		// set dialog items
		if (pls->bIsLogging) {
			SendMessage(GetDlgItem(hDlg, IDC_LOGGING), BM_SETCHECK, (WPARAM)TRUE, 0);
			SendMessage(GetDlgItem(hDlg, IDC_LOGPATH), WM_SETTEXT, 0,
			            (LPARAM)pls->szFileName);
		} else
			EnableWindow(GetDlgItem(hDlg, IDC_LOGPATH), FALSE);

		// center the dialog
		CenterDialog(hDlg, TRUE);
		return (TRUE);
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			// set filename if logging is enabled
			if (IsDlgButtonChecked(hDlg, IDC_LOGGING)) {
				pls->bIsLogging = TRUE;
				GetDlgItemText(hDlg, IDC_LOGPATH, pls->szFileName,
				               _MAX_PATH + _MAX_FNAME);
			} else
				pls->bIsLogging = FALSE;

			EndDialog(hDlg, TRUE);
			break;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			break;
		case IDC_LOGGING:
			if (IsDlgButtonChecked(hDlg, IDC_LOGGING)) {
				EnableWindow(GetDlgItem(hDlg, IDC_LOGPATH), TRUE);
				SetFocus(GetDlgItem(hDlg, IDC_LOGPATH));
			} else
				EnableWindow(GetDlgItem(hDlg, IDC_LOGPATH), FALSE);
			break;
		}
	default:
		break;
	}
	return (FALSE);
}

/////////////////////////
// InitAppData Function
VOID InitAppData()
{
	CHAR szFullPath[_MAX_PATH + _MAX_FNAME];

	// ensure a valid pointer
	if (!pls)
		return;

	// get current directory
	// expected path for .INI file
	GetCurrentDirectory(_MAX_PATH, szFullPath);
	strcat(szFullPath, INIFILE );

	// return logging option
	pls->bIsLogging = GetPrivateProfileInt("Preferences", "Logging",
	                                       0, szFullPath);

	// return logging file name
	GetPrivateProfileString("Preferences", "LogFilePath",
	                        "", pls->szFileName, _MAX_PATH + _MAX_FNAME, szFullPath);

}

////////////////////////////
// UpdateInitData Function
VOID UpdateInitData()
{
	CHAR	szFullPath[_MAX_PATH + _MAX_FNAME];
	CHAR	szBuffer[10];

	// ensure a valid pointer
	if (!pls)
		return;

	// get current directory
	// expected path for .INI file
	GetCurrentDirectory(_MAX_PATH, szFullPath);
	strcat(szFullPath, INIFILE );

	// write the data
	_itoa(pls->bIsLogging, szBuffer, 10);
	WritePrivateProfileString("Preferences", "Logging", szBuffer, szFullPath);

	WritePrivateProfileString("Preferences", "LogFilePath", pls->szFileName, szFullPath);
}

///////////////////////////
// WriteLogEntry Function
VOID WriteLogEntry(HWND hWndList, LPCSTR szLogEntry)
{
	FILE*		fp;
	SCREENLINE	sl;
	LPTIME		currenttime;
	LPSTR		lpszTime;
	time_t		aclock;

	// get time in seconds
	time(&aclock);

	// convert time to structure
	currenttime = localtime(&aclock);

	// null terminate time string
	lpszTime = asctime(currenttime);
	lpszTime[strlen(lpszTime)-1] = '\0';

	// open file for append
	if (!(fp = fopen(pls->szFileName, "a+t"))) {
		// error opening file, disable logging
		pls->bIsLogging = FALSE;
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_FILEOPENERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		UpdateInitData();
		return;
	}

	// write log entry to file
	if (!(fprintf(fp, "%s\t%s\n", lpszTime, szLogEntry))) {
		// error writing to file, disable logging
		pls->bIsLogging = FALSE;
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_FILEWRITEERR, sl.szText, MAXMSGLEN);
		AddListItem(hWndList, &sl);
		UpdateInitData();
	}

	// close the file
	fclose(fp);
}

///////////////////////
// GetSocket Function
INT GetSocket()
{
	INT i;

	for (i = 0; i < MAXCONN; i++)
		if (Sockets[i].sdVal == INVALID_SOCKET)
			return(i);

	return (NOTFOUND);
}

////////////////////////
// FindSocket Function
INT FindSocket(SOCKET sdParam)
{
	INT i;

	for (i = 0; i < MAXCONN; i++)
		if (Sockets[i].sdVal == sdParam)
			return(i);

	return (NOTFOUND);
}

///////////////////////////
// CreateListBox Function
HWND CreateListBox(HWND hWnd)
{
	HWND hWndList;
	RECT rc;

	GetClientRect(hWnd, &rc);

	// create the listbox window
	hWndList = CreateWindow("LISTBOX",
	                        "",
	                        WS_VISIBLE | WS_CHILD | WS_VSCROLL |
	                        LBS_NOTIFY | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT |
	                        LBS_USETABSTOPS | LBS_OWNERDRAWFIXED,
	                        CW_USEDEFAULT,
	                        CW_USEDEFAULT,
	                        (rc.right - rc.left),
	                        (rc.bottom - rc.top),
	                        hWnd,
	                        (HMENU)ID_LISTBOX,
	                        hInst,
	                        NULL);
	return (hWndList);
}

////////////////////////
// ReceiveCmd Function
VOID ReceiveCmd(HWND hWndList, INT i)
{
	RESPONSE		rsp;
	INT				iRc;
	DWORD			dwRtn;
	SCREENLINE		sl;
	CHAR			szBuffer[80];
	DWORD			nSecPerClust, nBytesPerSec,
	nNumFreeClust, nTotalNumClust;
	DISKINFOSTRUCT	dis;

	// turn off FD_READ event until
	// receive algorithm completes
	iRc = WSAAsyncSelect(Sockets[i].sdVal, GetParent(hWndList),
	                     WM_WSAASYNC, FD_CLOSE);

	// receive command
	iRc = recv(Sockets[i].sdVal, (LPSTR)&(Sockets[i].Request),
	           sizeof(REQUEST), NO_FLAGS_SET);

	if (iRc == SOCKET_ERROR) {
		if ((iRc = WSAGetLastError()) != WSAEWOULDBLOCK) {
			sl.uColor	= COLOR_RED;
			LoadString(hInst, IDS_RCVERR, szBuffer, MAXMSGLEN);
			sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
			AddListItem(hWndList, &sl);
			return;
		}
	}

	// check for segmented command
	if (iRc != sizeof(REQUEST)) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_SEGMENTERR, szBuffer, MAXMSGLEN);
		sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
		AddListItem(hWndList, &sl);
		return;
	}

	// turn notification back on
	iRc = WSAAsyncSelect(Sockets[i].sdVal, GetParent(hWndList),
	                     WM_WSAASYNC, FD_ACCEPT | FD_READ | FD_CLOSE);

	rsp.cType		= RSP;
	rsp.cSubType	= Sockets[i].Request.cSubType;
	rsp.cDetails	= Sockets[i].Request.cDetails;
	rsp.cError		= SUCCESS;

	// parse the message request
	switch (Sockets[i].Request.cType) {
	case GET:
		if (Sockets[i].Request.cSubType == DISK) {	// disk info
			switch (Sockets[i].Request.cDetails) {
			case ENUMDRIVES:
				// get drive information
				dwRtn = GetLogicalDriveStrings(MAXMSGSPEC, rsp.cMsgSpec);

				if (dwRtn > MAXMSGSPEC) {
					rsp.iMsgLen = htons(0);
					rsp.cError = ERROREXEC;
				} else {
					rsp.iMsgLen	= htons(LOWORD(dwRtn));
					sl.uColor = COLOR_GREEN;
				}

				break;
			case DISKINFO:
				// find the disk free space information

				// expecting message specific
				// data to include null terminated
				// root path in format "C:\".
				// if length of message specific
				// data is not (3) then an error
				// occcured.
				if (strlen(Sockets[i].Request.cMsgSpec) != 3)
					break;

				if (!(GetDiskFreeSpace(Sockets[i].Request.cMsgSpec,
				                       &nSecPerClust,
				                       &nBytesPerSec,
				                       &nNumFreeClust,
				                       &nTotalNumClust))) {
					rsp.iMsgLen = htons(0);
					rsp.cError	= ERROREXEC;
				} else {
					// calculate total bytes
					// and total free bytes
					dis.lTotalBytes	= htonl(nTotalNumClust * nSecPerClust * nBytesPerSec);
					dis.lFreeBytes	= htonl(nNumFreeClust * nSecPerClust * nBytesPerSec);

					rsp.iMsgLen	= htons(sizeof(DISKINFOSTRUCT));
					memcpy((LPDISKINFOSTRUCT)rsp.cMsgSpec, &dis, sizeof(DISKINFOSTRUCT));
					rsp.cError	= SUCCESS;
				}
				break;
			}
		}
		break;
	case PUT:
		break;
	default:
		rsp.cError	= ERRORBADCMD;
		break;
	}

	// show message notification
	if (rsp.cError != SUCCESS) {
		sl.uColor	= COLOR_RED;
		LoadString(hInst, IDS_REQEXECERR, szBuffer, MAXMSGLEN);
	} else {
		sl.uColor	= COLOR_GREEN;
		LoadString(hInst, IDS_REQSUCCESS, szBuffer, MAXMSGLEN);
	}

	sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
	AddListItem(hWndList, &sl);

	// send the response message
	iRc = send(Sockets[i].sdVal, (LPSTR)&rsp, sizeof(RESPONSE), 0);
	if (iRc == SOCKET_ERROR || iRc < sizeof(RESPONSE)) {
		sl.uColor = COLOR_RED;
		LoadString(hInst, IDS_SENDERR, szBuffer, MAXMSGLEN);
		sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
		AddListItem(hWndList, &sl);
	}
}

////////////////////////////
// ActiveConnProc Function
BOOL WINAPI ActiveConnProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CHAR	szBuffer[80];

	switch (msg) {
		INT i, j;
		static HWND hWndList;

	case WM_INITDIALOG:

		// set window handle for listbox
		hWndList = (HWND)lParam;

		//  refresh list
		SendMessage(hDlg, WM_COMMAND, ID_REFRESH, 0);
		CenterDialog(hDlg, TRUE);
		return (TRUE);
	case WM_COMMAND:
		switch (wParam) {
			int iItem, sdVal;
			SCREENLINE sl;

		case ID_TERMINATE:
			iItem = SendDlgItemMessage(hDlg, IDC_LSTCONN, LB_GETCURSEL, 0, 0);
			if (iItem == LB_ERR) {
				LoadString(hInst, IDS_NOSEL, szBuffer, 80);
				MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
				break;
			}

			// get the socket value
			// for currently selected item
			sdVal = SendDlgItemMessage(hDlg, IDC_LSTCONN, LB_GETITEMDATA, iItem, 0);
			if (sdVal == LB_ERR) {
				LoadString(hInst, IDS_SOCKERRLST, szBuffer, 80);
				MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
				break;
			}

			LoadString(hInst, IDS_KILLSOCK, szBuffer, 80);
			if (MessageBox(hDlg, szBuffer, "Kill Connection", MB_ICONQUESTION |
			               MB_YESNO | MB_DEFBUTTON2) == IDYES) {
				i = FindSocket(sdVal);
				if (i == NOTFOUND) {
					LoadString(hInst, IDS_ERRNOSOCK, szBuffer, 80);
					MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
					break;
				}
				// add item to screen list
				sl.uColor = COLOR_RED;
				LoadString(hInst, IDS_SERVKILL, szBuffer, 80);
				sprintf(sl.szText, szBuffer, Sockets[i].IPAddress);
				AddListItem(hWndList, &sl);

				// remove socket from array of connected sockets
				closesocket(Sockets[i].sdVal);
				Sockets[i].sdVal	= INVALID_SOCKET;
				Sockets[i].iState	= FREE;

				//  refresh list
				SendMessage(hDlg, WM_COMMAND, ID_REFRESH, 0);
			}
			break;
		case ID_REFRESH:
			// clear listbox
			SendDlgItemMessage(hDlg, IDC_LSTCONN, LB_RESETCONTENT, 0, 0);

			// iterate through sockets
			// displaying connected items
			for (i = 0, j = 0; i < MAXCONN; i++) {
				if (Sockets[i].iState == CONNECTED) {
					// set IP address
					SendDlgItemMessage(hDlg, IDC_LSTCONN, LB_ADDSTRING, 0,
					                   (LPARAM)Sockets[i].IPAddress);

					// set socket descriptor value
					SendDlgItemMessage(hDlg, IDC_LSTCONN, LB_SETITEMDATA, j,
					                   (LPARAM)Sockets[i].sdVal);
					j++;
				}
			}
			break;
		case IDCANCEL:
		case IDOK:
			EndDialog(hDlg, TRUE);
			break;
		}
	default:
		break;
	}
	return (FALSE);
}