/////////////////////////////////////////////////////////////////////////////
//
// WINDOW.H : Win32 window base class
//

#ifndef __WINDOW_H__
#define __WINDOW_H__

/////////////////////////////////////////////////////////////////////////////
class Window {
public:
	typedef map<HWND, Window *> WindowMap;
// Construction / Destruction
	Window();
	virtual ~Window();

// Interface
	static bool hookWindowCreate(Window *pWnd);
	static bool unhookWindowCreate();
	static const RECT rectDefault;
	virtual bool create(LPCTSTR className, LPCTSTR windowName,
	                    DWORD style = WS_OVERLAPPEDWINDOW, LPRECT rect = (LPRECT)&rectDefault, Window *parent = NULL,
	                    LPVOID param = NULL);

	HWND getHandle() const;

	bool showWindow(int show) const;
	bool updateWindow() const;

// Implementation
	bool attach(HWND hWnd);
	bool detach();

protected:
	static LPCTSTR registerClass();
	static Window *lookupWindow(HWND hWnd);
	static LRESULT CALLBACK cbtFilterHook(int code, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK NeptuneWndProc(
	    HWND hWnd,
	    UINT Msg,
	    WPARAM wParam,
	    LPARAM lParam);

private:
	static HHOOK oldCbtHook;
	static Window *wndInit;	// in hook progress
	static WindowMap windowMap;
	HWND hWnd;
};
/////////////////////////////////////////////////////////////////////////////

inline HWND Window::getHandle() const
{
	return hWnd;
}

inline bool Window::showWindow(int show) const
{
	ASSERT(hWnd);
	return ShowWindow(hWnd, show) == TRUE;
}

inline bool Window::updateWindow() const
{
	ASSERT(hWnd);
	return UpdateWindow(hWnd) == TRUE;
}

#endif // __WINDOW_H__

