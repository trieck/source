#include "wxcdiodoc.h"
#include "main.h"

IMPLEMENT_DYNAMIC_CLASS(wxcdioDoc, wxDocument)

wxcdioDoc::wxcdioDoc()
{
}

wxcdioDoc::~wxcdioDoc()
{
}

bool wxcdioDoc::OnSaveDocument(const wxString& filename)
{
	return wxDocument::OnSaveDocument(filename);
}

bool wxcdioDoc::OnOpenDocument(const wxString& filename)
{
	if (!wxDocument::OnOpenDocument(filename))
		return false;
		
	if (!m_image.OpenImage(filename)) {
		wxLogError(_T("Unable to open image."));
		return false;		
	}
		
	MainApp &theApp = wxGetApp();
	wxString title;
	title.Printf(_T("%s : %s"), WXCDIO_APP_NAME,
		filename.c_str());
		
	wxFrame *frame = theApp.GetFrame();
	frame->SetTitle(title);
	
	return true;	
}

bool wxcdioDoc::OnNewDocument()
{
	return wxDocument::OnNewDocument();
}

bool wxcdioDoc::OnCloseDocument()
{
	if (!wxDocument::OnCloseDocument())
		return false;
		
	MainApp &theApp = wxGetApp();
	
	wxFrame *frame = theApp.GetFrame();
	frame->SetTitle(WXCDIO_APP_NAME);
	
	return true;
}


