#ifndef __wxcdiocanvas__
#define __wxcdiocanvas__

#include "wxcdiotreectrl.h"

class wxcdioCanvas : public wxScrolledWindow {
public:
	wxcdioCanvas(wxView *view, wxFrame *frame, const wxPoint& pos,
	             const wxSize& size, const long style);
	~wxcdioCanvas();

	DECLARE_EVENT_TABLE()

public:
	void rebuildTree(isoimage* doc);

private:
	wxView *m_view;
	wxcdioTreeCtrl *m_treeCtrl;
};

#endif // __wxcdiocanvas__
