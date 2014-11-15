//////////////////////////////////
//	Module:	MultiThreadTest.c	//
//	Author:	Thomas A. Rieck		//
//	Date:	07/05/97			//
//////////////////////////////////

#include <stdio.h>
#include "MultiThreadTest.h"
#include "resource.h"

HINSTANCE	hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    if (!InitApplication(hInstance))
        return(0);

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

    wc.style			= 0;
    wc.lpfnWndProc		= (WNDPROC)MainWndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hIcon			= LoadIcon (NULL, IDI_APPLICATION);
    wc.hInstance		= hInstance;
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MAINMENU);
    wc.lpszClassName	= "MultiThreadTest";

    return (RegisterClass(&wc));
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND	hWnd;

    hInst = hInstance;

    hWnd = CreateWindowEx(
               WS_EX_WINDOWEDGE,
               "MultiThreadTest",
               "Multiple Threads",
               WS_OVERLAPPEDWINDOW |		// Window style.
               WS_CLIPCHILDREN,
               CW_USEDEFAULT,              // Default horizontal position.
               CW_USEDEFAULT,              // Default vertical position.
               400,			            // width.
               400,		                // height.
               NULL,                       // Overlapped windows have no parent.
               NULL,                       // Use the window class menu.
               hInstance,                  // This instance owns this window.
               NULL						// Pointer not needed.
           );

    if (!hWnd)
        return (FALSE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return (TRUE);
}

