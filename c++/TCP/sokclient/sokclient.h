///////////////////////////////
//	Module:	SOKCLIENT.H		 //	
//	Author:	Thomas A. Rieck	 //
//	Date:	05/25/97		 //
///////////////////////////////

#ifndef NO_FLAGS_SET
#define	NO_FLAGS_SET	0
       
#define	SERVICE_NAME	"merlin"
#define MAXTOOLBUTTONS  6

#define WSA_ASYNC		(WM_USER + 0)
#define WM_WSGETHOST	(WM_USER + 1)

#define COLOR_YELLOW	RGB(255,255,0)

#include <winsock2.h>
#include <commctrl.h>
#include <stdio.h>

BOOL			InitApplication(HINSTANCE hInstance);
BOOL			InitInstance(HINSTANCE hInstance, int nCmdShow);
LONG APIENTRY	MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD			FillAddress(HWND hWnd, LPCSTR szHostName, SOCKADDR_IN* pSin);
BOOL WINAPI		MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
WORD			ResolveServicePort(void);
BOOL WINAPI		AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
HWND			CreateToolBar(HWND hWndParent);
HWND			CreateStatusBar(HWND hWndParent);
VOID			SetConnectState(HWND hWndStatus, BOOL bConnected);
VOID			SetConnectMenus(HWND hWnd, HWND hWndToolBar, BOOL bConnect);
BOOL WINAPI		DiskInfoProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
#endif	// NO_FLAGS_SET