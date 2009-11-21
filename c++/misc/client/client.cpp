/*--------------------------------------------
	Module	:	CLIENT.CPP
	Date	: 	07/15/1997
	Purpose	:	Component Client
---------------------------------------------*/

#include "capp.h"
#include "resource.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, INT nCmdShow)
{
	MSG	msg;

	CApp* pApp = new CApp(hInstance, nCmdShow);
	if (!pApp) return (0);

	// Initialize application
	if (!pApp->Init(_T("ComponentClient")))
		return (0);

	// Create window
	if (!pApp->Create(_T("Component Client")))
		return (0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (pApp) delete pApp;

	return (msg.wParam);
}

/*---------------------------------------------------------
				BEGIN CAPP IMPLEMENTATION
---------------------------------------------------------*/

CApp :: CApp(HINSTANCE hInstance, INT nCmdShow) : m_fInitialized(FALSE)
{
	m_hInst 			= hInstance;
	m_nCmdShow			= nCmdShow;
	m_hWnd				= NULL;
	m_hWndList			= NULL;
	m_hWndStatus		= NULL;
	m_cRef				= 0;
	m_fExe				= FALSE;
	m_pIMisc			= NULL;
	m_szClassName[0] 	= '\0';
}

BOOL CApp :: Init(LPCTSTR lpszClassName)
{
	// Initialize OLE Library
	m_fInitialized = SUCCEEDED(CoInitialize(NULL));

	if (!lpszClassName)
		return (FALSE);

#ifdef _UNICODE
	wcscpy (m_szClassName, lpszClassName);
#else
	strcpy (m_szClassName, lpszClassName);
#endif

	// Create Frame class
	m_wndClass.style			= CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc		= (WNDPROC)MainWndProc;
	m_wndClass.cbClsExtra		= 0;
	m_wndClass.cbWndExtra		= 0;
	m_wndClass.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN));
	m_wndClass.hInstance		= m_hInst;
	m_wndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hbrBackground	= NULL;
	m_wndClass.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU);
	m_wndClass.lpszClassName	= m_szClassName;

	if (!RegisterClass(&m_wndClass))
		return FALSE;

	return TRUE;
}

BOOL CApp :: Create(LPCTSTR lpszCaption)
{
	InitCommonControls();

	// Create the mainframe window
	m_hWnd = CreateWindowEx(
	             0L,
	             m_szClassName,
	             lpszCaption,
	             WS_OVERLAPPEDWINDOW |
	             WS_CLIPCHILDREN, 		// Window style.
	             CW_USEDEFAULT,          // Default horizontal position.
	             CW_USEDEFAULT,          // Default vertical position.
	             350,					// Width.
	             400,					// Height.
	             NULL,                   // Overlapped windows have no parent.
	             NULL,                   // Use the window class menu.
	             m_hInst,				// This instance owns this window.
	             this
	         );

	assert(IsWindow(m_hWnd));

	ShowWindow(m_hWnd, m_nCmdShow);
	UpdateWindow(m_hWnd);

	return (m_hWnd != NULL);
}

BOOL CApp :: GetDate(BSTR& bstrDate)
{
	HRESULT	hr;

	assert(m_pIMisc);

	hr = m_pIMisc->GetDate(&bstrDate);

	return SUCCEEDED(hr);
}

BOOL CApp :: GetTime(BSTR& bstrTime)
{
	HRESULT hr;

	assert(m_pIMisc);

	hr = m_pIMisc->GetTime(&bstrTime);

	return SUCCEEDED(hr);
}

BOOL CApp :: GetDateTime(BSTR& bstrDateTime)
{
	HRESULT hr;

	assert(m_pIMisc);

	hr = m_pIMisc->GetDateTime(&bstrDateTime);

	return SUCCEEDED(hr);
}

BOOL CApp :: GetDriveSpace()
{
	BOOL fRtn = ::DialogBoxParam(m_hInst, MAKEINTRESOURCE(IDD_DRIVELETTER),
	                             m_hWnd, (DLGPROC)DriveProc, (LPARAM)this);

	return fRtn;
}

