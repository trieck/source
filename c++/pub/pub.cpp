/*--------------------------------------------
	Module	:	PUB.CPP
	Purpose	:	Public Component Client
	Date	: 	07/19/1997
---------------------------------------------*/

#include <windows.h>
#include <initguid.h>
#include "capp.h"
#include "resource.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPSTR lpCmdLine, INT nCmdShow)
{
    MSG msg;
	
	PAPP pApp = new CApp(hInstance, nCmdShow);
	if (!pApp) return (0);
	
	// Initialize application
	if (!pApp->Init(_T("PubClass")))
		return (0);

	// Create main window
	if (!pApp->Create(_T("Public Component")))
		return (0);

	// Create child window
	pApp->CreateChild(MAKEINTRESOURCE(IDD_COMPONENT), 
			(DLGPROC)DlgProc);
					
    while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!pApp->GetChildWnd() || 
			!IsDialogMessage(pApp->GetChildWnd(), &msg))
		{
			TranslateMessage(&msg);    
			DispatchMessage(&msg);     
		}
	}
	
	if (pApp) delete pApp;

    return (msg.wParam); 
}

CApp :: CApp(HINSTANCE hInstance, INT nCmdShow)
{
	m_hInst 			= hInstance;
	m_nCmdShow			= nCmdShow;
	m_hWndFrame			= 0;
	m_hWndClient		= 0;
	m_hWndChild			= 0;
	m_szClassName[0]	= '\0';
	m_bInitialized		= FALSE;
	m_bExe				= FALSE;
	m_pIUnknown			= NULL;
	m_pIAdviseSink		= NULL;
	m_pIDataObject		= NULL;
	m_cRef				= 0;
	m_dwConn			= 0;
}

BOOL CApp :: Init(LPCTSTR lpszClassName)
{
	WNDCLASS wndclass;

	if (!lpszClassName)
		return (FALSE);

	strcpy (m_szClassName, lpszClassName);

	// Initialize COM library
	if (FAILED(OleInitialize(NULL)))
		m_bInitialized = FALSE;
	else
		m_bInitialized = TRUE;

	// Create main window class
	wndclass.style			= CS_NOCLOSE;                    
    wndclass.lpfnWndProc	= (WNDPROC)MainWndProc;       
	wndclass.cbClsExtra		= 0;
    wndclass.cbWndExtra		= 0;
    wndclass.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN));
    wndclass.hInstance		= m_hInst;
    wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground	= NULL;
    wndclass.lpszMenuName	= NULL;
    wndclass.lpszClassName	= m_szClassName; 

    if (!RegisterClass(&wndclass))
		return (FALSE);

	// Create Client Class
	wndclass.style			= 0;  
	wndclass.lpfnWndProc	= (WNDPROC)ClientProc;       
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hIcon			= 0;
	wndclass.hInstance		= m_hInst;
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= NULL;
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= _T("ClientClass");

	if (!RegisterClass(&wndclass))
		return (FALSE);

	if (!(m_pIAdviseSink = new CAdviseSink(this)))
        return FALSE;

    m_pIAdviseSink->AddRef();

	return (TRUE);
}

BOOL CApp :: Create(LPCTSTR lpszCaption)
{
	m_hWndFrame = CreateWindowEx(
			0L,							
			m_szClassName,                  
			lpszCaption,   
			WS_OVERLAPPEDWINDOW,            // Window style.                      
			CW_USEDEFAULT,                  // Default horizontal position.       
			CW_USEDEFAULT,                  // Default vertical position.         
			CW_USEDEFAULT,                  // Default width.                     
			CW_USEDEFAULT,                  // Default height.                    
			NULL,                           // Overlapped windows have no parent. 
			NULL,                           // Use the window class menu.         
			m_hInst,						// This instance owns this window.    
			this							// Object back pointer
			);
    
    if (!m_hWndFrame)
        return (FALSE);

	// Create client window
	m_hWndClient = 	CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, 
				_T("ClientClass"),
				NULL, 
				WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, 
				CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT, 
				m_hWndFrame, NULL,m_hInst,
				this);

	if (!m_hWndClient)
		return (FALSE);
	
	// Create Status Bar
	InitCommonControls();
	m_hWndStatus = CreateStatusWindow(WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
						NULL, m_hWndFrame, IDC_STATUS);

	if (!m_hWndStatus)
		return (FALSE);

    ShowWindow(m_hWndFrame, m_nCmdShow);  
    UpdateWindow(m_hWndFrame);          

    return (TRUE);
}     

