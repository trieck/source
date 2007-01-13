
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <commdlg.h>
#include <time.h>

#include "ui.h"
#include "main.h"
#include "resource.h"
#include "bencode.h"
#include "btdict.h"
#include "lex.h"

static long CALLBACK window_proc(HWND window, UINT msg,
	WPARAM wparam, LPARAM lparam);
static long CALLBACK child_proc(HWND window, UINT msg,
	WPARAM wparam, LPARAM lparam);
static INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, 
	WPARAM wParam, LPARAM lParam);

static void ui_dispatch_event(MSG *msg);
static BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
static void OnDestroy(HWND hWnd);
static void OnPaint(HWND hWnd);
static void OnSize(HWND hwnd, UINT state, int cx, int cy);
static void OnFormSize(HWND hwnd, UINT state, int cx, int cy);
static void CenterWindow(HWND hwnd);
static BOOL CreateChild(HWND hWnd);
static BOOL CreateStatus(HWND hWnd);
static BOOL CreateDialogForm(HWND hWnd);
static BOOL OnInitForm(HWND hwnd, HWND hwndFocus, LPARAM lParam);
static BOOL ResizeToTab(HWND hwnd, UINT id, int cx);
static BOOL MoveToTab(HWND hwnd, UINT id, int cx);
static void OnNotify(HWND hWnd, int id, NMHDR *lParam);
static void ResizeFrameToDlg(HWND hWnd);
static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
static void OnExpand(void);
static void OnBrowse(void);
static void SetFrameTitle(LPCSTR title);
static BOOL LoadFile(LPCSTR filename);
static void UpdateForm(void);
static void UpdateControlText(UINT id, LPCSTR text);
static void UpdateControlDate(UINT id, struct tm* date);
static void UpdateInfo(void);
static void InsertFileItem(LPCSTR file, __int64 length);

static HWND main_hwnd, child_hwnd, status_hwnd, list_hwnd;
static HWND form_hwnd;
static bt_element torrent;

#define APPLICATION_CLASS_MAIN ("torrent:Main")
#define APPLICATION_CLASS_CHILD ("torrent:Child")
#define CX_TABOFFSET (5)
#define CY_TABOFFSET (5)
#define CX_FRAMEOFFSET (3)

int ui_init(int argc, char **argv)
{
	WNDCLASS window_class;
	memset(&window_class, 0, sizeof(WNDCLASS));

	InitCommonControls();

    /* Register the window class.  */
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = winmain_instance;
    window_class.hIcon = LoadIcon(winmain_instance,
		MAKEINTRESOURCE(IDI_TORRENT));
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = APPLICATION_CLASS_MAIN;
	window_class.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE + 1;
    RegisterClass(&window_class);

	main_hwnd = CreateWindow(APPLICATION_CLASS_MAIN,
		"torrent", 
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        winmain_instance,
        NULL);

	if (main_hwnd == NULL)
		return -1;

	CenterWindow(main_hwnd);
	ShowWindow(main_hwnd, winmain_cmd_show);
	UpdateWindow(main_hwnd);

	return 0;
}

long CALLBACK window_proc(HWND window, UINT msg, WPARAM wparam, 
	LPARAM lparam)
{
	switch (msg) {
	case WM_SIZE:
		HANDLE_WM_SIZE(window, wparam, lparam, OnSize);
		return 0;
	case WM_CREATE:
		return HANDLE_WM_CREATE(window, wparam, lparam, OnCreate);
	case WM_DESTROY:
		HANDLE_WM_DESTROY(window, wparam, lparam, OnDestroy);
		return 0;
	}

    return DefWindowProc(window, msg, wparam, lparam);
}

long CALLBACK child_proc(HWND window, UINT msg, WPARAM wparam, 
	LPARAM lparam)
{
	return DefWindowProc(window, msg, wparam, lparam);
}

int ui_error(const char *format, ...)
{
	va_list args;
	char buff[1000];	/* overflow?? */

    va_start(args, format);	
	vsprintf(buff, format, args);
	va_end(args);

	return MessageBox(main_hwnd, buff, "error", MB_OK | MB_ICONSTOP);
}

