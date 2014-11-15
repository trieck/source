/////////////////////////////////////////////////////////////////////////////
//
//	WINPROC.C : main window procedure
//

#include "common.h"
#include "winapp.h"
#include "dbdlg.h"
#include "resource.h"

static void onClose(HWND hWnd);
static void onDestroy(HWND hWnd);
static void onOptions(void);
static void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
static void onPanelCommand(HWND hWnd, int id, HWND hwndCtl,
                           UINT codeNotify);
static void onSize(HWND hwnd, UINT state, int cx, int cy);
static BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
static BOOL onCreateEdit(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
static void onDestroyEdit(HWND hwnd);
static HBRUSH onColorEdit(HWND hwnd, HDC hdc, HWND hwndChild, int type);
static LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam,
                                 LPARAM lParam);
static BOOL CALLBACK panelProc(HWND hWnd, UINT msg, WPARAM wParam,
                               LPARAM lParam);
static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
static BOOL onInitPanel(HWND hwnd, HWND hwndFocus, LPARAM lParam);
static void onSave(void);
static void onPrevious(void);
static void onNext(void);
static void onEditChange(void);

static HWND hwndEdit;			// edit window
static HWND hwndPanel;			// panel window
static WNDPROC oldEditProc;		// old edit wndproc; subclassed
static HFONT hFont;				// edit font
static HBRUSH hBrush;			// edit brush

#define COLOR_EDIT PALETTERGB(0xFF, 0xFF, 0xA8)

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam,
                            LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
        return HANDLE_WM_CREATE(hWnd, wParam, lParam, onCreate);
    case WM_COMMAND:
        return HANDLE_WM_COMMAND(hWnd, wParam, lParam, onCommand);
    case WM_SIZE:
        return HANDLE_WM_SIZE(hWnd, wParam, lParam, onSize);
    case WM_CTLCOLOREDIT:
        return HANDLE_WM_CTLCOLOREDIT(hWnd, wParam, lParam, onColorEdit);
    case WM_CLOSE:
        return HANDLE_WM_CLOSE(hWnd, wParam, lParam, onClose);
    case WM_DESTROY:
        return HANDLE_WM_DESTROY(hWnd, wParam, lParam, onDestroy);
    default:
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
void onClose(HWND hWnd)
{
    DestroyWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////
void onDestroy(HWND hWnd)
{
    if (hwndEdit != NULL) {
        DestroyWindow(hwndEdit);
        hwndEdit = NULL;
    }
    if (hwndPanel != NULL) {
        DestroyWindow(hwndPanel);
        hwndPanel = NULL;
    }

    App->hWndMain = NULL;

    PostQuitMessage(0);
}

/////////////////////////////////////////////////////////////////////////////
void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case IDM_EXIT:
        onClose(hWnd);
        break;
    case IDM_OPTIONS:
        onOptions();
    default:
        // handle edit notifications
        if (hwndCtl == hwndEdit) {
            switch (codeNotify) {
            case EN_CHANGE:
                onEditChange();
                break;
            default:
                break;
            }
        }
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
void onOptions()
{
    DbDialog *pdlg = createDbDialog();
    if (pdlg == NULL)
        return;

    DbDialogDisplay(pdlg);

    deleteDbDialog(pdlg);
}

/////////////////////////////////////////////////////////////////////////////
void onSize(HWND hwnd, UINT state, int cx, int cy)
{
    if (hwndEdit != NULL) {
        MoveWindow(hwndEdit, 0, 0, cx, cy / 2, TRUE);
    }
    if (hwndPanel != NULL) {
        MoveWindow(hwndPanel, 0, cy / 2, cx, cy, TRUE);
    }
}

/////////////////////////////////////////////////////////////////////////////
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    // set window hook for edit WM_CREATE message
//	HHOOK hhook = SetWindowsHookEx(
//		WH_CBT, hookProc,  App->hInstance, GetCurrentThreadId());

//	if (hhook == NULL)
//		return FALSE;	// could not set window hook

    // create the edit window
    hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
                              _T("Edit"),
                              _T(""),
                              WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_WANTRETURN
                              |  ES_AUTOVSCROLL | WS_VSCROLL | ES_NOHIDESEL,
                              0, 0, 0, 0, hwnd, NULL, App->hInstance, 0/*hhook*/);
    if (hwndEdit == NULL) {
//		UnhookWindowsHookEx(hhook);
        return FALSE;	// could not create edit window
    }

    // unhook window hook
