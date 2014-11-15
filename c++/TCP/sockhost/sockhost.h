///////////////////////////////
//	Module:	SOCKHOST.H		 //
//	Author:	Thomas A. Rieck	 //
//	Date:	05/26/97		 //
///////////////////////////////

#ifndef _WIN32_WINNT
#define _WIN32_WINNT	0x0400

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define	NO_FLAGS_SET	0

#define WM_WSAASYNC	(WM_USER + 0)

// max number connections
#define MAXCONN		 5

// socket states
#define FREE         0
#define LISTENING    1
#define CONNECTED    2

#define NOTFOUND	-1
#define MAXMSGLEN	80

// output colors
#define COLOR_RED		RGB(175, 0, 0)
#define COLOR_BLUE		RGB(0, 0, 175)
#define	COLOR_GREEN		RGB(0, 175, 0)
#define COLOR_YELLOW	RGB(255,255,0)

#define DEFAULT_FONTSIZE	10
#define DEFAULT_WEIGHT		FW_BOLD
#define DEFAULT_FACENAME	"MS Sans Serif"

#define INIFILE			"\\host.ini"

#define	SERVICE_NAME	"merlin"

typedef struct { // socket info structure
    SOCKET	sdVal;
    INT		iState;
    CHAR	IPAddress[16];
    REQUEST	Request;
} SDSTRUCT, *LPSDSTRUCT ;

typedef struct { // screen line structure
    COLORREF	uColor;
    CHAR		szText[255];
} SCREENLINE, *LPSCREENLINE;

typedef struct {	// logging structure
    BOOL		bIsLogging;
    CHAR		szFileName[_MAX_PATH + _MAX_FNAME];
} LOGSTRUCT, *LPLOGSTRUCT, **PPLOGSTRUCT;

typedef struct tm* LPTIME;

BOOL				InitApplication(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE hInstance, INT nCmdShow);
LONG	APIENTRY	MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD				AsyncListen(HWND hWndList, WORD wPort);
DWORD				FillAddress(HWND hWnd, SOCKADDR_IN* pSin, LPSTR lpszHostName, WORD wPort);
VOID				AddListItem(HWND hWndList, LPSCREENLINE pSL);
WORD				ResolveServicePort(VOID);
BOOL	WINAPI		AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL	WINAPI		SplashProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
VOID				CenterDialog(HWND hDlg, BOOL bOwner);
INT					GetCharHeight(HWND hWnd, LPLOGFONT pLF);
BOOL	WINAPI		PrefProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
VOID				InitAppData(VOID);
VOID				UpdateInitData(VOID);
VOID				WriteLogEntry(HWND hWndList, LPCSTR szLogEntry);
INT					GetSocket(VOID);
INT					FindSocket(SOCKET sdParam);
HWND				CreateListBox(HWND hWnd);
VOID				ReceiveCmd(HWND hWndList, INT i);
BOOL	WINAPI		ActiveConnProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
#endif	// _WIN32_WINNT