void ui_dispatch_event(MSG *msg)
{
	TranslateMessage(msg);
	DispatchMessage(msg);
}

int ui_dispatch_events(void)
{
    MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		ui_dispatch_event(&msg);	
	}

	return msg.wParam;
}

void OnPaint(HWND hWnd)
{
	RECT update_rect;
    if (GetUpdateRect(hWnd, &update_rect, FALSE)) {
		PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	} 
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	if (!CreateChild(hWnd))
		return FALSE;

	if (!CreateDialogForm(hWnd))
		return FALSE;

	if (!CreateStatus(hWnd))
		return FALSE;

	ResizeFrameToDlg(hWnd);

	return TRUE;
}

void CenterWindow(HWND hWnd)
{
	HWND hWndParent;
	RECT rc, rcWindow, rcParent;

	hWndParent = GetParent(hWnd);
	if (hWndParent == NULL) {
		hWndParent = GetDesktopWindow(); 
	}

    GetWindowRect(hWndParent, &rcParent); 
    GetWindowRect(hWnd, &rcWindow); 
    CopyRect(&rc, &rcParent); 

	OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top); 
    OffsetRect(&rc, -rc.left, -rc.top); 
    OffsetRect(&rc, -rcWindow.right, -rcWindow.bottom); 
 
    SetWindowPos(hWnd, 
		HWND_TOP, 
        rcParent.left + (rc.right / 2), 
        rcParent.top + (rc.bottom / 2), 
        0, 
		0,
        SWP_NOSIZE); 
}

void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rc;
	GetWindowRect(status_hwnd, &rc);

	/* forward message to status bar */
	SendMessage(status_hwnd, WM_SIZE, SIZE_RESTORED,
		MAKELPARAM(cx, cy));

	/* resize child window */
	if (IsWindowVisible(child_hwnd)) {
		cx /= 2;		
		MoveWindow(child_hwnd, 
			cx, 0,  
			cx, 
			cy - (rc.bottom - rc.top), 
			TRUE);
	}
	
	/* resize form dialog */
	MoveWindow(form_hwnd, 0, 0, 
		cx, 
		cy - (rc.bottom - rc.top), 
		TRUE);
}

void OnDestroy(HWND hWnd)
{
	free_element(torrent);
	PostQuitMessage(0);
}

BOOL CreateChild(HWND hWnd)
{
	WNDCLASS window_class;
	memset(&window_class, 0, sizeof(WNDCLASS));

    /* Register the child window class.  */
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = child_proc;
    window_class.hInstance = winmain_instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszClassName = APPLICATION_CLASS_CHILD;
    RegisterClass(&window_class);

	child_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		APPLICATION_CLASS_CHILD,
		NULL, 
		WS_CHILDWINDOW | WS_CLIPSIBLINGS,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        hWnd,
        NULL,
        winmain_instance,
        NULL);

	return child_hwnd != NULL;
}

BOOL CreateStatus(HWND hWnd)
{
	/* create status bar */
	status_hwnd = CreateStatusWindow(
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SBARS_SIZEGRIP,
		NULL, hWnd, IDC_STATUS);

	return status_hwnd != NULL;
}

BOOL CreateDialogForm(HWND hWnd)
{
	form_hwnd = CreateDialog(winmain_instance, 
		MAKEINTRESOURCE(IDD_FORMVIEW),
		hWnd,
		DlgProc);
	if (form_hwnd == NULL)
		return FALSE;

	ShowWindow(form_hwnd, winmain_cmd_show);
	return UpdateWindow(form_hwnd);
}

INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return HANDLE_WM_INITDIALOG(hwndDlg, wParam, lParam, OnInitForm);
	case WM_SIZE:
		HANDLE_WM_SIZE(hwndDlg, wParam, lParam, OnFormSize);
		return TRUE;
	case WM_NOTIFY:
		HANDLE_WM_NOTIFY(hwndDlg, wParam, lParam, OnNotify);
		return TRUE;
	case WM_COMMAND:
		HANDLE_WM_COMMAND(hwndDlg, wParam, lParam, OnCommand);
		return TRUE;
	}

	return FALSE;
}

