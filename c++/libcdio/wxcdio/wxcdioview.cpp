
#include "main.h"
#include "wxcdioview.h"

IMPLEMENT_DYNAMIC_CLASS(wxcdioView, wxView)

BEGIN_EVENT_TABLE(wxcdioView, wxView)    
END_EVENT_TABLE()

wxcdioView::wxcdioView() : m_canvas(NULL)
{
}

wxcdioView::~wxcdioView()
{
}

bool wxcdioView::OnCreate(wxDocument* doc, long flags)
{
	MainApp &theApp = wxGetApp();
	
	wxcdioFrame *theFrame;
	if ((theFrame = theApp.GetFrame()) == NULL)
		return false;
	
	wxSize size = theFrame->GetClientSize();
	
	m_canvas = new wxcdioCanvas(theFrame, wxPoint(0, 0), size, 0);
		 
	return true;
}

bool wxcdioView::OnClose(bool deleteWindow)
{
	return wxView::OnClose(deleteWindow);
}

void wxcdioView::OnClosingDocument()
{	
	wxView::OnClosingDocument();
}

void wxcdioView::OnDraw(wxDC* pDC)
{
}
