/*----------------------------------------
	Module	:	CAPP.H
	Date	: 	07/15/1997
	Purpose	:	Generic Window App Class
----------------------------------------*/

#ifndef _CAPP_H_
#define _CAPP_H_

#include <windows.h>
#include <commctrl.h>
#include <assert.h>

#define IDC_STATUS 		101

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam);

class CApp
{
    friend LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);
    friend LRESULT APIENTRY ChildProc(HWND, UINT, WPARAM, LPARAM);

protected:
    HINSTANCE		m_hInst;
    WNDCLASS		m_wndClass;
    WNDCLASS		m_wndChildClass;
    HWND			m_hWnd;
    HWND			m_hWndChild;
    HWND			m_hWndStatus;
    INT				m_nCmdShow;
    CHAR			m_szClassName[_MAX_PATH];
public:
    CApp(HINSTANCE hInstance, INT nCmdShow);
    ~CApp();
    BOOL Init(LPCSTR lpszClassName);
    BOOL Create(LPCSTR lpszCaption);
    inline HWND GetMainWnd()
    {
        return m_hWnd;
    }
    VOID Message(LPCTSTR szMessage);
};

typedef CApp* PAPP;

#endif // _CAPP_H_