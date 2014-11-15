/*--------------------------------------------
	Module	:	Generic.CPP
	Date	: 	07/15/1997
	Purpose	:	Generic Window App Class
				Implementation
---------------------------------------------*/

#include "capp.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, INT nCmdShow)
{
    MSG		msg;
    LPCSTR	lpszClass = "GenericWnd";
    LPCSTR	lpszTitle = "Generic Window";

    CApp* pApp = new CApp(hInstance, nCmdShow);
    if (!pApp) return (0);

    // Initialize application
    if (!pApp->Init(lpszClass))
        return (0);

    // Don't allow multiple instances
    if (::FindWindow(lpszClass, NULL))
        return 0;

    // Create window
    if (!pApp->Create(lpszTitle))
        return (0);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (pApp) delete pApp;

    return (msg.wParam);
}

CApp :: CApp(HINSTANCE hInstance, INT nCmdShow)
{
    m_hInst 			= hInstance;
    m_nCmdShow			= nCmdShow;
    m_hWnd				= NULL;
    m_hWndChild			= NULL;
    m_hWndStatus		= NULL;
    m_szClassName[0] 	= '\0';
}

BOOL CApp :: Init(LPCSTR lpszClassName)
{
    if (!lpszClassName)
        return (FALSE);

    strcpy (m_szClassName, lpszClassName);

    // Create Frame class
    m_wndClass.style			= CS_HREDRAW | CS_VREDRAW;
    m_wndClass.lpfnWndProc		= (WNDPROC)MainWndProc;
    m_wndClass.cbClsExtra		= 0;
    m_wndClass.cbWndExtra		= 0;
    m_wndClass.hIcon			= 0;
    m_wndClass.hInstance		= m_hInst;
    m_wndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
    m_wndClass.hbrBackground	= NULL;
    m_wndClass.lpszMenuName		= NULL;
    m_wndClass.lpszClassName	= m_szClassName;

    if (!RegisterClass(&m_wndClass))
        return FALSE;

    // Create Child Class
    m_wndChildClass.style			= CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT;
    m_wndChildClass.lpfnWndProc		= (WNDPROC)ChildProc;
    m_wndChildClass.cbClsExtra		= 0;
    m_wndChildClass.cbWndExtra		= 0;
    m_wndChildClass.hIcon			= 0;
    m_wndChildClass.hInstance		= m_hInst;
    m_wndChildClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
    m_wndChildClass.hbrBackground	= GetSysColorBrush(COLOR_WINDOW);
    m_wndChildClass.lpszMenuName	= NULL;
    m_wndChildClass.lpszClassName	= "ChildClass";

    if (!RegisterClass(&m_wndChildClass))
        return FALSE;

    return TRUE;
}

BOOL CApp :: Create(LPCSTR lpszCaption)
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
                 400,					// Width.
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

CApp::~CApp()
{
    if (IsWindow(m_hWnd))
        DestroyWindow(m_hWnd);
}

VOID CApp :: Message (LPCTSTR szMessage)
{
    MessageBox(m_hWnd, szMessage, "", MB_ICONEXCLAMATION);
}

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
{
    static PAPP		pApp;
    LPCREATESTRUCT	lpcs;
    RECT			rc;
    INT				cx, cy, yStatus;

    switch (message) {
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

        assert(IsWindow(pApp->m_hWndStatus));

        GetWindowRect(pApp->m_hWndStatus, &rc);
        yStatus = (rc.bottom - rc.top);

        // Create the child window
        pApp->m_hWndChild = CreateWindowEx(
                                WS_EX_CLIENTEDGE,
                                pApp->m_wndChildClass.lpszClassName,
                                NULL,
                                WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,    // Window style.
                                0,	                  						// Default horizontal position.
                                0,                  						// Default vertical position.
                                lpcs->cx,                  					// Width.
                                lpcs->cy - yStatus,                			// Height.
                                hWnd,			                           	// Window parent
                                NULL,                           			// Use the window class menu.
                                pApp->m_hInst,								// This instance owns this window.
                                pApp);

        assert(IsWindow(pApp->m_hWndChild));

        MoveWindow(hWnd, cx, cy, lpcs->cx, lpcs->cy, TRUE);

        break;
    case WM_SIZE:
        RECT 	rcStatus;
        INT 	xClient, yClient, yStatus;

        GetWindowRect(pApp->m_hWndStatus, &rcStatus);

        xClient = LOWORD(lParam);
        yClient = HIWORD(lParam);

        yStatus = (rcStatus.bottom - rcStatus.top);

        SendMessage(pApp->m_hWndStatus, WM_SIZE, wParam, lParam);
        MoveWindow(pApp->m_hWndChild, 0, 0, xClient, yClient - yStatus, TRUE);

        break;
    case WM_SYSCOLORCHANGE:
    case WM_SETTINGCHANGE:
        SendMessage(pApp->m_hWndStatus, WM_SETTINGCHANGE, wParam, lParam);
        break;
    case WM_DESTROY:
        DestroyWindow(pApp->m_hWndChild);
        DestroyWindow(pApp->m_hWndStatus);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return (0);
}

LRESULT APIENTRY ChildProc(HWND hWnd, UINT message,
                           WPARAM wParam, LPARAM lParam)
{
    static		PAPP pApp;

    switch (message) {
    case WM_CREATE:
        pApp = (PAPP)((LPCREATESTRUCT)lParam)->lpCreateParams;
        assert(pApp);
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return (0);
}

