#ifndef __wxcdiocanvas__
#define __wxcdiocanvas__

#include <wx/wx.h>
#include <wx/treectrl.h>

class wxcdioCanvas : public wxScrolledWindow 
{
public:
	wxcdioCanvas(wxFrame *frame, const wxPoint& pos, 
		const wxSize& size, const long style);
	~wxcdioCanvas();
			
    DECLARE_EVENT_TABLE()
		
private:
	wxTreeCtrl* m_treeCtrl;	
};

#endif // __wxcdiocanvas__
