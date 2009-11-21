/*--------------------------------------------
	Module	:	EMISC.CPP
	Date	: 	10/31/1997
	Purpose	:	Out of Process Server
---------------------------------------------*/

#include "capp.h"
#include "resource.h"
#include "misc.h"
#include "registry.h"

// Static variables
static	LONG	g_cComponents	= 0;		// Count of active components
static	LONG	g_cServerLocks	= 0;		// Count of locks
static	HWND	g_hWnd			= NULL;		// Global window handle

// ObjectDestroyed():
// Shut down window when there
// are no more components or server locks
VOID ObjectDestroyed()
{
	g_cComponents--;

	//No more objects and no locks, shut the app down.
	if (0L == g_cComponents && 0L== g_cServerLocks && IsWindow(g_hWnd))
		PostMessage(g_hWnd, WM_CLOSE, 0, 0);

}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, INT nCmdShow)
{
	MSG	msg;

	// Controls whether UI is shown or not
	BOOL bUI = TRUE;

	// If TRUE, don't loop.
	BOOL bExit = FALSE;

	// Initialize the COM Library.
	HRESULT hr = CoInitialize(NULL) ;
	if (FAILED(hr))
		return 0;

	// Read the command line.
	TCHAR	szTokens[] = _T("-/");
	TCHAR	szCmdLine[128];
	LPTSTR	lpszToken;

#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpCmdLine, - 1, szCmdLine, 128);
	lpszToken = wcstok(szCmdLine, szTokens);
#else
	strcpy(szCmdLine, lpCmdLine);
	lpszToken = strtok(szCmdLine, szTokens);
#endif

	while (lpszToken != NULL) {
#ifdef _UNICODE
		if (_wcsicmp(lpszToken, _T("UnregServer")) == 0)
#else
		if (_stricmp(lpszToken, _T("UnregServer")) == 0)
#endif
		{
			UnregisterServer(CLSID_Miscellaneous, g_szVerIndProgID,
			g_szProgID);

			// We are done, so exit.
			bExit = TRUE;
			bUI = FALSE;
		}
#ifdef _UNICODE
		else if (_wcsicmp(lpszToken, _T("RegServer")) == 0)
#else
		else if (_stricmp(lpszToken, _T("RegServer")) == 0)
#endif
		{
			RegisterServer(hInstance, CLSID_Miscellaneous,
			g_szFriendlyName, g_szVerIndProgID, g_szProgID,
			LIBID_MiscLib);

			// We are done, so exit.
			bExit = TRUE;
			bUI = FALSE;
		}
#ifdef _UNICODE
		else if (_wcsicmp(lpszToken, _T("Embedding")) == 0)
#else
		else if (_stricmp(lpszToken, _T("Embedding")) == 0)
#endif
		{
			// Don't display a window if we are embedded.
			bUI = FALSE ;
			break;
		}
#ifdef _UNICODE
		lpszToken = wcstok(NULL, szTokens);
#else
		lpszToken = strtok(NULL, szTokens);
#endif
	}

	if (bExit) return 0;

	CApp* pApp = new CApp(hInstance, nCmdShow);
	if (!pApp) return -1;

	// Initialize application
	if (!pApp->Init(_T("OutProcServer")))
		return -2;

	// Create window
	if (!pApp->Create(_T("Miscellaneous Server")))
		return -3;

	g_hWnd = pApp->GetMainWnd();

	if (bUI) {
		ShowWindow(g_hWnd, nCmdShow);
		UpdateWindow(g_hWnd);
	}

	LPCLASSFACTORY	pIClassFactory;
	DWORD			dwCookie;

	// Register the Class Factory
	pIClassFactory = new CFactory();
	if (!pIClassFactory)
		return 0;

	hr = ::CoRegisterClassObject(CLSID_Miscellaneous, pIClassFactory
	                             , CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwCookie);
	if (FAILED(hr))
		return 0;

	// Enter the message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Revoke the Class Factory
	// and release the pointer
	if (dwCookie)
		CoRevokeClassObject(dwCookie);

	pIClassFactory->Release();

	if (pApp) delete pApp;

	CoUninitialize();

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

BOOL CApp :: Init(LPCTSTR lpszClassName)
{
	if (!lpszClassName)
		return (FALSE);

#ifdef _UNICODE
	wcscpy (m_szClassName, lpszClassName);
#else
	strcpy (m_szClassName, lpszClassName);
#endif

	// Create Frame class
	m_wndClass.style			= CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc		= (WNDPROC)MainWndProc;
	m_wndClass.cbClsExtra		= 0;
	m_wndClass.cbWndExtra		= 0;
	m_wndClass.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN));
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
	m_wndChildClass.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN));
	m_wndChildClass.hInstance		= m_hInst;
	m_wndChildClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	m_wndChildClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndChildClass.lpszMenuName	= NULL;
	m_wndChildClass.lpszClassName	= _T("ChildClass");

	if (!RegisterClass(&m_wndChildClass))
		return FALSE;

	return TRUE;
}

