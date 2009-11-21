/*----------------------------------------
	Module	:	CAPP.H
	Date	: 	07/15/1997
	Purpose	:	Generic Window App Class
----------------------------------------*/

#ifndef _CAPP_H_
#define _CAPP_H_

#ifdef UNICODE
#define _UNICODE
#endif // UNICODE

#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#include <commctrl.h>
#include <assert.h>

#include "comtypes.h"
#include "iface.h"

#define COLOR_RED		RGB(150, 0, 0)
#define COLOR_BLUE		RGB(0, 0, 150)
#define COLOR_YELLOW	RGB(255, 255, 0)

#define ICON_WIDTH	15
#define ICON_HEIGHT	15

// Forward declarations
extern "C" const CLSID CLSID_Miscellaneous;

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam);

class CApp {
	friend LRESULT APIENTRY	MainWndProc(HWND, UINT, WPARAM, LPARAM);
	friend LRESULT APIENTRY	ChildProc(HWND, UINT, WPARAM, LPARAM);
	friend BOOL	CALLBACK DriveProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	friend BOOL CALLBACK AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HINSTANCE		m_hInst;
	WNDCLASS		m_wndClass;
	BOOL			m_fInitialized;
	HWND			m_hWnd;
	HWND			m_hWndList;
	HWND			m_hWndStatus;
	INT				m_nCmdShow;
	TCHAR			m_szClassName[_MAX_PATH];
	IMiscellaneous*	m_pIMisc;
	ULONG			m_cRef;
	BOOL			m_fExe;	// Component in .EXE
public:
	CApp(HINSTANCE hInstance, INT nCmdShow);
	~CApp();

	BOOL	Init(LPCTSTR);
	BOOL	Create(LPCTSTR);
	VOID	Trace(LPCTSTR);
	VOID	Trace(wchar_t*);
	VOID	Trace(LONG);
	VOID	StatusTrace(LPCTSTR);

	inline	HWND GetMainWnd() {
		return m_hWnd;
	}
protected:
	BOOL GetDate(BSTR&);
	BOOL GetTime(BSTR&);
	BOOL GetDateTime(BSTR&);
	BOOL GetDriveSpace();
	BOOL EnumDrives(BSTR&);

	VOID DrawStatusBar(LPDRAWITEMSTRUCT);
	VOID DrawListBox(LPDRAWITEMSTRUCT);
};

typedef CApp* PAPP;

#endif // _CAPP_H_