void OnFormSize(HWND hwnd, UINT state, int cx, int cy)
{
	HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB);
	int width;
	
	/* move tab window */
	MoveWindow(tab_hwnd, 
		CX_TABOFFSET, 
		CY_TABOFFSET, 
		cx - (CX_TABOFFSET*2), 
		cy - (CY_TABOFFSET*2), 
		TRUE);

	/* resize controls */
	width = cx - (CX_TABOFFSET*2) - CX_FRAMEOFFSET;
	ResizeToTab(hwnd, IDC_FRAME, width);	
	ResizeToTab(hwnd, IDC_FILELIST, width);	
	
	MoveToTab(hwnd, IDC_BROWSE, width);
	MoveToTab(hwnd, IDC_EXPAND, width);

	width = cx - (CX_TABOFFSET*3) - (CX_FRAMEOFFSET*2);
	ResizeToTab(hwnd, IDC_ANNOUNCE, width);	
	ResizeToTab(hwnd, IDC_CREATEDBY, width);	
	ResizeToTab(hwnd, IDC_CREATIONDATE, width);	
	ResizeToTab(hwnd, IDC_COMMENT, width);	
}

BOOL OnInitForm(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCITEM item; 
	LV_COLUMN lvc;

	HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB);
	if (tab_hwnd == NULL)
		return FALSE;
	
	item.mask = TCIF_TEXT;
	item.pszText = "Torrent Info";
	if (SendMessage(tab_hwnd, TCM_INSERTITEM, 0, (LPARAM)&item) == -1)
		return FALSE;

	list_hwnd = GetDlgItem(hwnd, IDC_FILELIST);
	if (list_hwnd == NULL)
		return FALSE;

	ListView_SetTextColor(list_hwnd, RGB(64, 0, 0));
	ListView_SetExtendedListViewStyleEx(list_hwnd, 
		0, 
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
	);
	
	memset(&lvc, 0, sizeof(LV_COLUMN));
	lvc.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.iSubItem = 0;
	lvc.pszText	= "Name";
	lvc.cx = 200;
	ListView_InsertColumn(list_hwnd, 0, &lvc);

	lvc.iSubItem = 1;
	lvc.pszText	= "Size";
	lvc.cx = 50;
	ListView_InsertColumn(list_hwnd, 1, &lvc);

	return TRUE;
}

BOOL ResizeToTab(HWND hWnd, UINT id, int cx)
{
	RECT rc;
	HWND hwndControl = GetDlgItem(hWnd, id);
	if (hwndControl == NULL)
		return FALSE;

	GetWindowRect(hwndControl, &rc);
	MapWindowPoints(HWND_DESKTOP, hWnd, (LPPOINT)&rc, 2);
	
	SetWindowPos(hwndControl, NULL, 0, 0, 
		cx - rc.left,
		rc.bottom - rc.top,
		SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;
}

BOOL MoveToTab(HWND hWnd, UINT id, int cx)
{
	RECT rc;
	HWND hwndControl = GetDlgItem(hWnd, id);
	if (hwndControl == NULL)
		return FALSE;

	GetWindowRect(hwndControl, &rc);
	MapWindowPoints(HWND_DESKTOP, hWnd, (LPPOINT)&rc, 2);

	cx -= rc.right - rc.left;
	
	SetWindowPos(hwndControl, NULL, 
		cx, 
		rc.top, 
		0,
		0,
		SWP_NOSIZE | SWP_NOZORDER);

	return TRUE;
}

void OnNotify(HWND hWnd, int id, NMHDR *hdr)
{
}

void ResizeFrameToDlg(HWND hWnd)
{
	RECT rc, rcStatus;
	int cx, cy;

	GetWindowRect(form_hwnd, &rc);
	GetWindowRect(status_hwnd, &rcStatus);
	rc.bottom += (rcStatus.bottom - rcStatus.top);

	AdjustWindowRectEx(&rc, 
		GetWindowLong(hWnd, GWL_STYLE),
		FALSE,
		GetWindowLong(hWnd, GWL_EXSTYLE));
	
	cx = rc.right - rc.left;
	cy = rc.bottom - rc.top;
	
	SetWindowPos(hWnd, NULL, 0, 0, cx, cy,
		SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER);	
	SendMessage(hWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(cx, cy));
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id) {
	case IDC_EXPAND:
		OnExpand();
		break;
	case IDC_BROWSE:
		OnBrowse();
		break;
	case IDC_EXIT:
		SendMessage(main_hwnd, WM_CLOSE, 0, 0);
		break;
	}
}

