
#include "common.h"
#include <wx/file.h>
#include <wx/imaglist.h>
#include "wxcdiotreectrl.h"
#include "wxcdiodoc.h"
#include "guiPropertiesDlg.h"
#include "main.h"

#define CEILING(x, y) ((x+(y-1))/y)

BEGIN_EVENT_TABLE(wxcdioTreeCtrl, wxTreeCtrl)
    EVT_TREE_ITEM_MENU(wxID_ANY, wxcdioTreeCtrl::OnItemMenu)
    EVT_TREE_ITEM_COLLAPSED(wxID_ANY, wxcdioTreeCtrl::OnItemCollapsed)
    EVT_TREE_ITEM_EXPANDED(wxID_ANY, wxcdioTreeCtrl::OnItemExpanded)
    EVT_TREE_ITEM_EXPANDING(wxID_ANY, wxcdioTreeCtrl::OnItemExpanding)
    EVT_MENU(MENU_ID_EXTRACT, wxcdioTreeCtrl::OnExtract)
    EVT_MENU(MENU_ID_PROPERTIES, wxcdioTreeCtrl::OnProperties)
END_EVENT_TABLE()

wxcdioTreeCtrl::wxcdioTreeCtrl(wxView *view, wxWindow *parent)
    : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                 wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_HIDE_ROOT),
      m_view(view)
{
    wxImageList *imageList = new wxImageList(CX_IMAGE, CY_IMAGE, true, 0);

    imageList->Add(wxBitmap( wxT("resources/folder-closed.png"), wxBITMAP_TYPE_ANY));
    imageList->Add(wxBitmap(wxT("resources/folder-open.png"), wxBITMAP_TYPE_ANY));
    imageList->Add(wxBitmap(wxT("resources/file.png"), wxBITMAP_TYPE_ANY));

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
        menu.Append(MENU_ID_EXTRACT, _T("Extract"));
        menu.AppendSeparator();
    }

    menu.Append(MENU_ID_PROPERTIES, _T("Properties"));

    PopupMenu(&menu, pt);
}

void wxcdioTreeCtrl::OnExtract(wxCommandEvent& WXUNUSED(event))
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
    wxFileDialog dlg(theApp.GetFrame(), _T("Extract file"), _T(""), filename, _T("*.*"), wxFD_SAVE);
    if (wxID_OK == dlg.ShowModal()) {
        ExtractEntry(stat, dlg.GetPath());
    }
}

void wxcdioTreeCtrl::ExtractEntry(iso9660_stat_t *stat, const wxString &filename)
{
    wxBusyCursor wait;
    wxcdioDoc *pDoc = (wxcdioDoc*)m_view->GetDocument();
    isoimage *image = pDoc->GetImage();
    wxASSERT(image != NULL);

    wxFile file;
    if (!file.Open(filename, wxFile::write)) {
        wxLogError(_T("unable to open file \"%s\""), filename.c_str());
        return;
    }

    uint32_t nblocks = CEILING(stat->size, ISO_BLOCKSIZE);
    uint32_t blocksize, written, remaining = stat->size;

    char block[ISO_BLOCKSIZE];

    for (uint32_t i = 0; i < nblocks; i++) {
        if (ISO_BLOCKSIZE != image->SeekRead(block, stat->lsn + i)) {
            wxLogError(_T("error reading ISO 9660 file at LSN %lu."),
                       stat->lsn + i);
            return;
        }

        blocksize = min(uint32_t(ISO_BLOCKSIZE), remaining);
        if (blocksize != file.Write(block, blocksize)) {
            wxLogError(_T("error writing file."));
            return;
        }

        remaining -= blocksize;
    }

    file.Flush();
    file.Close();
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