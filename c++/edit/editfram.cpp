/////////////////////////////////////////////////////////////////////////////
//
// EDITFRAM.CPP : edit frame
//
// Copyright (c) 1999 Rieck Enterprises
//

#include "common.h"
#include "editfram.h"

EditFrame::EditFrame(LPCSTR caption, int x, int y, int width, int height)
		: FrameWindow(caption, x, y, width, height)
{
	RegisterMessages();
}

EditFrame::~EditFrame()
{
}

void EditFrame::RegisterMessages()
{
	REGISTER_MESSAGE(WM_ERASEBKGND, EditFrame::OnEraseBkgnd)
}

void EditFrame::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 128, 128));

	RECT rc;
	GetClientRect(*this, &rc);
	FillRect((HDC)wParam, &rc, hBrush);

	DeleteObject(hBrush);
}



