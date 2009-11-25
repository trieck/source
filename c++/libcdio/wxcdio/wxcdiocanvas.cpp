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
	
	wxImageList *imageList = new wxImageList(16, 16, true, 0);
	imageList->Add(wxIcon(wxT("WXICON_SMALL_CLOSED_FOLDER"),  
		wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
	
	m_treeCtrl->AssignImageList(imageList);	
	m_treeCtrl->AddRoot(_T("root"), 0, 0);
	
	bSizer->Add(m_treeCtrl, 1, wxEXPAND, 5);
	
	SetSizer(bSizer);	
	Layout();
}

wxcdioCanvas::~wxcdioCanvas()
{	
}
