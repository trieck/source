#include "wxcdiocanvas.h"

BEGIN_EVENT_TABLE(wxcdioCanvas, wxScrolledWindow)
END_EVENT_TABLE()
	
wxcdioCanvas::wxcdioCanvas(wxFrame *frame, const wxPoint& pos, 
	const wxSize& size, const long style) : 
    wxScrolledWindow(frame, wxID_ANY, pos, size, style), m_treeCtrl(NULL)
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);
		
	m_treeCtrl = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	bSizer->Add(m_treeCtrl, 1, wxEXPAND, 5);
	
	SetSizer(bSizer);	
	Layout();
}

wxcdioCanvas::~wxcdioCanvas()
{	
}
