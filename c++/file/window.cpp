/////////////////////////////////////////////////////////////////////////////
//
// WINDOW.CPP : Win32 window base class
//

#include "common.h"
#include "window.h"

// static initializers
HHOOK Window::oldCbtHook = NULL;
Window* Window::wndInit = NULL;
Window::WindowMap Window::windowMap;

const RECT Window::rectDefault = {
	CW_USEDEFAULT, CW_USEDEFAULT,
	0 /* 2*CW_USEDEFAULT */, 0 /* 2*CW_USEDEFAULT */
};

Window::Window()
	: hWnd(0)
{
}

Window::~Window()
{
}

/////////////////////////////////////////////////////////////////////////////
bool Window::create(LPCTSTR className, LPCTSTR windowName,
                    DWORD style, LPRECT rect, Window *parent, LPVOID param)
{
	ASSERT(className != NULL);
	ASSERT(windowName != NULL);
	ASSERT(rect != NULL);

	CREATESTRUCT cs;
	cs.dwExStyle = 0;
	cs.lpszClass = registerClass();
	cs.lpszName = windowName;
	cs.style = style;
	cs.x = rect->left;
	cs.y = rect->top;
	cs.cx = rect->right - rect->left;
	cs.cy = rect->bottom - rect->top;
	cs.hwndParent = parent ? parent->getHandle() : NULL;
	cs.hMenu = NULL;	// TODO:
	cs.hInstance = getInstance();
	cs.lpCreateParams = param;

	hookWindowCreate(this);

	HWND hWindow = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
	                                cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
	                                cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);

	unhookWindowCreate();

	ASSERT(hWindow == hWnd);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
LPCTSTR Window::registerClass()
{
	static TCHAR name[1024];

	WNDCLASS wndcls;
	memset(&wndcls, 0, sizeof(WNDCLASS));

	wndcls.lpfnWndProc = DefWindowProc;
	wndcls.hInstance = getInstance();
	wndcls.hCursor = NULL;

	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	_stprintf(name, _T("Neptune:%x:%x"), getInstance(), wndcls.style);

	wndcls.lpszClassName = name;

	RegisterClass(&wndcls);

	return name;
}

/////////////////////////////////////////////////////////////////////////////
bool Window::attach(HWND handle)
{
	ASSERT(::IsWindow(handle));
	ASSERT(hWnd == NULL);

	Window *pWnd = lookupWindow(handle);
	ASSERT(pWnd == NULL);
	if (pWnd)
		return false;	// already exists

	windowMap[(hWnd = handle)] = this;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool Window::detach()
{
	if (hWnd != NULL) 	{
		//CHandleMap* pMap = afxMapHWND(); // don't create if not exist
		//if (pMap != NULL)
		//	pMap->RemoveHandle(m_hWnd);
		hWnd = NULL;
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
Window * Window::lookupWindow(HWND hWnd)
{
	WindowMap::const_iterator it = windowMap.find(hWnd);
	if (it == windowMap.end())
		return NULL;

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
bool Window::hookWindowCreate(Window *pWnd)
{
	ASSERT(pWnd != NULL);
	ASSERT(Window::oldCbtHook == NULL);

	if (wndInit == pWnd)
		return FALSE;

	oldCbtHook = ::SetWindowsHookEx(WH_CBT,
	                                cbtFilterHook, NULL, ::GetCurrentThreadId());

	wndInit = pWnd;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
bool Window::unhookWindowCreate()
{
	if (oldCbtHook != NULL) {
		::UnhookWindowsHookEx(oldCbtHook);
		oldCbtHook = NULL;
	}

	if (wndInit != NULL)
		return FALSE;	// not successfully hooked

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Window::cbtFilterHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HCBT_CREATEWND)	{
		return CallNextHookEx(oldCbtHook, code, wParam, lParam);
	}

	LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
	ASSERT(lpcs != NULL);

	if (wndInit != NULL) {
		HWND hWnd = (HWND)wParam;
		ASSERT(hWnd != NULL);

		wndInit->hWnd = hWnd;

		bool bWndProc = ((WNDPROC) GetWindowLong(hWnd, GWL_WNDPROC) == NeptuneWndProc);
		if (!bWndProc) {
			WNDPROC oldWndProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC,
			                     (DWORD)NeptuneWndProc);
			ASSERT(oldWndProc != NULL);
		}

		wndInit = NULL;
	}

	return CallNextHookEx(oldCbtHook, code, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Window::NeptuneWndProc(HWND hWnd, UINT msg, WPARAM wParam,
                                        LPARAM lParam)
{
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}


