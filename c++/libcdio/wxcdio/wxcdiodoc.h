#ifndef __wxcdiodoc__
#define __wxcdiodoc__

#include <wx/docview.h>
#include "isoimage.h"

class wxcdioDoc : public wxDocument {
	DECLARE_DYNAMIC_CLASS(wxcdioDoc)
public:
	wxcdioDoc();
	~wxcdioDoc();
	
	bool OnSaveDocument(const wxString& filename);
    bool OnOpenDocument(const wxString& filename);
    bool OnNewDocument();
    bool OnCloseDocument();
	
private:
	isoimage m_image;	
};
#endif // __wxcdiodoc__
