/*----------------------------------------
	Module	:	CAPP.H
	Date	: 	07/15/1997
	Purpose	:	Generic Window App Class
----------------------------------------*/

#ifndef _CAPP_H_
#define _CAPP_H_

#include <windows.h>
#include <commctrl.h>
#include <TCHAR.H>

#include "olemac.h"
#include "interfac.h"

#define SZSTREAM	_T("MyStream")
#define SZFILE		_T("object.dat")

LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,
                             WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY ClientProc(HWND hWnd, UINT message,
                            WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hWnd, UINT message,
                      WPARAM wParam, LPARAM lParam);

class CAdviseSink;
typedef class CAdviseSink *PCAdviseSink;

class CApp {
    friend	LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);
    friend	LRESULT APIENTRY ClientProc(HWND, UINT, WPARAM, LPARAM);
    friend	BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
    friend	class CAdviseSink;

protected:
    HINSTANCE		m_hInst;
    HWND			m_hWndFrame;
    HWND			m_hWndClient;
    HWND			m_hWndChild;
    HWND			m_hWndStatus;
    INT				m_nCmdShow;
    TCHAR			m_szClassName[_MAX_PATH];
    BOOL			m_bInitialized;
    BOOL			m_bExe;
    LPUNKNOWN		m_pIUnknown;
    PCAdviseSink	m_pIAdviseSink;
    LPDATAOBJECT	m_pIDataObject;
    DWORD			m_cRef;		// reference count
    DWORD			m_dwConn;	// advisory connection
public:
    CApp(HINSTANCE hInstance, INT nCmdShow);
    ~CApp();
    BOOL Init(LPCTSTR);
    BOOL Create(LPCTSTR);
    VOID CreateChild(LPCTSTR, DLGPROC);
    HWND GetMainWnd();
    HWND GetClientWnd();
    HWND GetChildWnd();
    HWND GetStatusBar();
    VOID Message(LPCTSTR);
    VOID Message(UINT);
    VOID Paint(LPPAINTSTRUCT lpPS);
    BOOL SaveObject(LPCTSTR);
    BOOL LoadObject(LPCTSTR);
    VOID UpdateControls();
    BOOL Clip();
protected:
    BOOL WriteToStorage(LPSTORAGE);
    BOOL ReadFromStorage(LPSTORAGE);
};

typedef CApp* PAPP;

class CAdviseSink : public IAdviseSink {
protected:
    ULONG               m_cRef;
    PAPP                m_pApp;

public:
    CAdviseSink(PAPP);
    ~CAdviseSink();

    // IUnknown members
    STDMETHODIMP QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IAdviseSink members
    STDMETHODIMP_(VOID)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
    STDMETHODIMP_(VOID)  OnViewChange(DWORD, LONG);
    STDMETHODIMP_(VOID)  OnRename(LPMONIKER);
    STDMETHODIMP_(VOID)  OnSave();
    STDMETHODIMP_(VOID)  OnClose();
};

#endif // _CAPP_H_