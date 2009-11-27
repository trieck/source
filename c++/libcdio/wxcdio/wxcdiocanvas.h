#ifndef __wxcdiocanvas__
#define __wxcdiocanvas__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "wxcdiodoc.h"

class wxcdioCanvas : public wxScrolledWindow 
{
public:
	wxcdioCanvas(wxFrame *frame, const wxPoint& pos, 
		const wxSize& size, const long style);
	~wxcdioCanvas();
			
    DECLARE_EVENT_TABLE()
	
public:		
	void rebuildTree(isoimage* doc);
	
private:
	wxTreeCtrl* m_treeCtrl;	
	
	enum { CX_IMAGE = 16 };
	enum { CY_IMAGE = 16 };
	
};

#endif // __wxcdiocanvas__
