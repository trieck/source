#ifndef __wxcdioview__
#define __wxcdioview__

#include <wx/docview.h>
#include "wxcdiocanvas.h"

class wxcdioView : public wxView {
	DECLARE_DYNAMIC_CLASS(wxcdioView)
public:
	wxcdioView();
	~wxcdioView();

	void OnDraw(wxDC*);
	bool OnCreate(wxDocument* doc, long flags);
	void OnClosingDocument();
	bool OnClose(bool deleteWindow);
	
    DECLARE_EVENT_TABLE()
	
private:
	wxcdioCanvas *m_canvas;
};

#endif // __wxcdioview__
