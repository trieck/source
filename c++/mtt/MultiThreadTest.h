//////////////////////////////////
//	Module:	MultiThreadTest.h	//
//	Author:	Thomas A. Rieck		//
//	Date:	07/05/97			//
//////////////////////////////////

#ifndef __MULTITHREADTEST_H__
#define	__MULTITHREADTEST_H__

#include <windows.h>
#include <process.h>

#define	MAX_CHILDREN 3

// shape constants
#define SH_ELLIPSE 		1
#define SH_RECTANGLE	2
#define SH_ROUNDRECT	3

#define WM_SETPARAM (WM_USER + 1)

typedef struct {
	INT			iShape;
	CHAR		szClassName[20];
	WNDPROC		wndProc;
	HWND		hWnd;
	HANDLE		hEvent;
} PARAM, *PPARAM;

BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LONG APIENTRY MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LONG APIENTRY EllipseProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LONG APIENTRY RectangleProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LONG APIENTRY RoundRectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID ThreadProc(LPVOID pArgs);
VOID DrawShape(PPARAM pParam);
#endif	// __MULTITHREADTEST_H__