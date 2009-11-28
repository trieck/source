
#include "wxcdiotreectrl.h"
#include "guiPropertiesDlg.h"
#include "main.h"

BEGIN_EVENT_TABLE(wxcdioTreeCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_MENU(wxID_ANY, wxcdioTreeCtrl::OnItemMenu)
	EVT_MENU(MENU_ID_PROPERTIES, wxcdioTreeCtrl::OnProperties)
END_EVENT_TABLE()

wxcdioTreeCtrl::wxcdioTreeCtrl(wxWindow *parent) 
 : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS)
{
	wxImageList *imageList = new wxImageList(CX_IMAGE, CY_IMAGE, true, 0);
	imageList->Add(wxBitmap(wxT("resources/disk-cd.png"), wxBITMAP_TYPE_PNG));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_CLOSED_FOLDER"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_OPEN_FOLDER"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_FILE"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
		
	AssignImageList(imageList);	
}

wxcdioTreeCtrl::~wxcdioTreeCtrl()
{
}

void wxcdioTreeCtrl::OnItemMenu(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
    wxcdioNode *item = itemId.IsOk() ? (wxcdioNode *)GetItemData(itemId)
                                         : NULL;
    wxPoint clientpt = event.GetPoint();

    ShowMenu(item, clientpt);
}

void wxcdioTreeCtrl::ShowMenu(wxcdioNode *item, const wxPoint &pt)
{
    wxMenu menu;
    menu.Append(MENU_ID_PROPERTIES, _T("Properties"));

    PopupMenu(&menu, pt);	
}

void wxcdioTreeCtrl::OnProperties(wxCommandEvent& WXUNUSED(event))
{
	MainApp &theApp = wxGetApp();
	
	guiPropertiesDlg dlg(theApp.GetFrame());
    dlg.ShowModal();
}
