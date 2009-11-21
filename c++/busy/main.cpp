

// main.cpp
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <process.h>
#include <time.h>
#include "resource.h"
static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg,
                                   WPARAM wParam, LPARAM lParam);
static BOOL onInit(HWND hWnd, HWND hWndFocus, LPARAM lParam);
static void onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify);
static HBRUSH onColor(HWND hWnd, HDC hDC, HWND hWndChild, int type);
static void onClose(HWND hWnd);
static void onDestroy(HWND hWnd);
static void onExpand(HWND hWnd);
static BOOL centerWindow(HWND hWnd, HWND hWndParent);
static void progressProc(LPVOID param);
static void outputProc(LPVOID param);
static BOOL setMessageFont(HWND hWnd);
static BOOL setOutputFont(HWND hWnd);
#define COLOR_RED	PALETTERGB(128, 0, 0)
#define COLOR_WHITE	RGB(255, 255, 255)
#define COLOR_BLACK RGB(0, 0, 0)
#define COLOR_GREEN	RGB(0, 255, 0)
#define COLOR_PINK	RGB(255, 200, 200)
typedef struct {
	HBRUSH dlgBrush;	// dialog brush
	HBRUSH outBrush;	// output brush
	HANDLE hEvent;		// event object
} WNDDATA, *LPWNDDATA;
/////////////////////////////////////////////////////////////////////////////
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance,
	                          MAKEINTRESOURCE(IDR_ACCELERATOR));
	if (hAccel == NULL)
		return 1;
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_PROCDLG),
	                         NULL, (DLGPROC)DialogProc);
	if (hDlg == NULL)
		return 1;
	ShowWindow(hDlg, nShowCmd);
	UpdateWindow(hDlg);
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		if (!TranslateAccelerator(hDlg, hAccel, &msg))
			TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return HANDLE_WM_INITDIALOG(hWnd, wParam, lParam, onInit);
	case WM_COMMAND:
		HANDLE_WM_COMMAND(hWnd, wParam, lParam, onCommand);
		return TRUE;
	case WM_CLOSE:
		HANDLE_WM_CLOSE(hWnd, wParam, lParam, onClose);
		return TRUE;
	case WM_DESTROY:
		HANDLE_WM_DESTROY(hWnd, wParam, lParam, onDestroy);
		return TRUE;
	case WM_CTLCOLORSTATIC:
		return HANDLE_WM_CTLCOLORSTATIC(hWnd, wParam, lParam, onColor);
	case WM_CTLCOLORDLG:
		return HANDLE_WM_CTLCOLORDLG(hWnd, wParam, lParam, onColor);
	default:
		break;
	}
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
void onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
	switch (id) {
	case IDCANCEL:
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	case IDC_EXPAND:
		onExpand(hWndCtl);
		break;
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////
BOOL onInit(HWND hWnd, HWND hWndFocus, LPARAM lParam)
{
	LPWNDDATA pdata = (LPWNDDATA)LocalAlloc(LPTR, sizeof(WNDDATA));
	pdata->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	pdata->dlgBrush = CreateSolidBrush(COLOR_RED);
	pdata->outBrush = CreateSolidBrush(COLOR_BLACK);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)pdata);
	// set the message font
	if (!setMessageFont(GetDlgItem(hWnd, IDC_MESSAGE))) {
		DestroyWindow(hWnd);
		return FALSE;
	}
	// set the output font
	if (!setOutputFont(GetDlgItem(hWnd, IDC_OUTPUT))) {
		DestroyWindow(hWnd);
		return FALSE;
	}

	centerWindow(hWnd, GetDesktopWindow());
	// create the progress worker thread
	if (!_beginthread(progressProc, 0, GetDlgItem(hWnd, IDC_PROGRESS))) {
		DestroyWindow(hWnd);
		return FALSE;
	}
	// create the output worker thread
	if (!_beginthread(outputProc, 0, GetDlgItem(hWnd, IDC_OUTPUT))) {
		DestroyWindow(hWnd);
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
HBRUSH onColor(HWND hWnd, HDC hDC, HWND hWndChild, int type)
{
	LPWNDDATA pdata = (LPWNDDATA)GetWindowLong(hWnd, GWL_USERDATA);
	SetBkMode(hDC, TRANSPARENT);

	if (hWndChild == GetDlgItem(hWnd, IDC_OUTPUT)) {
		SetTextColor(hDC, COLOR_GREEN);
		return pdata->outBrush;
	} else {
		SetTextColor(hDC, COLOR_WHITE);
		return pdata->dlgBrush;
	}
}
/////////////////////////////////////////////////////////////////////////////
BOOL centerWindow(HWND hWnd, HWND hWndParent)
{
	RECT rc, rcParent;
	GetWindowRect(hWnd, &rc);
	GetWindowRect(hWndParent, &rcParent);
	int width = abs(rc.right - rc.left);
	int height = abs(rc.bottom - rc.top);
	POINT pt;
	pt.x = abs(rcParent.right - rcParent.left) / 2;
	pt.y = abs(rcParent.bottom - rcParent.top) / 2;
	ClientToScreen(hWndParent, &pt);
	pt.x -= width / 2;
	pt.y -= height / 2;
	return MoveWindow(hWnd, pt.x, pt.y, width, height, FALSE);
}
/////////////////////////////////////////////////////////////////////////////
void progressProc(LPVOID param)
{
	HWND hWnd = (HWND)param;
	RECT rc, rcSegment;
	GetClientRect(hWnd, &rc);
	InflateRect(&rc, -1, -1);
	int interval = (rc.right - rc.left) / 20;
	rcSegment.left = rc.left;
	rcSegment.top = rc.top;
	rcSegment.bottom = rc.bottom;
	rcSegment.right = rcSegment.left + interval;
	HBRUSH hBrush = CreateSolidBrush(COLOR_PINK);
	HDC hDC = GetDC(hWnd);
	LPWNDDATA pdata = (LPWNDDATA)GetWindowLong(GetParent(hWnd), GWL_USERDATA);
	HANDLE hEvent = pdata->hEvent;
	time_t old = time(NULL);
	for (;;) {
		DWORD rtn = WaitForSingleObject(hEvent, 10);
		if (rtn == WAIT_FAILED || rtn == WAIT_OBJECT_0)
			break;
		if (time(NULL) >= old + 1) {
			rcSegment.right += interval;
			old = time(NULL);
		}
		if (rcSegment.right > rc.right) {
			rcSegment.right = rcSegment.left + interval;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}
		FillRect(hDC, &rcSegment, hBrush);
	}
	ReleaseDC(hWnd, hDC);
	DeleteObject(hBrush);
}
/////////////////////////////////////////////////////////////////////////////
void outputProc(LPVOID param)
{
	HWND hWnd = (HWND)param;
	RECT rc;
	GetClientRect(hWnd, &rc);
	TCHAR output[4096];
	LoadString(GetModuleHandle(NULL), IDS_OUTPUT, output, sizeof(output));
	HBRUSH hBrush = CreateSolidBrush(COLOR_WHITE);
	HDC hDC = GetDC(hWnd);
	LPWNDDATA pdata = (LPWNDDATA)GetWindowLong(GetParent(hWnd), GWL_USERDATA);
	HANDLE hEvent = pdata->hEvent;
	HFONT hFont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, COLOR_GREEN);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
	time_t old = time(NULL);
	const char *poutput = output;
	for (;;) {
		DWORD rtn = WaitForSingleObject(hEvent, 10);
		if (rtn == WAIT_FAILED || rtn == WAIT_OBJECT_0)
			break;
		if (time(NULL) >= old + 1) {
			old = time(NULL);
			poutput = _tcschr(poutput, _T('\n'));
			if (!poutput) poutput = output;
			else ++poutput;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		DrawText(hDC, poutput, _tcslen(poutput) * sizeof(TCHAR),
		         &rc, DT_EDITCONTROL);
	}
	SelectObject(hDC, hOldFont);
	ReleaseDC(hWnd, hDC);
	DeleteObject(hBrush);
}
/////////////////////////////////////////////////////////////////////////////
void onClose(HWND hWnd)
{
	DestroyWindow(hWnd);
}
/////////////////////////////////////////////////////////////////////////////
void onDestroy(HWND hWnd)
{
	LPWNDDATA pdata = (LPWNDDATA)GetWindowLong(hWnd, GWL_USERDATA);
	SetEvent(pdata->hEvent);
	CloseHandle(pdata->hEvent);
	DeleteObject(pdata->dlgBrush);
	DeleteObject(pdata->outBrush);
	LocalFree(pdata);
	HFONT hFontMsg = (HFONT)SendMessage(GetDlgItem(hWnd, IDC_MESSAGE),
	                                    WM_GETFONT, 0, 0);
	DeleteObject(hFontMsg);
	HFONT hFontOut = (HFONT)SendMessage(GetDlgItem(hWnd, IDC_OUTPUT),
	                                    WM_GETFONT, 0, 0);
	DeleteObject(hFontOut);

	PostQuitMessage(0);
}
/////////////////////////////////////////////////////////////////////////////
BOOL setMessageFont(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	int height = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	ReleaseDC(hWnd, hDC);
	HFONT hFont = CreateFont(height,
	                         0,						/* width */
	                         0,						/* escapement */
	                         0,						/* orientation */
	                         FW_BOLD,				/* weight */
	                         0,						/* italic */
	                         0,						/* underline */
	                         0,						/* strikeout */
	                         DEFAULT_CHARSET,		/* character set */
	                         OUT_DEFAULT_PRECIS,		/* output precision */
	                         CLIP_CHARACTER_PRECIS,	/* clip precision */
	                         DEFAULT_QUALITY,		/* quality */
	                         DEFAULT_PITCH |
	                         FF_DONTCARE,			/* pitch and family */
	                         _T("Tahoma")			/* face name */
	                        );
	if (hFont == NULL)
		return FALSE;
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
BOOL setOutputFont(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	int height = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	ReleaseDC(hWnd, hDC);
	HFONT hFont = CreateFont(height,
	                         0,						/* width */
	                         0,						/* escapement */
	                         0,						/* orientation */
	                         FW_DONTCARE,			/* weight */
	                         0,						/* italic */
	                         0,						/* underline */
	                         0,						/* strikeout */
	                         DEFAULT_CHARSET,		/* character set */
	                         OUT_DEFAULT_PRECIS,		/* output precision */
	                         CLIP_CHARACTER_PRECIS,	/* clip precision */
	                         DEFAULT_QUALITY,		/* quality */
	                         DEFAULT_PITCH |
	                         FF_DONTCARE,			/* pitch and family */
	                         _T("Courier New")		/* face name */
	                        );
	if (hFont == NULL)
		return FALSE;
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
void onExpand(HWND hWnd)
{
	static bool isexpanded = true;
	HWND hDlg = GetParent(hWnd);
	RECT units;
	units.left = 0;
	units.top = 0;
	units.right = 231;
	isexpanded = !isexpanded;
	TCHAR str[_MAX_PATH];
	if (!isexpanded) {
		LoadString(GetModuleHandle(NULL), IDS_UNEXPANDED, str, sizeof(str));
		units.bottom = 87;
	} else {
		LoadString(GetModuleHandle(NULL), IDS_EXPANDED, str, sizeof(str));
		units.bottom = 178;
	}
	LONG style = GetWindowLong(hDlg, GWL_STYLE);
	LONG exstyle = GetWindowLong(hDlg, GWL_EXSTYLE);
	MapDialogRect(hDlg, &units);
	AdjustWindowRectEx(&units, style, FALSE, exstyle);
	units.right += GetSystemMetrics(SM_CXBORDER);
	units.bottom += GetSystemMetrics(SM_CYBORDER);
	SetWindowPos(hDlg, NULL, 0, 0,
	             units.right - units.left, units.bottom - units.top,
	             SWP_NOMOVE | SWP_SHOWWINDOW);

	SetWindowText(hWnd, str);
}