BOOL CApp :: EnumDrives(BSTR& bstrDrives)
{
	HRESULT hr;

	assert(m_pIMisc);

	hr = m_pIMisc->EnumDrives(&bstrDrives);

	return SUCCEEDED(hr);
}

VOID CApp :: DrawStatusBar(LPDRAWITEMSTRUCT lpDIS)
{
	int			nHeight, nWidth;
	int			x, y;

	HICON hIcon = (HICON)lpDIS->itemData;
	assert(hIcon);

	nHeight = (lpDIS->rcItem.bottom - lpDIS->rcItem.top) + lpDIS->rcItem.top * 2;
	nWidth	= (lpDIS->rcItem.right - lpDIS->rcItem.left) + lpDIS->rcItem.left * 2;

	x = (nWidth - ICON_WIDTH) / 2;
	y = (nHeight - ICON_HEIGHT) / 2;

	DrawIconEx(lpDIS->hDC, x, y, hIcon,
	           ICON_WIDTH, ICON_HEIGHT, NULL, NULL, DI_NORMAL);
}

VOID CApp :: DrawListBox(LPDRAWITEMSTRUCT lpDIS)
{
	INT 				y;
	TCHAR 				tchBuffer[255];
	HBRUSH 				hBrush, hBrushOld;
	TEXTMETRIC			tm;

	// Get item text
	SendMessage(lpDIS->hwndItem, LB_GETTEXT,
	            lpDIS->itemID, (LPARAM) tchBuffer);

	// Retrieve position
	GetTextMetrics(lpDIS->hDC, &tm);

	y = (lpDIS->rcItem.bottom + lpDIS->rcItem.top -
	     tm.tmHeight) / 2;

	// Check if item is selected
	if (lpDIS->itemState & ODS_SELECTED)
		// Draw selected rectangle
		hBrush = CreateSolidBrush(COLOR_YELLOW);
	else
		// Draw default background
		hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

	hBrushOld = (HBRUSH)SelectObject(lpDIS->hDC, hBrush);
	FillRect(lpDIS->hDC, &(lpDIS->rcItem), hBrush);

	if (lpDIS->itemState & ODS_SELECTED) {
		HPEN hPen1, hPen2, hPenOld;

		// Draw the highlight
		hPen1 = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHIGHLIGHT));
		hPen2 = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

		hPenOld = (HPEN)SelectObject(lpDIS->hDC, hPen1);

		MoveToEx(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, NULL);
		LineTo(lpDIS->hDC, lpDIS->rcItem.right, lpDIS->rcItem.top);

		SelectObject(lpDIS->hDC, hPen2);

		MoveToEx(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.bottom - 1, NULL);
		LineTo(lpDIS->hDC, lpDIS->rcItem.right, lpDIS->rcItem.bottom - 1);

		SelectObject(lpDIS->hDC, hPenOld);
		DeleteObject(hPen1);
		DeleteObject(hPen2);
	}

	SelectObject(lpDIS->hDC, hBrushOld);
	DeleteObject(hBrush);

	// Set background mode
	SetBkMode(lpDIS->hDC, TRANSPARENT);

	// Set text color
	SetTextColor(lpDIS->hDC,
	             lpDIS->itemState & ODS_SELECTED ? COLOR_RED : COLOR_BLUE);

	// Display the text item
	TextOut(lpDIS->hDC,
	        2,
	        y,
	        tchBuffer,
#ifdef _UNICODE
	        wcslen(tchBuffer)
#else
	        strlen(tchBuffer)
#endif
	       );

}

VOID CApp :: Trace(LPCTSTR lpszMessage)
{
	assert (IsWindow(m_hWndList));
	assert (lpszMessage);

	SendMessage(m_hWndList, LB_ADDSTRING, 0, (LPARAM)lpszMessage);
}

