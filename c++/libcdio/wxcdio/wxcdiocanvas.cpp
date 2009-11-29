
#include "common.h"
#include "wxcdiocanvas.h"
#include "wxcdionode.h"

BEGIN_EVENT_TABLE(wxcdioCanvas, wxScrolledWindow)
END_EVENT_TABLE()

wxcdioCanvas::wxcdioCanvas(wxFrame *frame, const wxPoint& pos,
                           const wxSize& size, const long style) :
		wxScrolledWindow(frame, wxID_ANY, pos, size, style), m_treeCtrl(NULL)
{
	wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

	m_treeCtrl = new wxcdioTreeCtrl(this);

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

	wxString volumeId = image->GetVolumeId();

	wxTreeItemId root = m_treeCtrl->AddRoot(volumeId, 0, 0);

	wxString filename;
	wxCharBuffer buffer;
	char *tfilename;
	stat_vector_t stat_vector;
	int nimage;

	if (image->ReadDir(_T("/"), stat_vector)) {
		stat_vector_t::const_iterator it = stat_vector.begin();
		for ( ; it != stat_vector.end(); it++) {
			ISO9660::Stat *stat = *it;
			buffer = wxCharBuffer(strlen(stat->p_stat->filename));
			tfilename = buffer.data();
			tfilename[0] = '\0';

			iso9660_name_translate_ext(stat->p_stat->filename, tfilename, 1);

			if (strcmp(tfilename, ".") != 0 && strcmp(tfilename, "..") != 0) {
				filename = wxString::FromAscii(tfilename);
				nimage = (iso9660_stat_s::_STAT_DIR == stat->p_stat->type) ?
				         1 : 3;
				m_treeCtrl->AppendItem(root, filename, nimage, nimage, new wxcdioNode(stat));
			} else {
				delete stat;
			}
		}
	}

	m_treeCtrl->Expand(root);
}