VOID CApp :: CreateChild(LPCTSTR szDialogName, DLGPROC lpDlgProc)
{
	m_hWndChild = CreateDialogParam(m_hInst, 
					szDialogName, 
					m_hWndFrame, 
					lpDlgProc, 
					(LPARAM)this);
}

HWND CApp :: GetMainWnd()
{
	return (m_hWndFrame);
}

HWND CApp :: GetClientWnd()
{
	return (m_hWndClient);
}

HWND CApp :: GetChildWnd()
{
	return (m_hWndChild);
}

HWND CApp :: GetStatusBar()
{
	return (m_hWndStatus);
}

VOID CApp :: Paint(LPPAINTSTRUCT lpPS)
{
	HBRUSH	hBrush, hBrushOld;
	
	SetViewportExtEx(lpPS->hdc, lpPS->rcPaint.right - lpPS->rcPaint.left,
								lpPS->rcPaint.bottom - lpPS->rcPaint.top, NULL);

	hBrush		= (HBRUSH)GetSysColorBrush(COLOR_WINDOW);
	
	hBrushOld	= (HBRUSH)SelectObject(lpPS->hdc, hBrush);

	PatBlt(lpPS->hdc, lpPS->rcPaint.left, 
				lpPS->rcPaint.top, 
				lpPS->rcPaint.right - lpPS->rcPaint.left, 
				lpPS->rcPaint.bottom - lpPS->rcPaint.top,
				PATCOPY);
	
    SelectObject(lpPS->hdc, hBrushOld);
	DeleteObject(hBrush);

	if (m_pIUnknown)
		OleDraw(m_pIUnknown, DVASPECT_CONTENT, lpPS->hdc, &lpPS->rcPaint);
}

BOOL CApp :: SaveObject(LPCTSTR lpszFileName)
{
	HRESULT		hr;
	LPSTORAGE	pIStorage;
	LONG		lRet;
	OLECHAR		szName[20];
	CHAR		szTemp[20];

	if (!lpszFileName)
		return (FALSE);

#ifndef UNICODE
	strcpy(szTemp, lpszFileName);

	MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szName, 20);
#else
	wcscpy(szName, lpszFileName);
#endif
	
	hr = StgCreateDocfile(szName, STGM_DIRECT | STGM_WRITE
			| STGM_CREATE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 0, &pIStorage);

	if (FAILED(hr))
		return (FALSE);

	// Mark this as one of our class
	WriteClassStg(pIStorage, CLSID_DrawObject);

	// Write User Readable Class Information
#ifndef UNICODE
	strcpy(szTemp, _T("Draw Object"));

	MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szName, 20);
#else
	wcscpy(szName, _T("Draw Object"));
#endif
	WriteFmtUserTypeStg(pIStorage, CF_METAFILEPICT, szName);

	// Write the data to storage
	lRet = WriteToStorage(pIStorage);
	pIStorage->Release();
		
	if (!lRet) return (FALSE);
	
	return (TRUE);
}

BOOL CApp :: LoadObject(LPCTSTR lpszFileName)
{
	HRESULT		hr;
	LPSTORAGE	pIStorage;
	LONG		lRet;
	OLECHAR		szFileName[_MAX_PATH];
	
	if (!lpszFileName)
		return (FALSE);

#ifndef UNICODE
	CHAR szTemp[_MAX_PATH];
	
	strcpy(szTemp, lpszFileName);

	MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szFileName, _MAX_PATH);
#else
	wcscpy(szFileName, lpszFileName);
#endif

	if (StgIsStorageFile(szFileName) != NOERROR)
		return (FALSE);

	hr = StgOpenStorage(szFileName, NULL,
			STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
			NULL, 0, &pIStorage);
	
	if (FAILED(hr))
		return (FALSE);

	lRet = ReadFromStorage(pIStorage);
	pIStorage->Release();

	if (!lRet)
		return (FALSE);

	return (TRUE);
}

BOOL CApp :: ReadFromStorage(LPSTORAGE pIStorage)
{
	HRESULT				hr;
	LPPERSISTSTREAM		pIPersistStream;
	LPSTREAM			pIStream;
	OLECHAR				szStream[20];
	
	if (!pIStorage || !m_pIDataObject)
		return (FALSE);

	// Open the stream
#ifndef UNICODE
	CHAR szTemp[20];
	
	strcpy(szTemp, SZSTREAM);

	MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szStream, 20);
#else
	wcscpy(szStream, SZSTREAM);