LONG APIENTRY MainWndProc(HWND hWnd, UINT msg,
                          WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        WNDCLASSEX wndclass;
        INT i, xPos, yPos, x, y;
        static PARAM param[MAX_CHILDREN];
        static INT cxClient, cyClient;

    case WM_CREATE:
        // set param structures
        param[0].iShape	= SH_ELLIPSE;
        strcpy(param[0].szClassName, "EllipseClass");
        param[0].wndProc = EllipseProc;

        param[1].iShape	= SH_RECTANGLE;
        strcpy(param[1].szClassName, "RectangleClass");
        param[1].wndProc = RectangleProc;

        param[2].iShape = SH_ROUNDRECT;
        strcpy(param[2].szClassName, "RoundRectClass");
        param[2].wndProc = RoundRectProc;

        for (i = 0; i < MAX_CHILDREN; i++) {

            // create the child windows
            wndclass.cbSize        = sizeof (wndclass);
            wndclass.style         = CS_HREDRAW | CS_VREDRAW;
            wndclass.cbClsExtra    = 0;
            wndclass.cbWndExtra    = 0;
            wndclass.hInstance     = hInst;
            wndclass.hIcon         = NULL;
            wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
            wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
            wndclass.lpszMenuName  = NULL;
            wndclass.hIconSm       = NULL;

            wndclass.lpfnWndProc   = param[i].wndProc;
            wndclass.lpszClassName = param[i].szClassName;

            RegisterClassEx (&wndclass);

            param[i].hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                                           param[i].szClassName, NULL,
                                           WS_CHILDWINDOW | WS_VISIBLE |
                                           WS_CLIPSIBLINGS,
                                           0, 0, 0, 0, hWnd, (HMENU)i, hInst, NULL);

            param[i].hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

            // set parameter to windows
            SendMessage(param[i].hWnd, WM_SETPARAM, 0, (LPARAM)&param[i]);
        }
        break;
    case WM_SIZE:
        cxClient = LOWORD (lParam);
        cyClient = HIWORD (lParam);

        for (i=0; i < MAX_CHILDREN; i++) {
            switch (i) {
            case 0:
                xPos = 0;
                yPos = 0;
                x = cxClient;
                y = cyClient / MAX_CHILDREN;
                break;
            case 1:
                xPos = 0;
                yPos = cyClient / MAX_CHILDREN;
                x = cxClient;
                y = cyClient / MAX_CHILDREN;
                break;
            case 2:
                xPos = 0;
                yPos = cyClient - (cyClient / MAX_CHILDREN) ;
                x = cxClient;
                y = cyClient / MAX_CHILDREN;
                break;
            }
            MoveWindow(param[i].hWnd, xPos, yPos, x, y, TRUE);
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDM_PAUSETHREAD1:
            ResetEvent(param[0].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_STARTTHREAD1, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_STARTTHREAD1:
            SetEvent(param[0].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_PAUSETHREAD1, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_PAUSETHREAD2:
            ResetEvent(param[1].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_STARTTHREAD2, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_STARTTHREAD2:
            SetEvent(param[1].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_PAUSETHREAD2, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_PAUSETHREAD3:
            ResetEvent(param[2].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_STARTTHREAD3, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_STARTTHREAD3:
            SetEvent(param[2].hEvent);
            CheckMenuItem(GetMenu(hWnd), LOWORD(wParam), MF_BYCOMMAND | MF_CHECKED);
            CheckMenuItem(GetMenu(hWnd), IDM_PAUSETHREAD3, MF_BYCOMMAND | MF_UNCHECKED);
            break;
        case IDM_EXIT:
            SendMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        };
        break;
    case WM_DESTROY:
        // destroy child windows
        for (i=0; i < MAX_CHILDREN; i++)
            if (param[i].hWnd) DestroyWindow(param[i].hWnd);

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return (0);
}

// ThreadProc
VOID ThreadProc(LPVOID pArgs)
{
    PPARAM	pParam;

    pParam = (PPARAM)pArgs;

    while (TRUE) {
        WaitForSingleObject(pParam->hEvent, INFINITE);
        DrawShape(pParam);
    }

    _endthread();
}


// DrawShape
VOID DrawShape(PPARAM pParam)
{
    DWORD	bColor;
    DWORD	pColor;
    HDC		hDC;
    HBRUSH	hBrush, hBrushOld;
    HPEN	hPen, hPenOld;
    RECT	rc, rcWnd;
    static	BYTE i, j, k;

    hDC = GetDC(pParam->hWnd);

    switch (pParam->iShape) {
    case SH_ELLIPSE:
        bColor = RGB(i, 0, 0);
        pColor = RGB(255 - i, 0, 0);
        i++;
        if (i > 255) i = 0;
        break;
    case SH_RECTANGLE:
        bColor = RGB(0, j, 0);
        pColor = RGB(0, 255 - j, 0);
        j++;
        if (j > 255) j = 0;
        break;
    case SH_ROUNDRECT:
        bColor = RGB(0, 0, k);
        pColor = RGB(0, 0, 255 - k);
        k++;
        if (k > 255) k = 0;
        break;
    }
    hBrush = CreateSolidBrush(bColor);
    hBrushOld = SelectObject(hDC, hBrush);

    hPen = CreatePen(PS_SOLID, 1, pColor);
    hPenOld = SelectObject(hDC, hPen);

    GetClientRect(pParam->hWnd, &rcWnd);

    if (rcWnd.right != 0 && rcWnd.bottom !=0) {
        rc.left		= rand() % rcWnd.right;
        rc.top		= rand() % rcWnd.bottom;
        rc.right	= rand() % rcWnd.right;
        rc.bottom	= rand() % rcWnd.bottom;

        switch (pParam->iShape) {
        case SH_ELLIPSE:
            Ellipse(hDC, min(rc.left, rc.right),
                    min(rc.top, rc.bottom),
                    max(rc.left, rc.right),
                    max(rc.top, rc.bottom));
            break;
        case SH_RECTANGLE:
            Rectangle(hDC, min(rc.left, rc.right),
                      min(rc.top, rc.bottom),
                      max(rc.left, rc.right),
                      max(rc.top, rc.bottom));
            break;
        case SH_ROUNDRECT:
            RoundRect(hDC, min(rc.left, rc.right),
                      min(rc.top, rc.bottom),
                      max(rc.left, rc.right),
                      max(rc.top, rc.bottom), 25, 25);
            break;
        }

    }
    // clean up
    SelectObject(hDC, hBrushOld);
    DeleteObject(hBrush);

    SelectObject(hDC, hPenOld);
    DeleteObject(hPen);

    ReleaseDC(pParam->hWnd, hDC);
}

// EllipseProc
LONG APIENTRY EllipseProc(HWND hWnd, UINT msg,
                          WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_SETPARAM:
        // create a new thread
        _beginthread(ThreadProc, 0,
                     (LPVOID)(PPARAM)lParam);
        break;
    }
    return DefWindowProc (hWnd, msg, wParam, lParam);
}

// RectangleProc
LONG APIENTRY RectangleProc(HWND hWnd, UINT msg,
                            WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_SETPARAM:
        // create a new thread
        _beginthread(ThreadProc, 0,
                     (LPVOID)(PPARAM)lParam);
        break;
    }
    return DefWindowProc (hWnd, msg, wParam, lParam);
}

// RoundRectProc
LONG APIENTRY RoundRectProc(HWND hWnd, UINT msg,
                            WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_SETPARAM:
        // create a new thread
        _beginthread(ThreadProc, 0,
                     (LPVOID)(PPARAM)lParam);
        break;
    }
    return DefWindowProc (hWnd, msg, wParam, lParam);
}