/////////////////////////////////////////////////////////////////////////////
//
//	WINAPP.H : windows application
//

#ifndef __WINAPP_H__
#define __WINAPP_H__

#include <windows.h>
#include <tchar.h>

typedef struct {
    HINSTANCE hInstance;
    LPTSTR command;
    int show;
    HWND hWndMain;
} WinApp;

// Helper functions
BOOL centerWindow(HWND hWnd, HWND hWndParent);
BOOL pumpMessages();
void enterModalLoop(HWND hWnd);
void endModalLoop(HWND hWnd);

extern WinApp *App;

// application defined
extern BOOL initApp(void);
extern int runApp(void);
extern int exitApp(void);

#endif // __WINAPP_H__
