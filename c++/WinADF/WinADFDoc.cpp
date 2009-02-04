// WinADFDoc.cpp : implementation of the WinADFDoc class
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WinADFDoc

IMPLEMENT_DYNCREATE(WinADFDoc, CDocument)

BEGIN_MESSAGE_MAP(WinADFDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &WinADFDoc::OnUpdateFileSave)
END_MESSAGE_MAP()


// WinADFDoc construction/destruction

WinADFDoc::WinADFDoc() : volume(NULL)
{
}

WinADFDoc::~WinADFDoc()
{
}

BOOL WinADFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


BOOL WinADFDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
#ifdef _DEBUG
	if (IsModified())
		TRACE(traceAppMsg, 0, "Warning: OnOpenDocument replaces an unsaved document.\n");
#endif
	ENSURE(lpszPathName);
	
	DeleteContents();
	
	try {
		CWaitCursor wait;
		disk = Disk::open(lpszPathName);		
		volume = disk->mount();
	} catch (const ADFException &e) {
		DeleteContents();   // remove failed contents
		AfxMessageBox(e.getDescription().c_str());
		AfxThrowUserException();
		return FALSE;
	}

	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void WinADFDoc::DeleteContents()
{
	if (disk.get() != NULL) {
		Disk *pDisk = disk.release();
		delete pDisk;
	}

	volume = NULL;
}

/////////////////////////////////////////////////////////////////////////////
EntryList WinADFDoc::readdir()
{
	if (volume == NULL)
		return EntryList();

	EntryList entries = volume->readdir(volume->getCurrentDir(), false);

	return entries;
}

// WinADFDoc diagnostics

#ifdef _DEBUG
void WinADFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void WinADFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// WinADFDoc commands

void WinADFDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bModified);
}