#endif

	hr = pIStorage->OpenStream(szStream, 0, STGM_DIRECT | STGM_READ
			| STGM_SHARE_EXCLUSIVE, 0, &pIStream);

	if (FAILED(hr))
		return (FALSE);

	// Does the object support IPersistStream?
	hr = m_pIUnknown->QueryInterface(IID_IPersistStream, 
					(PPVOID)&pIPersistStream);

	if (FAILED(hr))
	{
		pIStream->Release();
		return (FALSE);
	}

	// Load the data
	hr = pIPersistStream->Load(pIStream);
	
	pIStream->Release();
	pIPersistStream->Release();
	
	if (FAILED(hr))
		return (FALSE);

	return (FAILED(hr) ? FALSE : TRUE);
}

BOOL CApp :: WriteToStorage (LPSTORAGE pIStorage)
{
	HRESULT			hr;
	LPSTREAM		pIStream;
	LPPERSISTSTREAM	pIPersistStream;
	OLECHAR			szStream[20];

	if (!pIStorage)
		return (FALSE);

#ifndef UNICODE
	CHAR szTemp[20];
	
	strcpy(szTemp, SZSTREAM);

	MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szStream, 20);
#else
	wcscpy(szStream, SZSTREAM);
#endif	

	hr = pIStorage->CreateStream(szStream, STGM_DIRECT | STGM_CREATE
			| STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &pIStream);

	if (FAILED(hr))
		return (FALSE);

	// Does the object support IPersistStream?
	hr = m_pIUnknown->QueryInterface(IID_IPersistStream, 
					(PPVOID)&pIPersistStream);

	if (FAILED(hr))
	{
		pIStream->Release();
		return (FALSE);
	}

	// Save the data
	hr = pIPersistStream->Save(pIStream, TRUE);
	
	pIStream->Release();
	pIPersistStream->Release();
	
	if (FAILED(hr))
		return (FALSE);

	return (TRUE);
}

VOID CApp :: Message (LPCTSTR szMessage)
{
	SetWindowText(m_hWndStatus, szMessage);
}

// Overloaded function to deal with string resources
VOID CApp :: Message (UINT wResName)
{
	DWORD	dwByteSize = 256;
	LPTSTR	pData;
	
	pData = (LPTSTR)CoTaskMemAlloc(dwByteSize);
	if (!pData)
		return;

	LoadString(m_hInst, wResName, pData, dwByteSize);

	Message(pData);

	CoTaskMemFree(pData);
}

VOID CApp :: UpdateControls()
{
	PDRAWOBJECT	pObj;
	HRESULT		hr;
	COLORREF	lColor;
	BYTE		rValue;

	if (m_pIUnknown)
	{
		hr = m_pIUnknown->QueryInterface(IID_IDrawObject,
				(PPVOID)&pObj);

		if (FAILED(hr))
			return;
				
		pObj->GetColor(&lColor);
		pObj->Release();
			
		rValue = GetRValue(lColor);

		SendDlgItemMessage(m_hWndChild, IDC_COLORSLIDE, TBM_SETPOS, TRUE, rValue);
		InvalidateRect(m_hWndChild, 0, TRUE);
	}
}

BOOL CApp :: Clip()
{
	HRESULT			hr;
	PDRAWOBJECT		pObj;
	LPDATAOBJECT	pIDataObject;
	FORMATETC		fe;
	STGMEDIUM		stm;
	
	if (!m_pIUnknown || !m_pIDataObject)
		return FALSE;
	
	hr = CoCreateInstance(CLSID_DrawObject, 
			NULL, CLSCTX_INPROC_SERVER,
			IID_IDrawObject, (PPVOID)&pObj);

	if (FAILED(hr))
		return FALSE;

	fe.cfFormat	= CF_METAFILEPICT;
	fe.dwAspect	= DVASPECT_CONTENT;
	fe.ptd		= NULL;
	fe.tymed	= TYMED_MFPICT;
	fe.lindex	= -1;
	
	hr = m_pIDataObject->GetData(&fe, &stm);
	
	if (FAILED(hr))
	{
		pObj->Release();
		return FALSE;
	}

	pObj->QueryInterface(IID_IDataObject, (PPVOID)&pIDataObject);
	pObj->Release();

	pIDataObject->SetData(&fe, &stm, TRUE);

	// Set the data
	hr = OleSetClipboard(pIDataObject);

	pIDataObject->Release();

	return (SUCCEEDED(hr));
}
	