VOID CApp :: Trace(wchar_t* lpszMessage)
{
	assert(IsWindow(m_hWndList));
	assert(lpszMessage);

#ifndef _UNICODE
	TCHAR	szMessage[256];

	WideCharToMultiByte(CP_ACP, 0, lpszMessage,
	                    -1, szMessage, 255, NULL, NULL);

	SendMessage(m_hWndList, LB_ADDSTRING, 0, (LPARAM)szMessage);
#else
	SendMessage(m_hWndList, LB_ADDSTRING, 0, (LPARAM)lpszMessage);
#endif
}

VOID CApp :: Trace(LONG lNumber)
{
	UINT nFlags = LMEM_FIXED | LMEM_DISCARDABLE;

	LPTSTR lpszNumber = (LPTSTR)LocalAlloc(nFlags, 128);
	if (!lpszNumber)
		return;

#ifdef _UNICODE
	_ltow(lNumber, lpszNumber, 10);
#else
	_ltoa(lNumber, lpszNumber, 10);
#endif

	Trace(lpszNumber);

	LocalFree(lpszNumber);
}

VOID CApp :: StatusTrace(LPCTSTR lpszMessage)
{
	assert(m_hWndStatus);

	SendMessage(m_hWndStatus, SB_SETTEXT, 1, (LPARAM)lpszMessage);
}

CApp::~CApp()
{
	if (IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);

	if (m_pIMisc) {
		m_pIMisc->Release();
		m_pIMisc = NULL;
	}

	if (m_fInitialized)
		CoUninitialize();
}

/*---------------------------------------------------------
				END OF CAPP IMPLEMENTATION
---------------------------------------------------------*/

