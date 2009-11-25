
#include "main.h"
#include "wxcdioview.h"

IMPLEMENT_DYNAMIC_CLASS(wxcdioView, wxView)

wxcdioView::wxcdioView() : m_canvas(NULL), m_canvasID(0)
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
	m_canvasID = m_canvas->GetId();
	
	return true;
}

bool wxcdioView::OnClose(bool deleteWindow)
{
	if (!GetDocument()->Close())
        return false;
		
	if (deleteWindow && m_canvas != NULL) {
		wxWindow *pCanvas;
		if ((pCanvas = wxWindow::FindWindowById(m_canvasID)) != NULL) {
			pCanvas->Destroy();
			m_canvas = NULL;
		}
	}
	
	return true;
}

void wxcdioView::OnClosingDocument()
{	
	wxView::OnClosingDocument();
}

void wxcdioView::OnDraw(wxDC* pDC)
{
}
