
#include "common.h"
#include "wxcdiotreectrl.h"
#include "wxcdiodoc.h"
#include "guiPropertiesDlg.h"
#include "main.h"

BEGIN_EVENT_TABLE(wxcdioTreeCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_MENU(wxID_ANY, wxcdioTreeCtrl::OnItemMenu)
	EVT_TREE_ITEM_EXPANDING(wxID_ANY, wxcdioTreeCtrl::OnItemExpanding)
	EVT_MENU(MENU_ID_PROPERTIES, wxcdioTreeCtrl::OnProperties)
END_EVENT_TABLE()

wxcdioTreeCtrl::wxcdioTreeCtrl(wxView *view, wxWindow *parent)
		: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
		wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_HIDE_ROOT),
		m_view(view)
{
	wxImageList *imageList = new wxImageList(CX_IMAGE, CY_IMAGE, true, 0);
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

	if (item != NULL) {
		ShowMenu(item, clientpt);
	}
}

void wxcdioTreeCtrl::OnItemExpanding(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	if (!itemId.IsOk())
		return;
		
	if (GetChildrenCount(itemId) > 0)
		return;	// alrady expanded
		
	wxcdioNode *item;
	if ((item = (wxcdioNode *)GetItemData(itemId)) == NULL)
		return;
		
	iso9660_stat_t *stat = item->GetStat();
	if (iso9660_stat_s::_STAT_DIR != stat->type)
		return;	// not a directory
		
	wxcdioDoc *pDoc = (wxcdioDoc*)m_view->GetDocument();
	isoimage *image = pDoc->GetImage();
	
	wxASSERT(image != NULL);
	
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

void wxcdioTreeCtrl::rebuild(isoimage *image)
{
	DeleteAllItems();

	wxTreeItemId root = AddRoot(_T(""));
stat_vector_t stat_vector;
	image->ReadDir(_T("/"), stat_vector);
	

	wxString filename;
	wxCharBuffer buffer;
	wxTreeItemId id;
	char *tfilename;
	
	stat_vector_t::const_iterator it = stat_vector.begin();
	for ( ; it != stat_vector.end(); it++) {
		ISO9660::Stat *stat = *it;
		buffer = wxCharBuffer(strlen(stat->p_stat->filename));
		tfilename = buffer.data();
		tfilename[0] = '\0';

		iso9660_name_translate_ext(stat->p_stat->filename, tfilename, 1);

		if (strcmp(tfilename, ".") != 0 && strcmp(tfilename, "..") != 0) {
			filename = wxString::FromAscii(tfilename);
			if (iso9660_stat_s::_STAT_DIR == stat->p_stat->type) {
				id = AppendItem(root, filename, 0, 1, new wxcdioNode(stat));
				SetItemHasChildren(id, true);
			} else {
				id = AppendItem(root, filename, 2, 2, new wxcdioNode(stat));
				SetItemHasChildren(id, false);
			}
		} else {
			delete stat;
		}
	}
}