//	UnhookWindowsHookEx(hhook);

    // create the panel window
    hwndPanel = CreateDialog(App->hInstance,
                             MAKEINTRESOURCE(IDD_PANEL), hwnd, panelProc);
    if (hwndPanel == NULL)
        return FALSE;	// could not create panel window

    memset(&dbinfo, 0, sizeof(DbInfo));

    SetFocus(hwndEdit);

    return centerWindow(hwnd, GetDesktopWindow());
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK EditProc(HWND hWnd, UINT msg, WPARAM wParam,
                          LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
        return HANDLE_WM_CREATE(hWnd, wParam, lParam, onCreateEdit);
    case WM_DESTROY:
        HANDLE_WM_DESTROY(hWnd, wParam, lParam, onDestroyEdit);
        break;
    default:
        break;
    }

    // we are subclassed, must do CallWindowProc with previous proc
    return CallWindowProc(oldEditProc, hWnd, msg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
BOOL onCreateEdit(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    HDC hDC;
    int height;

    // necessary for proper creation of edit window
    CallWindowProc(oldEditProc, hWnd, WM_CREATE, 0, (LPARAM)lpCreateStruct);

    // create edit font
    hDC = GetDC(hWnd);
    height = -MulDiv(12, GetDeviceCaps(hDC, LOGPIXELSY), 72);

    hFont = CreateFont(
                height,							// height
                0,								// average character width
                0,								// angle of escapement
                0,								// base-line orientation angle
                FW_MEDIUM,						// font weight
                0,								// italic attribute option
                0,								// underline attribute option
                0,								// strikeout attribute option
                DEFAULT_CHARSET,				// character set identifier
                OUT_DEFAULT_PRECIS,				// output precision
                CLIP_DEFAULT_PRECIS,			// clipping precision
                DEFAULT_QUALITY,				// output quality
                DEFAULT_PITCH | FF_DONTCARE,	// pitch and family
                _T("Courier New")			// typeface name
            );

    ReleaseDC(hWnd, hDC);

    if (hFont == NULL)
        return FALSE;	// font creation failed

    SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

    // create edit brush
    hBrush = CreateSolidBrush(COLOR_EDIT);
    if (hBrush == NULL)
        return FALSE;	// brush creation failed

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code == HCBT_CREATEWND) {
        CBT_CREATEWND *pcwnd = (CBT_CREATEWND *)lParam;
        HWND hWnd = (HWND)wParam;

        // subclass edit window
        oldEditProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)EditProc);

        return CallNextHookEx((HHOOK)pcwnd->lpcs->lpCreateParams,
                              code, wParam, lParam);
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
void onDestroyEdit(HWND hwnd)
{
    // destroy edit font
    if (hFont != NULL) {
        DeleteObject(hFont);
        hFont = NULL;
    }

    // destroy edit brush
    if (hBrush != NULL) {
        DeleteObject(hBrush);
        hBrush = NULL;
    }
}

/////////////////////////////////////////////////////////////////////////////
HBRUSH onColorEdit(HWND hwnd, HDC hdc, HWND hwndChild, int type)
{
    if (hwndChild == hwndEdit) {
        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, hBrush);
        return hBrush;
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK panelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG:
        return HANDLE_WM_INITDIALOG(hWnd, wParam, lParam, onInitPanel);
    case WM_COMMAND:
        return HANDLE_WM_COMMAND(hWnd, wParam, lParam, onPanelCommand);
    default:
        break;
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL onInitPanel(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void onPanelCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case IDC_SAVE:
        onSave();
        break;
    case IDC_PREVIOUS:
        onPrevious();
        break;
    case IDC_NEXT:
        onNext();
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
void onSave(void)
{
    HWND hWnd = GetDlgItem(hwndPanel, IDC_SAVE);
    EnableWindow(hWnd, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
void onPrevious(void)
{
}

/////////////////////////////////////////////////////////////////////////////
void onNext(void)
{
}

/////////////////////////////////////////////////////////////////////////////
void onEditChange(void)
{
    HWND hWnd = GetDlgItem(hwndPanel, IDC_SAVE);
    EnableWindow(hWnd, TRUE);
}