/*---------------------------------------------------------
				BEGIN WINDOW PROCS
---------------------------------------------------------*/

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
{
	static PAPP		pApp;
	LPCREATESTRUCT	lpcs;
	HMENU			hMenu;
	INT				cx, cy, yStatus;
	RECT			rcStatus;

	switch (message) {
	case WM_COMMAND:
		switch LOWORD(wParam) {
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case ID_OPTIONS_DLL:
			CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_EXE, MF_BYCOMMAND | MF_UNCHECKED);

			pApp->m_fExe = FALSE;

			break;
		case ID_OPTIONS_EXE:
			CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_OPTIONS_DLL, MF_BYCOMMAND | MF_UNCHECKED);

			pApp->m_fExe = TRUE;

			break;
		case ID_OPTIONS_CLEAR:
			assert(pApp->m_hWndList);
			SendMessage(pApp->m_hWndList, LB_RESETCONTENT, 0, 0);
			break;
		case ID_CREATEOBJECT:
			HRESULT hr;
			DWORD	dwClsCtx;

			assert(pApp->m_pIMisc == NULL && pApp->m_cRef == 0);

			SetCapture(hWnd);
			SetCursor(LoadCursor(NULL, IDC_WAIT));

			dwClsCtx = (pApp->m_fExe) ? CLSCTX_LOCAL_SERVER
			           : CLSCTX_INPROC_SERVER;

			// Create an instance of the object
			hr = ::CoCreateInstance(CLSID_Miscellaneous,
			                        NULL,
			                        dwClsCtx,
			                        IID_IMiscellaneous,
			                        (PPVOID)&pApp->m_pIMisc);

			if (SUCCEEDED(hr)) {
				hMenu = GetMenu(hWnd);
				EnableMenuItem(hMenu, LOWORD(wParam), MF_GRAYED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_OPTIONS_DLL, MF_GRAYED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_OPTIONS_EXE, MF_GRAYED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_DESTROYOBJECT, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_GETDATE, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_GETTIME, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_GETDATETIME, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_GETDRIVESPACE, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_ENUMDRIVES, MF_ENABLED | MF_BYCOMMAND);
				EnableMenuItem(hMenu, ID_GETCOMPUTERNAME, MF_ENABLED | MF_BYCOMMAND);

				pApp->m_cRef = 1;

				pApp->StatusTrace((pApp->m_fExe) ? _T("Exe Object Created.") : _T("Dll Object Created."));
			} else
				pApp->StatusTrace((pApp->m_fExe) ? _T("Exe Object Not Created.") : _T("Dll Object Not Created."));

			SetCursor(pApp->m_wndClass.hCursor);
			ReleaseCapture();

			break;
		case ID_DESTROYOBJECT:

			assert(pApp->m_pIMisc);

			while (pApp->m_cRef--) {
				pApp->m_pIMisc->Release();

				CoFreeUnusedLibraries();
				pApp->m_pIMisc = NULL;
			}

			pApp->m_cRef = 0;

			hMenu = GetMenu(hWnd);
			EnableMenuItem(hMenu, LOWORD(wParam), MF_GRAYED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_OPTIONS_DLL, MF_ENABLED| MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_OPTIONS_EXE, MF_ENABLED| MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_CREATEOBJECT, MF_ENABLED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_GETDATE, MF_GRAYED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_GETTIME, MF_GRAYED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_GETDATETIME, MF_GRAYED| MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_GETDRIVESPACE, MF_GRAYED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_ENUMDRIVES, MF_GRAYED | MF_BYCOMMAND);
			EnableMenuItem(hMenu, ID_GETCOMPUTERNAME, MF_GRAYED | MF_BYCOMMAND);

			pApp->StatusTrace(_T("Object Destroyed."));

			break;
		case ID_GETDATE:
			BSTR bstrDate;
			if (pApp->GetDate(bstrDate))
				pApp->Trace(bstrDate);
			else
				pApp->Trace(_T("Error getting date."));

			if (bstrDate)
				::SysFreeString(bstrDate);
			break;
		case ID_GETTIME:
			BSTR bstrTime;
			if (pApp->GetTime(bstrTime))
				pApp->Trace(bstrTime);
			else
				pApp->Trace(_T("Error getting time."));

			if (bstrTime)
				::SysFreeString(bstrTime);
			break;
		case ID_GETDATETIME:
			BSTR bstrDateTime;
			if (pApp->GetDateTime(bstrDateTime))
				pApp->Trace(bstrDateTime);
			else
				pApp->Trace(_T("Error getting Date / Time."));

			if (bstrDateTime)
				::SysFreeString(bstrDateTime);
			break;
		case ID_GETDRIVESPACE:
			pApp->GetDriveSpace();
			break;
		case ID_ENUMDRIVES:
			BSTR bstrDrives;
			if (pApp->EnumDrives(bstrDrives))
				pApp->Trace(bstrDrives);
			else
				pApp->Trace(_T("Error getting drives."));

			if (bstrDrives)
				::SysFreeString(bstrDrives);
			break;
		case ID_ABOUT:
			::DialogBoxParam(pApp->m_hInst, MAKEINTRESOURCE(IDD_ABOUT),
			                 hWnd, (DLGPROC)AboutProc, (LPARAM)pApp);
			break;
		default:
			break;
		};
		break;
	case WM_CREATE:
		lpcs = (LPCREATESTRUCT)lParam;
		assert(lpcs != NULL);

		pApp = (PAPP)lpcs->lpCreateParams;
		assert(pApp != NULL);

		cx = (GetSystemMetrics(SM_CXFULLSCREEN) - lpcs->cx) / 2 ;
		cy = (GetSystemMetrics(SM_CYFULLSCREEN) - lpcs->cy) / 2;

		// Create Status Bar
		pApp->m_hWndStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
		                                        NULL, hWnd, IDC_STATUS);

		assert(pApp->m_hWndStatus);

		// Set the parts
		INT aWidths[2];
		aWidths[0] = ICON_WIDTH + 2;
		aWidths[1] = -1;

		SendMessage(pApp->m_hWndStatus, SB_SETPARTS, 2, (LPARAM)aWidths);

		// Set Part 0 as owner drawn
		HICON hIcon;
		hIcon = (HICON)LoadImage(pApp->m_hInst,
		                         MAKEINTRESOURCE(IDI_WORLD),
		                         IMAGE_ICON,
		                         ICON_WIDTH, ICON_HEIGHT,
		                         0);

		SendMessage(pApp->m_hWndStatus, SB_SETTEXT, (WPARAM) 0 | SBT_OWNERDRAW, (LPARAM)hIcon);

		// Create the list window
		pApp->m_hWndList = CreateWindowEx(
		                       WS_EX_OVERLAPPEDWINDOW,
		                       _T("LISTBOX"),
		                       NULL,
		                       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
		                       WS_VSCROLL | LBS_NOINTEGRALHEIGHT |
		                       LBS_USETABSTOPS | LBS_OWNERDRAWFIXED |
		                       LBS_HASSTRINGS,								// Window style.
		                       0,	                  						// Default horizontal position.
		                       0,											// Default vertical position.
		                       lpcs->cx,                  					// Width.
		                       lpcs->cy,                					// Height.
		                       hWnd,			                           	// Window parent
		                       NULL,                           			// Use the window class menu.
		                       pApp->m_hInst,								// This instance owns this window.
		                       pApp);

		assert(IsWindow(pApp->m_hWndList));

		HDC		hDC;
		HFONT	hFont;
		LOGFONT lf;

		hDC = GetDC(pApp->m_hWnd);

		lf.lfHeight			= -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		lf.lfWidth			= 0;
		lf.lfEscapement		= 0;
		lf.lfOrientation	= 0;
		lf.lfWeight			= FW_DEMIBOLD;
		lf.lfItalic			= 0;
		lf.lfUnderline		= 0;
		lf.lfStrikeOut		= 0;
		lf.lfCharSet		= DEFAULT_CHARSET;
		lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
		lf.lfQuality		= DEFAULT_QUALITY;
		lf.lfPitchAndFamily	= DEFAULT_PITCH;
