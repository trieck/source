
#include "wxcdiocanvas.h"
#include <cdio/iso9660.h>

BEGIN_EVENT_TABLE(wxcdioCanvas, wxScrolledWindow)
END_EVENT_TABLE()
	
wxcdioCanvas::wxcdioCanvas(wxFrame *frame, const wxPoint& pos, 
	const wxSize& size, const long style) : 
    wxScrolledWindow(frame, wxID_ANY, pos, size, style), m_treeCtrl(NULL)
{
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);
		
	m_treeCtrl = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS);
	
	wxImageList *imageList = new wxImageList(CX_IMAGE, CY_IMAGE, true, 0);
	imageList->Add(wxBitmap(wxT("resources/disk-cd.png"), wxBITMAP_TYPE_PNG));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_CLOSED_FOLDER"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_OPEN_FOLDER"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
	imageList->Add(wxIcon(wxT("WXICON_SMALL_FILE"),  
		wxBITMAP_TYPE_ICO_RESOURCE, CX_IMAGE, CY_IMAGE));
		
	m_treeCtrl->AssignImageList(imageList);	
		
	bSizer->Add(m_treeCtrl, 1, wxEXPAND, 5);
	
	SetSizer(bSizer);	
	Layout();
}

wxcdioCanvas::~wxcdioCanvas()
{	
}

void wxcdioCanvas::rebuildTree(isoimage* image)
{
	m_treeCtrl->DeleteAllItems();
	
	wxTreeItemId root = m_treeCtrl->AddRoot(_T("root"), 0, 0);
	
	wxString filename;
	stat_vector_t stat_vector;
	int nimage;
	char tfilename[4096];
		
	if (image->ReadDir(_T("/"), stat_vector)) {
		stat_vector_t::const_iterator it = stat_vector.begin();
		for ( ; it != stat_vector.end(); it++) {
			ISO9660::Stat *stat = *it;
			iso9660_name_translate(stat->p_stat->filename, tfilename);
			
			if (strcmp(tfilename, ".") != 0 && strcmp(tfilename, "..") != 0) {
				filename = wxString::FromAscii(tfilename);			
				nimage = (iso9660_stat_s::_STAT_DIR == stat->p_stat->type) ?
					1 : 3;			
				m_treeCtrl->AppendItem(root, filename, nimage, nimage);					
			}	
			delete stat;			
		}		
	}
	
	m_treeCtrl->Expand(root);
}

