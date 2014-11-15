/////////////////////////////////////////////////////////////////////////////
//
//	MAIN.C : main entry point
//

#include "common.h"
#include "winapp.h"
#include "resource.h"

extern LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                   LPARAM lParam);

static LPCTSTR className = _T("FishingFrameWnd");

/////////////////////////////////////////////////////////////////////////////
BOOL initApp()
{
    WNDCLASS wc;
    TCHAR title[_MAX_FNAME];

    // Register the window class for the main window.
    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)windowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = App->hInstance;
    wc.hIcon = LoadIcon((HINSTANCE) NULL,
                        IDI_APPLICATION);
    wc.hCursor = LoadCursor((HINSTANCE) NULL,
                            IDC_ARROW);
    wc.hbrBackground = GetStockObject(NULL_BRUSH);
    wc.lpszMenuName =  MAKEINTRESOURCE(IDR_MAINMENU);
    wc.lpszClassName = className;

    if (!RegisterClass(&wc))
        return FALSE;

    if (!LoadString(App->hInstance, IDS_APPTITLE, title, _MAX_FNAME))
        return FALSE;

    // Create the main window
    App->hWndMain = CreateWindowEx(0, className,
                                   title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                   CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, App->hInstance, NULL);

    if (App->hWndMain == NULL)
        return FALSE;

    // Show the window and paint its contents
    ShowWindow(App->hWndMain, App->show);
    UpdateWindow(App->hWndMain);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
int runApp(void)
{
    MSG msg;

    // Start the message loop
    while (GetMessage(&msg, (HWND)NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Return the exit code to the system
    return msg.wParam;
}

/////////////////////////////////////////////////////////////////////////////
int exitApp()
{
    UnregisterClass(className, App->hInstance);

    return 0;
}