#ifdef _UNICODE
		wcscpy(lf.lfFaceName, _T("Tahoma"));
#else
		strcpy(lf.lfFaceName, _T("Tahoma"));
#endif

		hFont = CreateFontIndirect(&lf);

		// set font for list box
		SendMessage(pApp->m_hWndList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

		ReleaseDC(pApp->m_hWnd, hDC);

		MoveWindow(hWnd, cx, cy, lpcs->cx, lpcs->cy, FALSE);

		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);

		GetWindowRect(pApp->m_hWndStatus, &rcStatus);
		yStatus = (rcStatus.bottom - rcStatus.top);

		MoveWindow(pApp->m_hWndList, 0, 0, cx, cy - yStatus, TRUE);
		SendMessage(pApp->m_hWndStatus, WM_SIZE, wParam, lParam);
		break;
	case WM_MEASUREITEM:	// Owner drawn list box
		LPMEASUREITEMSTRUCT lpMIS;
		HDC					hdcList;
		TEXTMETRIC			tm;

		lpMIS= (LPMEASUREITEMSTRUCT)lParam;

		hdcList = GetDC(pApp->m_hWndList);

		GetTextMetrics(hdcList, &tm);

		lpMIS->itemWidth	= tm.tmAveCharWidth;
		lpMIS->itemHeight	= tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(pApp->m_hWndList, hdcList);
		break;
	case WM_DRAWITEM:
		LPDRAWITEMSTRUCT	lpDIS;

		lpDIS = (LPDRAWITEMSTRUCT)lParam;

		if (lpDIS->itemID == -1)
			break;

		if (lpDIS->hwndItem == pApp->m_hWndStatus)
			pApp->DrawStatusBar(lpDIS);
		else if (lpDIS->hwndItem == pApp->m_hWndList)
			pApp->DrawListBox(lpDIS);

		break;
	case WM_NOTIFY:
		LPNMHDR pnmh;

		pnmh = (LPNMHDR)lParam;

		if (pnmh->hwndFrom == pApp->m_hWndStatus)
			if (pnmh->code == NM_RCLICK) {
				POINT	pt, spt;

				// Get Cursor position
				// saving screen coordinates
				GetCursorPos(&spt);

				memcpy(&pt, &spt, sizeof(POINT));

				// Convert to status client coordinates
				ScreenToClient(pApp->m_hWndStatus, &pt);

				// Ensure this point is within
				// the first part of the status bar
				INT aParts[2];

				SendMessage(pApp->m_hWndStatus, SB_GETPARTS, 2, (LPARAM)aParts);
				if (pt.x <= aParts[0]) {
					HMENU hMenu;
					hMenu = GetSubMenu(GetMenu(hWnd), 2);
					assert(hMenu);

					TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON,
					               spt.x, spt.y, 0, hWnd, NULL);
				}
			}
		break;
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		// Forward message to common controls
		SendMessage(pApp->m_hWndStatus, WM_SETTINGCHANGE, wParam, lParam);
		break;
	case WM_DESTROY:
		DestroyWindow(pApp->m_hWndList);
		DestroyWindow(pApp->m_hWndStatus);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
}

