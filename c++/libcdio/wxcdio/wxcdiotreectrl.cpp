
#include "common.h"
#include "wxcdiotreectrl.h"
#include "wxcdiodoc.h"
#include "guiPropertiesDlg.h"
#include "main.h"

BEGIN_EVENT_TABLE(wxcdioTreeCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_MENU(wxID_ANY, wxcdioTreeCtrl::OnItemMenu)
	EVT_TREE_ITEM_COLLAPSED(wxID_ANY, wxcdioTreeCtrl::OnItemCollapsed)
	EVT_TREE_ITEM_EXPANDED(wxID_ANY, wxcdioTreeCtrl::OnItemExpanded)
	EVT_TREE_ITEM_EXPANDING(wxID_ANY, wxcdioTreeCtrl::OnItemExpanding)
	EVT_MENU(MENU_ID_EXPORT, wxcdioTreeCtrl::OnExport)
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

void wxcdioTreeCtrl::OnItemCollapsed(wxTreeEvent &event)
{
	wxTreeItemId itemId = event.GetItem();
	if (!itemId.IsOk())
		return;
		
	SetItemImage(itemId, 0);
}

void wxcdioTreeCtrl::OnItemExpanded(wxTreeEvent &event)
{
	wxTreeItemId itemId = event.GetItem();
	if (!itemId.IsOk())
		return;
		
	SetItemImage(itemId, 1);
}

void wxcdioTreeCtrl::OnItemExpanding(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	if (!itemId.IsOk())
		return;
		
	if (GetChildrenCount(itemId) > 0)
		return;	// already built
		
	wxcdioNode *item;
	if ((item = (wxcdioNode *)GetItemData(itemId)) == NULL)
		return;
		
	iso9660_stat_t *stat = item->GetStat();
	if (iso9660_stat_s::_STAT_DIR != stat->type)
		return;	// not a directory
		
	wxcdioDoc *pDoc = (wxcdioDoc*)m_view->GetDocument();
	isoimage *image = pDoc->GetImage();
	
	wxASSERT(image != NULL);
			
	buildChildren(image, itemId);
}

void wxcdioTreeCtrl::ShowMenu(wxcdioNode *item, const wxPoint &pt)
{
	iso9660_stat_t *stat;
	if ((stat = item->GetStat()) == NULL)
		return;	// no stat
		
	wxMenu menu;	
	if (iso9660_stat_s::_STAT_DIR != stat->type) {
		menu.Append(MENU_ID_EXPORT, _T("Export"));
		menu.AppendSeparator();
	}
	
	menu.Append(MENU_ID_PROPERTIES, _T("Properties"));

	PopupMenu(&menu, pt);
}

void wxcdioTreeCtrl::OnExport(wxCommandEvent& WXUNUSED(event))
{
	MainApp &theApp = wxGetApp();

	wxTreeItemId id = GetSelection();
	if (!id.IsOk())
		return;
	
	wxcdioNode *item;
	if ((item = (wxcdioNode *)GetItemData(id)) == NULL)
		return;	// no node
	
	iso9660_stat_t *stat;
	if ((stat = item->GetStat()) == NULL)
		return;	// no stat
	
	wxString filename = GetItemText(id);
	wxFileDialog dlg(theApp.GetFrame(), _T("Export file"), _T(""), filename, _T("*.*"), wxFD_SAVE);
	if (wxID_OK == dlg.ShowModal()) {
		ExportEntry(stat, dlg.GetPath());
	}
}

void wxcdioTreeCtrl::ExportEntry(iso9660_stat_t *stat, const wxString &filename) 
{
	wxcdioDoc *pDoc = (wxcdioDoc*)m_view->GetDocument();
	isoimage *image = pDoc->GetImage();
	wxASSERT(image != NULL);	
	
/*
 * if (!(p_outfd = fopen (psz_fname, "wb")))
    {
      perror ("fopen()");
      free(p_statbuf);
      iso9660_close(p_iso);
      return 3;
    }

  //Copy the blocks from the ISO-9660 filesystem to the local filesystem.
  {
    const unsigned int i_blocks = CEILING(p_statbuf->size, ISO_BLOCKSIZE);
    for (i = 0; i < i_blocks ; i++) 
    {
      char buf[ISO_BLOCKSIZE];
      const lsn_t lsn = p_statbuf->lsn + i;

      memset (buf, 0, ISO_BLOCKSIZE);
      
      if ( ISO_BLOCKSIZE != iso9660_iso_seek_read (p_iso, buf, lsn, 1) )
      {
	fprintf(stderr, "Error reading ISO 9660 file %s at LSN %lu\n",
		psz_fname, (long unsigned int) lsn);
	my_exit(4);
      }
      
      fwrite (buf, ISO_BLOCKSIZE, 1, p_outfd);
      
      if (ferror (p_outfd))
	{
	  perror ("fwrite()");
	  my_exit(5);
	}
    }
  }
  
  fflush (p_outfd);

  //Make sure the file size has the exact same byte size. Without the
  //   truncate below, the file will a multiple of ISO_BLOCKSIZE.
  //
  if (ftruncate (fileno (p_outfd), p_statbuf->size))
    perror ("ftruncate()");

  printf("Extraction of file '%s' from %s successful.\n", 
	 psz_fname, psz_image);
*/
}

void wxcdioTreeCtrl::OnProperties(wxCommandEvent& WXUNUSED(event))
{
	MainApp &theApp = wxGetApp();

	wxTreeItemId id = GetSelection();
	if (!id.IsOk())
		return;
	
	wxcdioNode *item;
	if ((item = (wxcdioNode *)GetItemData(id)) == NULL)
		return;	// no node
	
	iso9660_stat_t *stat;
	if ((stat = item->GetStat()) == NULL)
		return;	// no stat
	
	wxString name = GetItemText(id);
	
	guiPropertiesDlg dlg(theApp.GetFrame(), stat);	
	dlg.SetTitle(name);	
	dlg.ShowModal();
}

void wxcdioTreeCtrl::rebuild(isoimage *image)
{
	DeleteAllItems();

	wxTreeItemId root = AddRoot(_T("/"));
	
	buildChildren(image, root);	
}

void wxcdioTreeCtrl::buildChildren(isoimage *image, const wxTreeItemId &item)
{
	stat_vector_t stat_vector;
	
	wxString path = GetAbsolutePath(item);
	
	if (!(image->ReadDir(path, stat_vector)))
		return;
	
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

		iso9660_name_translate(stat->p_stat->filename, tfilename);

		if (strcmp(tfilename, ".") != 0 && strcmp(tfilename, "..") != 0) {
			filename = wxString::FromAscii(tfilename);
			
			if (iso9660_stat_s::_STAT_DIR == stat->p_stat->type) {
				id = AppendItem(item, filename, 0, 0, new wxcdioNode(stat));
				SetItemHasChildren(id, true);
			} else {
				id = AppendItem(item, filename, 2, 2, new wxcdioNode(stat));
				SetItemHasChildren(id, false);
			}
		} else {
			delete stat;
		}
	}
}

wxString wxcdioTreeCtrl::GetAbsolutePath(const wxTreeItemId &item) const
{
	if (item == GetRootItem()) {	// virtual root
		return _T("/");
	}
	
	wxString path = GetItemText(item);
	
	wxTreeItemId next = item, parent;	
	
	for (;;) {
		parent = GetItemParent(next);
		if (!parent.IsOk())
			break;
			
		if (parent == GetRootItem()) {	// virtual root
			path = _T("/") + path;
			break;
		}
		
		path = GetItemText(parent) + _T("/") + path;
		
		next = parent;
	}
		
	return path;
}