/////////////////////////////////////////////////////////////////////////////
//
//	WINAPP.C : windows application
//

#include "winapp.h"

WinApp *App = NULL;

#define WF_CONTINUEMODAL 0x8080

// Helper functions
static BOOL pumpMessage();
static BOOL init(WinApp *pApp, HINSTANCE hInstance, LPTSTR command,
                 int show);

/////////////////////////////////////////////////////////////////////////////
BOOL init(WinApp *pApp, HINSTANCE hInstance, LPTSTR command, int show)
{
    pApp->hInstance = hInstance;
    pApp->command = command;
    pApp->show = show;
    App = pApp;

    return initApp();
}

/////////////////////////////////////////////////////////////////////////////
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR command,
                     INT show)
{
    WinApp theApp;

    if (!init(&theApp, hInstance,  command, show))
        return 1;

    runApp();

    return exitApp();
}

/////////////////////////////////////////////////////////////////////////////
BOOL centerWindow(HWND hWnd, HWND hWndParent)
{
    RECT rc, rcParent;
    POINT pt;

    GetWindowRect(hWnd, &rc);
    GetWindowRect(hWndParent, &rcParent);

    pt.x = rcParent.left + (((rcParent.right - rcParent.left) -
                             (rc.right - rc.left)) / 2);
    pt.y = rcParent.top + (((rcParent.bottom - rcParent.top) -
                            (rc.bottom - rc.top)) / 2);

    return SetWindowPos(hWnd, NULL, pt.x, pt.y, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
BOOL pumpMessages()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
        if (!pumpMessage()) {
            PostQuitMessage(0);
            FALSE;
        }
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL pumpMessage()
{
    MSG msg;

    if (!GetMessage(&msg, NULL, 0, 0))
        return FALSE;

    // process this message
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void enterModalLoop(HWND hWnd)
{
    EnableWindow(GetParent(hWnd), FALSE);

    SetWindowLong(hWnd,
                  GWL_USERDATA,
                  GetWindowLong(hWnd, GWL_USERDATA) | WF_CONTINUEMODAL);

    for (;;) {
        LONG flags = GetWindowLong(hWnd, GWL_USERDATA);
        if ((flags & WF_CONTINUEMODAL) == 0)
            break;

        if (!pumpMessages())
            break;
    }

    DestroyWindow(hWnd);
}

/////////////////////////////////////////////////////////////////////////////
void endModalLoop(HWND hWnd)
{
    LONG flags = GetWindowLong(hWnd, GWL_USERDATA);
    if (flags & WF_CONTINUEMODAL) {
        flags &= ~WF_CONTINUEMODAL;
        SetWindowLong(hWnd, GWL_USERDATA, flags);
    }

    EnableWindow(GetParent(hWnd), TRUE);
}