//////////////////////////////////
//
// DriveProc() Function
//
BOOL CALLBACK DriveProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PAPP pApp;
	switch (msg) {
	case WM_INITDIALOG:
		pApp = (PAPP)lParam;
		assert(pApp);

		HWND hwndCombo;
		hwndCombo = GetDlgItem(hDlg, IDC_DRIVELETTER);
		assert(hwndCombo);

		// Build list of drives
		BSTR bstrDrives;

		if (!pApp->EnumDrives(bstrDrives))
			return FALSE;

#ifndef _UNICODE
		TCHAR	szDrives[512];
		LPTSTR	lpszToken;

		WideCharToMultiByte(CP_ACP, 0, bstrDrives,
		                    -1, szDrives, 512, NULL, NULL);

		lpszToken = strtok(szDrives, _T("~"));
#else
		wchar_t* lpszToken;

		lpszToken = wcstok(bstrDrives, _T("~"));
#endif // _UNICODE

		while (lpszToken) {
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)lpszToken);
#ifdef _UNICODE
			lpszToken = wcstok(NULL, _T("~"));
#else
			lpszToken = strtok(NULL, _T("~"));
#endif
		}

		// Free allocated memory
		if (bstrDrives)
			::SysFreeString(bstrDrives);

		// Default to first item
		SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			break;
		case IDOK:
			wchar_t	szDrive[8];
			TCHAR	szTemp[8];
			BSTR	bstrDrive;
			INT		nSel;

			nSel = SendDlgItemMessage(hDlg, IDC_DRIVELETTER, CB_GETCURSEL, 0, 0);
			if (nSel != CB_ERR) {
				HRESULT hr;
				__int64 lBytes;

				assert(pApp->m_pIMisc);

				GetWindowText(GetDlgItem(hDlg, IDC_DRIVELETTER), szTemp, 8);

#ifndef _UNICODE
				MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szDrive, 8);
#else
				wcscpy(szDrive, szTemp);
#endif
				bstrDrive = ::SysAllocString(szDrive);
				if (!bstrDrive)
					return 0;

				hr = pApp->m_pIMisc->GetDriveSpace(bstrDrive, &lBytes);
				if (SUCCEEDED(hr)) {
					TCHAR szMessage[50];
					wsprintf(szMessage, _T("Drive %s %I64d bytes."), szTemp, lBytes);
					pApp->Trace(szMessage);
				} else
					pApp->Trace(_T("Error getting drive info."));


				::SysFreeString(bstrDrive);

				EndDialog(hDlg, TRUE);
			}
			break;
		}
	default:
		return FALSE;
	};
}

//////////////////////////////////
//
// AboutProc() Function
//
BOOL CALLBACK AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PAPP pApp;
	switch (msg) {
	case WM_INITDIALOG:
		TCHAR szBuildMsg[50];
		TCHAR szTemp[25];

		pApp = (PAPP)lParam;
		assert(pApp);

		LoadString(pApp->m_hInst, IDS_BUILD, szTemp, 25);
#ifndef _UNICODE
		wsprintf(szBuildMsg, szTemp, _T("ANSI"));
#else
		wsprintf(szBuildMsg, szTemp, _T("Unicode"));
#endif // _UNICODE

		SetDlgItemText(hDlg, IDC_BUILD, szBuildMsg);

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hDlg, TRUE);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return FALSE;
}
