/////////////////////////////////////////////////////////////////////////////

//

// FRAMEWND.H : frame window class

//

// Copyright (c) 1999 Rieck Enterprises

//



#ifndef __FRAMEWND_H__

#define __FRAMEWND_H__



/////////////////////////////////////////////////////////////////////////////

class FrameWindow : public Window

{

// Construction / Destruction

public:

	FrameWindow(LPCSTR caption = "", int x = CW_USEDEFAULT,

	            int y = CW_USEDEFAULT,

	            int width = CW_USEDEFAULT,

	            int height = CW_USEDEFAULT);

	virtual ~FrameWindow();



// Interface



// Implementation

protected:

	BOOL Create(LPCSTR caption, int x, int y, int width, int height);

	virtual void InitClass(LPWNDCLASS) const;

	virtual void OnDestroy(WPARAM, LPARAM);

	virtual void OnNcDestroy(WPARAM, LPARAM);

	virtual void RegisterMessages();

private:

};

/////////////////////////////////////////////////////////////////////////////



#endif // __FRAMEWND_H__