#ifndef __wxcdiocanvas__
#define __wxcdiocanvas__

#include <wx/wx.h>
#include "wxcdiodoc.h"
#include "wxcdioTreeCtrl.h"

class wxcdioCanvas : public wxScrolledWindow {
public:
	wxcdioCanvas(wxFrame *frame, const wxPoint& pos,
	             const wxSize& size, const long style);
	~wxcdioCanvas();

	DECLARE_EVENT_TABLE()

public:
	void rebuildTree(isoimage* doc);

private:
	wxcdioTreeCtrl *m_treeCtrl;
};

#endif // __wxcdiocanvas__