BOOL CApp :: Create(LPCTSTR lpszCaption)
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

	return (m_hWnd != NULL);
}

CApp::~CApp()
{
	if (IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);
}

VOID CApp :: Message (LPCTSTR szMessage)
{
	MessageBox(m_hWnd, szMessage, m_szClassName, MB_ICONEXCLAMATION);
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
		// Forward message to common controls
		SendMessage(pApp->m_hWndStatus, WM_SETTINGCHANGE, wParam, lParam);
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

LRESULT APIENTRY ChildProc(HWND hWnd, UINT message,
                           WPARAM wParam, LPARAM lParam)
{
	static		PAPP pApp;

	switch (message) {
	case WM_CREATE:
		pApp = (PAPP)((LPCREATESTRUCT)lParam)->lpCreateParams;
		assert(pApp);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
}

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory :: QueryInterface(REFIID iid, PPVOID ppv)
{
	LPUNKNOWN pI;

	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
		pI = static_cast<LPCLASSFACTORY>(this);
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	pI->AddRef();

	*ppv = pI;

	return S_OK;
}

ULONG CFactory :: AddRef()
{
	return ::InterlockedIncrement(&m_cRef);
}

ULONG CFactory :: Release()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}

//
// IClassFactory implementation
//
HRESULT __stdcall CFactory :: CreateInstance(LPUNKNOWN pUnknownOuter,
        REFIID iid, PPVOID ppv)
{
	HRESULT hr = E_FAIL;

	// Cannot aggregate
	if (pUnknownOuter != NULL)
		return CLASS_E_NOAGGREGATION;

	// Create component telling us to notify us when it's gone.
	CMiscellaneous* pMisc = new CMiscellaneous(ObjectDestroyed);
	if (!pMisc) {
		// This starts shutdown if there are no other objects.
		InterlockedIncrement(&g_cServerLocks);
		ObjectDestroyed();
		return E_OUTOFMEMORY;
	}

	// Initialize the component
	HMODULE hModule = GetModuleHandle(NULL);
	hr = pMisc->Init(hModule);
	if (FAILED(hr)) {
		pMisc->Release();
		return hr;
	}

	// Get the requested interface
	hr = pMisc->QueryInterface(iid, ppv);

	pMisc->Release();

	InterlockedIncrement(&g_cComponents);

	return hr;
}

// LockServer
HRESULT __stdcall CFactory :: LockServer(BOOL bLock)
{
	if (bLock)
		InterlockedIncrement(&g_cServerLocks);
	else {
		InterlockedDecrement(&g_cServerLocks);
		//
		// Fake an object destruction:  this centralizes
		// all the shutdown code in the ObjectDestroyed
		// function, eliminating duplicate code here.
		//
		InterlockedIncrement(&g_cServerLocks);

		ObjectDestroyed();
	}

	return S_OK;
}


