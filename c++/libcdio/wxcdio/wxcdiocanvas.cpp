
#include "common.h"
#include "wxcdiocanvas.h"
#include "wxcdionode.h"

BEGIN_EVENT_TABLE(wxcdioCanvas, wxScrolledWindow)
END_EVENT_TABLE()

wxcdioCanvas::wxcdioCanvas(wxView *view, wxFrame *frame, const wxPoint& pos,
                           const wxSize& size, const long style) :
		wxScrolledWindow(frame, wxID_ANY, pos, size, style), m_treeCtrl(NULL), 
		m_view(view)
{
	m_treeCtrl = new wxcdioTreeCtrl(view, this);
	
	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);
	bSizer->Add(m_treeCtrl, 1, wxEXPAND, 5);

	SetSizer(bSizer);
	Layout();
}

wxcdioCanvas::~wxcdioCanvas()
{
}

void wxcdioCanvas::rebuildTree(isoimage* image)
{
	m_treeCtrl->rebuild(image);	
}

