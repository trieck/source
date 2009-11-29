#ifndef __wxcdiotreectrl__
#define __wxcdiotreectrl__

#include "wxcdionode.h"
#include "isoimage.h"

class wxcdioTreeCtrl : public wxTreeCtrl {
public:
	wxcdioTreeCtrl(wxView *view, wxWindow *parent);
	~wxcdioTreeCtrl();

	void OnItemMenu(wxTreeEvent& event);
	void OnItemExpanding(wxTreeEvent &event);
	void OnItemExpanded(wxTreeEvent &event);
	void OnItemCollapsed(wxTreeEvent &event);
	
	void rebuild(isoimage *image);
	
private:
	void buildChildren(isoimage *image, const wxTreeItemId &item);
	wxString GetAbsolutePath(const wxTreeItemId &item);
	
	void ShowMenu(wxcdioNode *item, const wxPoint &pt);
	void OnProperties(wxCommandEvent&);

	enum { CX_IMAGE = 16 };
	enum { CY_IMAGE = 16 };

	enum { MENU_ID_PROPERTIES = 1001 };

	DECLARE_EVENT_TABLE()
	
	wxView *m_view;
};


#endif // __wxcdiotreectrl__
