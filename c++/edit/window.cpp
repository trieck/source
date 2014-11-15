/////////////////////////////////////////////////////////////////////////////
//
// WINDOW.CPP : main windowing class
//
// Copyright (c) 1999 Rieck Enterprises
//

#include "common.h"

Window::Window()
    : m_hWnd(0)
{
}

Window::~Window()
{
}

void Window::RegisterMessages()
{
    // empty
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam)
{
    static Window * pWnd;
    ASSERT(pWnd == NULL || pWnd->m_hWnd == hWnd);

    if (uMsg == WM_CREATE)
        pWnd = (Window *)((LPCREATESTRUCT)lParam)->lpCreateParams;

    if (pWnd == NULL)
        return DefWindowProc(hWnd, uMsg, wParam, lParam);

    return pWnd->CallWindowProc(uMsg, wParam, lParam);
}

LRESULT Window::CallWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MsgFunc pfnc = m_messagemap[uMsg];
    if (pfnc != NULL) {
        (this->*pfnc)(wParam, lParam);
        return 0;
    }

    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}



