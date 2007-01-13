/////////////////////////////////////////////////////////////////////////////
//
// FRAMEWND.CPP : frame window class
//
// Copyright (c) 1999 Rieck Enterprises
//

#include "common.h"
#include "framewnd.h"

static LPCSTR className = "neptuneFrameClass";

FrameWindow::FrameWindow(LPCSTR caption, int x, int y, int width, int height)
{
	RegisterMessages();
	Create(caption, x, y, width, height);
}

FrameWindow::~FrameWindow()
{
}

void FrameWindow::RegisterMessages()
{
	Window::RegisterMessages();

	REGISTER_MESSAGE(WM_DESTROY, FrameWindow::OnDestroy)
	REGISTER_MESSAGE(WM_NCDESTROY, FrameWindow::OnNcDestroy)
}

BOOL FrameWindow::Create(LPCSTR caption, int x, int y, int width, int height)
{
	ASSERT(m_hWnd == NULL);

	WNDCLASS wndclass;
	InitClass(&wndclass);

	if (!RegisterClass(&wndclass))
		return NULL;

	m_hWnd = CreateWindow(
		wndclass.lpszClassName,			// pointer to registered class name
		caption,						// pointer to window name
		WS_OVERLAPPEDWINDOW,			// window style
		x,								// horizontal position of window
		y,								// vertical position of window
		width,							// window width
		height,							// window height
		NULL,							// handle to parent or owner window
		NULL,							// handle to menu or child-window identifier
		pApp->GetCurrentInstance(),     // handle to application instance
		this							// pointer to window-creation data
	);


	return m_hWnd != NULL;
}

void FrameWindow::InitClass(LPWNDCLASS pclass) const
{
	ASSERT(pclass != NULL);
    pclass->style = CS_HREDRAW | CS_VREDRAW;
    pclass->lpfnWndProc = Window::WindowProc;
    pclass->cbClsExtra = 0;
    pclass->cbWndExtra = 0;
    pclass->hInstance = pApp->GetCurrentInstance();
    pclass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    pclass->hCursor = LoadCursor(NULL, IDC_ARROW);
    pclass->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    pclass->lpszMenuName = NULL;
    pclass->lpszClassName = className;
}

void FrameWindow::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);
}

void FrameWindow::OnNcDestroy(WPARAM wParam, LPARAM lParam)
{
	delete this;
}