void OnBrowse(void)
{
	OPENFILENAME ofn;
	char filename[_MAX_PATH], title[_MAX_FNAME + _MAX_EXT];

	memset(&ofn, 0, sizeof(OPENFILENAME));
	filename[0] = title[0] = '\0';

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = main_hwnd;
	ofn.hInstance = winmain_instance;
	ofn.lpstrFilter	= "Torrent Files (*.torrent)\0*.torrent\0";
	ofn.nMaxFile = _MAX_PATH;
	ofn.nMaxFileTitle = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrDefExt = "torrent";
	ofn.lpstrFileTitle = title;
	ofn.lpstrFile = filename;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		if (LoadFile(ofn.lpstrFile)) {
			SetFrameTitle(title);
			UpdateForm();
		}
	}
}

void OnExpand(void)
{
	RECT rc;
	int cx, cy;	
	int nCmdShow = IsWindowVisible(child_hwnd) ?
		SW_HIDE : SW_SHOW;

	SetDlgItemText(form_hwnd, IDC_EXPAND, 
		nCmdShow == SW_HIDE ? ">>>" : "<<<");
	
	ShowWindow(child_hwnd, nCmdShow);
	GetWindowRect(main_hwnd, &rc);		
	cx = nCmdShow == SW_HIDE ? 
		((rc.right - rc.left) / 2) :
		((rc.right - rc.left) * 2);
	cy = (rc.bottom - rc.top);
	SetWindowPos(main_hwnd, NULL, 0, 0, cx, cy,
		SWP_NOMOVE | SWP_FRAMECHANGED | SWP_NOZORDER);	
}

void SetFrameTitle(LPCSTR title)
{
	char buf[_MAX_PATH];
	sprintf(buf, "torrent: %s", title);
	SetWindowText(main_hwnd, buf);
}

BOOL LoadFile(LPCSTR filename)
{
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		ui_error("unable to open \"%s\".\n", filename);
		return FALSE;
	}

	free_element(torrent);

	torrent = getelement(fp);
	if (torrent.type != ET_DICT) 
		ui_error("bad torrent file \"%s\".", filename);

	fclose(fp);

	return torrent.type == ET_DICT;
}

void UpdateForm(void)
{
	UpdateControlText(IDC_ANNOUNCE, 
		bt_dict_cstring(torrent.dval, "announce"));
	UpdateControlText(IDC_CREATEDBY, 
		bt_dict_cstring(torrent.dval, "created by"));
	UpdateControlDate(IDC_CREATIONDATE, 
		bt_dict_date(torrent.dval, "creation date"));	
	UpdateControlText(IDC_COMMENT, 
		bt_dict_cstring(torrent.dval, "comment"));

	UpdateInfo();
}

void UpdateControlText(UINT id, LPCSTR text)
{
	if (text != NULL) {
		SetDlgItemText(form_hwnd, id, text);
	} else {
		SetDlgItemText(form_hwnd, id, "");
	}
}

void UpdateControlDate(UINT id, struct tm *date)
{
	if (date != NULL) {
		char buf[128];
		strftime(buf, sizeof(buf), "%m/%d/%Y %I:%M:%S %p", date);
		SetDlgItemText(form_hwnd, id, buf);
	} else {
		SetDlgItemText(form_hwnd, id, "");
	}	
}

void UpdateInfo(void)
{
	bt_dict *info;

	ListView_DeleteAllItems(list_hwnd);

	info = bt_dict_dict(torrent.dval, "info");
	if (info != NULL) {
		InsertFileItem(
			bt_dict_cstring(info, "name"),
			bt_dict_int(info, "length")
		);
	}
}

void InsertFileItem(LPCSTR file, __int64 length)
{
	if (file != NULL) {
		LVITEM item;
		memset(&item, 0, sizeof(LVITEM));

		item.mask = LVIF_TEXT;
		item.pszText = (LPSTR)file;

		ListView_InsertItem(list_hwnd, &item);
	}
}