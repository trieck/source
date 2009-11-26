#include "wxcdiodoc.h"

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
	return wxDocument::OnOpenDocument(filename);
}

bool wxcdioDoc::OnNewDocument()
{
	return wxDocument::OnNewDocument();
}

bool wxcdioDoc::OnCloseDocument()
{
	return wxDocument::OnCloseDocument();
}

wxOutputStream& wxcdioDoc::SaveObject(wxOutputStream& stream)
{
	return stream;
}

wxInputStream& wxcdioDoc::LoadObject(wxInputStream& stream)
{
	return stream;
}
