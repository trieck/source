
// DrumSequencerDoc.cpp : implementation of the CDrumSequencerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrumSequencer.h"
#endif

#include "DrumSequencerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrumSequencerDoc

IMPLEMENT_DYNCREATE(CDrumSequencerDoc, CDocument)

// CDrumSequencerDoc construction/destruction

CDrumSequencerDoc::CDrumSequencerDoc()
{
}

CDrumSequencerDoc::~CDrumSequencerDoc()
{
}

BOOL CDrumSequencerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}

// CDrumSequencerDoc serialization

void CDrumSequencerDoc::Serialize(CArchive& ar)
{
	m_sequence.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDrumSequencerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDrumSequencerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDrumSequencerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrumSequencerDoc diagnostics

#ifdef _DEBUG
void CDrumSequencerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrumSequencerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrumSequencerDoc commands

void CDrumSequencerDoc::ToggleSub(const CPoint& pt)
{
	m_sequence.ToggleSub(pt);
	SetModifiedFlag();
	UpdateAllViews(NULL, MAKELONG(pt.x, pt.y), &m_sequence);
}

void CDrumSequencerDoc::DeleteContents()
{
	m_sequence.Clear();

	CDocument::DeleteContents();
}

