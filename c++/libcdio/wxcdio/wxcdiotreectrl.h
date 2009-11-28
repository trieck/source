#ifndef __wxcdiotreectrl__
#define __wxcdiotreectrl__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "wxcdionode.h"

class wxcdioTreeCtrl : public wxTreeCtrl
{
public:
	wxcdioTreeCtrl(wxWindow *parent);
	~wxcdioTreeCtrl();
	
	DECLARE_EVENT_TABLE()
	
	void OnItemMenu(wxTreeEvent& event);

private:
	void ShowMenu(wxcdioNode *item, const wxPoint &pt);
	void OnProperties(wxCommandEvent&);
	
	enum { CX_IMAGE = 16 };
	enum { CY_IMAGE = 16 };
	
	enum { MENU_ID_PROPERTIES = 1001 };
};


#endif // __wxcdiotreectrl__
