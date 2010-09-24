// HexDoc.cpp : implementation file
//

#include "stdafx.h"
#include "winhex.h"
#include "HexDoc.h"
#include "HexView.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HexDoc

IMPLEMENT_DYNCREATE(HexDoc, CDocument)

HexDoc::HexDoc()
{
	m_pdata = NULL;
	m_nsize = 0UL;
}

BOOL HexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

HexDoc::~HexDoc()
{
}

BEGIN_MESSAGE_MAP(HexDoc, CDocument)
	//{{AFX_MSG_MAP(HexDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(IDS_DOCUMENTSIZE, OnUpdateDocumentSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HexDoc diagnostics

#ifdef _DEBUG
void HexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void HexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// HexDoc serialization

void HexDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
		Load(ar);
	else Save(ar);
}

void HexDoc::Load(CArchive & ar)
{
	ASSERT(m_pdata == NULL);
	ASSERT(m_nsize == 0);

	CFile *pFile = ar.GetFile();
	int nlen = (int)pFile->GetLength();

	m_pdata = new BYTE[nlen];
	if (m_pdata == NULL)
		AfxThrowMemoryException();

	try {
		m_nsize = ar.Read(m_pdata, nlen);
	} catch (CFileException *E) {
		delete [] m_pdata;
		m_pdata = NULL;
		m_nsize = 0UL;
		throw E;
	}
}

void HexDoc::Save(CArchive & ar)
{
	ASSERT(m_pdata != NULL);

	try {
		ar.Write(m_pdata, m_nsize);
	} catch (CFileException *E) {
		throw E;
		return;
	}

	SetModifiedFlag(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// HexDoc commands

void HexDoc::DeleteContents()
{
	if (m_pdata != NULL) {
		delete [] m_pdata;
		m_pdata = NULL;
	}

	m_nsize = 0UL;

	CDocument::DeleteContents();
}

void HexDoc::SetData(UINT offset, BYTE data)
{
	ASSERT(offset < m_nsize);
	ASSERT(m_pdata != NULL);

	m_pdata[offset] = data;

	SetModifiedFlag();

	UpdateAllViews(NULL, offset, this);
}

void HexDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	pCmdUI->Enable(IsModified());
}

void HexDoc::OnUpdateDocumentSize(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	CString str;
	str.Format(IDS_DOCUMENTSIZE, Comma(m_nsize));

	pCmdUI->SetText(str);

	CStatusBar* pBar = (CStatusBar*)pCmdUI->m_pOther;
	ASSERT_VALID(pBar);

	UINT id, style;
	int width;

	pBar->GetPaneInfo(1, id, style, width);
	width = GetTextWidth(pBar, str);
	pBar->SetPaneInfo(1, id, style, width);
}

BOOL HexDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	UpdateHexView();

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return TRUE;
}

BOOL HexDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	UpdateHexView();

	return CDocument::OnSaveDocument(lpszPathName);
}

void HexDoc::UpdateHexView()
{
	if (!IsModified())
		return;

	POSITION pos = GetFirstViewPosition();
	if (pos != NULL) {
		HexView * pView = (HexView*)GetNextView(pos);
		if (pView != NULL)
			pView->Update();
	}
}

