/////////////////////////////////////////////////////////////////////////////
//
// EDITFRAM.H : frame window
//
// Copyright (c) 1999 Rieck Enterprises
//

#ifndef __EDITFRAM_H__
#define __EDITFRAM_H__

/////////////////////////////////////////////////////////////////////////////
class EditFrame : public FrameWindow {
// Construction / Destruction
public:
	EditFrame(LPCSTR caption = "", int x = CW_USEDEFAULT,
	          int y = CW_USEDEFAULT,
	          int width = CW_USEDEFAULT,
	          int height = CW_USEDEFAULT);
	~EditFrame();

// Interface

// Implementation
protected:
	void RegisterMessages();
	void OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
};
/////////////////////////////////////////////////////////////////////////////

#endif // __EDITFRAM_H__