CApp :: ~CApp()
{
	if (IsWindow(m_hWndChild))	DestroyWindow(m_hWndChild);
	if (IsWindow(m_hWndClient))	DestroyWindow(m_hWndClient);
	if (IsWindow(m_hWndFrame))	DestroyWindow(m_hWndFrame);

	if (m_dwConn)
		m_pIDataObject->DUnadvise(m_dwConn);

	ReleaseInterface(m_pIAdviseSink);
	ReleaseInterface(m_pIDataObject);

	while (m_cRef-- > 0)
        m_pIUnknown->Release();

    m_pIUnknown = NULL;
		
	OleFlushClipboard();

	if (m_bInitialized)
		OleUninitialize();
}


LRESULT APIENTRY MainWndProc(HWND hWnd, UINT message,             
				WPARAM wParam, LPARAM lParam)
{
	static PAPP pApp;
	
	switch (message) 
	{
	case WM_CREATE:
		pApp = (PAPP)((LPCREATESTRUCT)lParam)->lpCreateParams;
		break;
	case WM_SIZE:
		RECT 	rc, rcStatus;
		INT 	xClient, yClient, yStatus;
		
		GetClientRect(hWnd, &rc);
		GetWindowRect(pApp->m_hWndStatus, &rcStatus);
		
		xClient = (rc.right - rc.left);
		yClient = (rc.bottom - rc.top);
		
		yStatus = (rcStatus.bottom - rcStatus.top);

		SendMessage(pApp->m_hWndStatus, WM_SIZE, wParam, lParam);
		MoveWindow(pApp->m_hWndClient, 0, 0, xClient, yClient - yStatus, TRUE);
		break;
	case WM_DESTROY:
		DestroyWindow(pApp->m_hWndClient);
		DestroyWindow(pApp->m_hWndChild);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
} 

LRESULT APIENTRY ClientProc(HWND hWnd, UINT message,             
				WPARAM wParam, LPARAM lParam)
{
	static	PAPP		pApp;
			PAINTSTRUCT	ps;
			HDC			hDC;
			INT			cxClient, cyClient;
			PDRAWOBJECT pObj;
			HRESULT		hr;
			RECT		rc;

	switch (message) 
	{
	case WM_CREATE:
		pApp = (PAPP)((LPCREATESTRUCT)lParam)->lpCreateParams;

		hDC = GetDC(hWnd);
		
		SetMapMode(hDC, MM_ANISOTROPIC);
		SetWindowExtEx(hDC, 1024, 1024, NULL);
		
		ReleaseDC(hWnd, hDC);
		break;
	case WM_SIZE:
		if (!pApp->m_pIUnknown)
			break;

		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		SetRect(&rc, 0, 0, cxClient, cyClient);

		hr = pApp->m_pIUnknown->QueryInterface(
					IID_IDrawObject, 
					(PPVOID)&pObj);

		if (FAILED(hr))
			break;

		pObj->SetBounds(&rc);
		pObj->Release();

		InvalidateRect(hWnd, 0, TRUE);
		break;
	case WM_ERASEBKGND:
		return (1);
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		pApp->Paint(&ps);
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
} 

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg,             
				WPARAM wParam, LPARAM lParam)
{
	static PAPP pApp;
	static HWND	hWndColor, hWndTrack;
	static RECT	rcColor;
	HRESULT		hr;
	DWORD		dwClsCtx;

	switch (msg)
	{
	case WM_HSCROLL:
		PDRAWOBJECT		pObj;
		INT				nValue;
				
		if ((HWND)lParam == hWndTrack)
		{
			nValue = SendMessage(hWndTrack, TBM_GETPOS, 0, 0);

			// Redraw dialog color
			RedrawWindow(hDlg, &rcColor, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ERASENOW);

			// Set object color and redraw it
			if (pApp->m_pIUnknown)
			{
				hr = pApp->m_pIUnknown->QueryInterface(IID_IDrawObject,
						(PPVOID)&pObj);

				if (FAILED(hr))
					break;
				
				pObj->SetColor(RGB(nValue, 0, nValue));
				pObj->Release();
			}
		}
		break;
	case WM_INITDIALOG:
		pApp = (PAPP)lParam;

		// Get color window handle
		hWndColor = GetDlgItem(hDlg, IDC_COLOR);

		// Get Color rectangle
		GetClientRect(hWndColor, &rcColor);

		// Get Trackbar window handle
		hWndTrack = GetDlgItem(hDlg, IDC_COLORSLIDE);

		// Set the icon
		SetClassLong(hDlg, GCL_HICON, (LONG)LoadIcon(pApp->m_hInst, MAKEINTRESOURCE(IDI_MAIN)));

		// Set the Trackbar range
		SendMessage(hWndTrack, TBM_SETRANGE, TRUE, MAKELONG(0, 255));
		return (TRUE);
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CREATE:
			if (pApp->m_pIUnknown)
            {
				if (pApp->m_dwConn)
					pApp->m_pIDataObject->DUnadvise(pApp->m_dwConn);

				while (pApp->m_cRef--)
					pApp->m_pIUnknown->Release();
				
				CoFreeUnusedLibraries();
				pApp->m_pIUnknown = NULL;
			}
			pApp->m_cRef = 0;

			dwClsCtx = (pApp->m_bExe) ? CLSCTX_LOCAL_SERVER
                        : CLSCTX_INPROC_SERVER;

			// Create an instance of the object
			hr  = CoCreateInstance(CLSID_DrawObject, NULL,
						dwClsCtx, IID_IUnknown, (PPVOID)&pApp->m_pIUnknown);

            if (SUCCEEDED(hr))
            {
				pApp->m_cRef = 1;

				// Attempt to cache an IDataObject pointer
				hr = pApp->m_pIUnknown->QueryInterface(IID_IDataObject,
							(PPVOID)&pApp->m_pIDataObject);

				if (FAILED(hr))
				{
					pApp->Message(IDS_CREATEFAILED);
					break;
				}

				FORMATETC fe;
				SetDefFormatEtc(fe, CF_METAFILEPICT, TYMED_MFPICT);

				// Create an advisory connection
				pApp->m_pIDataObject->DAdvise(&fe, ADVF_NODATA, 
						pApp->m_pIAdviseSink, &pApp->m_dwConn);

				pApp->Message(IDS_CREATESUCCEED);
			}
			else
				pApp->Message(IDS_CREATEFAILED);
			break;
		case IDC_DRAW:
			PDRAWOBJECT pDrawObj;
									
			if (!pApp->m_pIUnknown)
			{
				pApp->Message(IDS_NOOBJECT);
				break;
			}

			// Do you support IDrawObject?
			hr = pApp->m_pIUnknown->QueryInterface(IID_IDrawObject,
					(PPVOID)&pDrawObj);
			
			if (FAILED(hr))
			{
				pApp->Message(IDS_INOSUPPORT);
				break;
			}
			
			hr = pDrawObj->Randomize();
						
			pDrawObj->Release();

			InvalidateRect(pApp->m_hWndClient, 0, TRUE);
			break;
		case IDC_COPY:
			if (!pApp->m_pIUnknown)
			{
				pApp->Message(IDS_NOOBJECT);
				break;
			}

			if (!pApp->Clip())
				pApp->Message(IDS_COPYFAIL);
			else
				pApp->Message(IDS_COPYSUCCEED);
			break;
		case IDC_LOAD:
			if (!pApp->m_pIUnknown)
			{
				pApp->Message(IDS_NOOBJECT);
				break;
			}

			if (!pApp->LoadObject(SZFILE))
			{
				pApp->Message(IDS_NOLOAD);
				break;
			}
			
			pApp->Message(IDS_LOAD);
			InvalidateRect(pApp->m_hWndClient, 0, TRUE);
			break;
		case IDC_SAVE:
			if (!pApp->m_pIUnknown)
			{
				pApp->Message(IDS_NOOBJECT);
				break;
			}
			
			if (!pApp->SaveObject(SZFILE))
				pApp->Message(IDS_NOSAVE);
			else
				pApp->Message(IDS_SAVE);
							
			break;
		case IDCANCEL:
		case IDC_EXIT:
			PostMessage(pApp->m_hWndFrame, WM_CLOSE, 0, 0);
			break;
		}
		default:
			break;
	case WM_PAINT:
		HDC			hDCColor;
		HBRUSH		hBrush, hBrushOld;
		PAINTSTRUCT ps;
		INT			iValue;

		BeginPaint(hDlg, &ps);

		// get trackbar value
		iValue = (INT)SendMessage(hWndTrack, TBM_GETPOS, 0, 0);
		
		hBrush = CreateSolidBrush(RGB(iValue, 0, iValue));

		hDCColor = GetDC(hWndColor);

		hBrushOld = (HBRUSH)SelectObject(hDCColor, hBrush);

		PatBlt(hDCColor, rcColor.left, 
					rcColor.top, 
					rcColor.right, 
					rcColor.bottom, PATCOPY);
				
		SelectObject(hDCColor, hBrushOld);
		DeleteObject(hBrush);

		ReleaseDC(hWndColor, hDCColor);

		EndPaint(hDlg, &ps);
		break;
	}
	return (FALSE);
}