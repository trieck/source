/////////////////////////////////////////////////////////////////////////////
//
// WINDOW.H : main windowing class
//
// Copyright (c) 1999 Rieck Enterprises
//

#ifndef __WINDOW_H__
#define __WINDOW_H__

// forward declarations
class Window;

typedef void(Window::*MsgFunc)(WPARAM, LPARAM);

#define REGISTER_MESSAGE(msg, pfn) \
	m_messagemap[msg] = (MsgFunc)pfn;

/////////////////////////////////////////////////////////////////////////////
class Window {
// Construction / Destruction
public:
    Window();
    virtual ~Window();

// Interface
    BOOL Show(int nCmdShow = 0);
    BOOL Update();
    operator HWND() const;

// Implementation
protected:
    virtual BOOL Create(LPCSTR caption, int x, int y, int width, int height) = 0;
    LRESULT CallWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void RegisterMessages();

    HWND m_hWnd;
    map<UINT, MsgFunc> m_messagemap;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam);
};
/////////////////////////////////////////////////////////////////////////////

inline Window::operator HWND () const
{
    return m_hWnd;
}

inline BOOL Window::Show(int nCmdShow)
{
    ASSERT(*this != NULL);
    if (nCmdShow == 0)
        nCmdShow = pApp->GetShow();
    return ::ShowWindow(*this, nCmdShow);
}

inline BOOL Window::Update()
{
    ASSERT(*this != NULL);
    return ::UpdateWindow(*this);
}

#endif // __WINDOW_H__