
// TFingerDoc.cpp : implementation of the CTFingerDoc class
//

#include "stdafx.h"
#include "TFinger.h"
#include "TFingerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTFingerDoc

IMPLEMENT_DYNCREATE(CTFingerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTFingerDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SEGMENT, &CTFingerDoc::OnUpdateImageSegment)
	ON_COMMAND(ID_IMAGE_SEGMENT, &CTFingerDoc::OnImageSegment)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_BINARIZE, &CTFingerDoc::OnUpdateImageBinarize)
	ON_COMMAND(ID_IMAGE_BINARIZE, &CTFingerDoc::OnImageBinarize)
	ON_COMMAND(ID_IMAGE_ERODE, &CTFingerDoc::OnImageErode)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ERODE, &CTFingerDoc::OnUpdateImageErode)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, &CTFingerDoc::OnUpdateFileClose)
	ON_COMMAND(ID_FILE_CLOSE, &CTFingerDoc::OnFileClose)
	ON_COMMAND(ID_IMAGE_DILATE, &CTFingerDoc::OnImageDilate)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DILATE, &CTFingerDoc::OnUpdateImageDilate)
	ON_COMMAND(ID_IMAGE_SKELETONIZE, &CTFingerDoc::OnImageSkeletonize)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SKELETONIZE, &CTFingerDoc::OnUpdateImageSkeletonize)
	ON_COMMAND(ID_IMAGE_EXTRACTMINUTIA, &CTFingerDoc::OnImageExtractMinutia)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_EXTRACTMINUTIA, &CTFingerDoc::OnUpdateImageExtractMinutia)
END_MESSAGE_MAP()

// CTFingerDoc construction/destruction
CTFingerDoc::CTFingerDoc()
 : m_segmented(FALSE), 
 m_binarized(FALSE), 
 m_eroded(FALSE), 
 m_dilated(FALSE),
 m_skeletonized(FALSE),
 m_extracted(FALSE)
{
}

CTFingerDoc::~CTFingerDoc()
{
}

BOOL CTFingerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

CSize CTFingerDoc::GetDocSize() const
{
	CSize size;
	if (m_bitmap.IsNull())
		return CSize(0, 0);

	size.cx = m_bitmap.GetWidth();
	size.cy = m_bitmap.GetHeight();
	
	return size;
}

// CTFingerDoc serialization
void CTFingerDoc::Serialize(CArchive& ar)
{	
}

// CTFingerDoc diagnostics

#ifdef _DEBUG
void CTFingerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTFingerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTFingerDoc commands
BOOL CTFingerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (!m_bitmap.LoadBitmap(lpszPathName)) {
		CString prompt;
		AfxFormatString1(prompt, IDS_CANTLOADBMP, lpszPathName);
		AfxMessageBox(prompt, MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void CTFingerDoc::DeleteContents()
{
	m_bitmap.Destroy();
	m_segmented = m_binarized = m_eroded = 
		m_dilated = m_skeletonized = m_extracted = FALSE;
	m_minutia.clear();

	CDocument::DeleteContents();
}

CImage *CTFingerDoc::GetBitmap()
{
	if (m_bitmap.IsNull())
		return NULL;

	return &m_bitmap;
}

const MinutiaVec *CTFingerDoc::GetMinutia() const
{
	if (m_minutia.size() == 0)
		return NULL;

	return &m_minutia;
}

void CTFingerDoc::OnFileClose()
{
	AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL);
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnUpdateImageSegment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && !m_segmented);
}

void CTFingerDoc::OnImageSegment()
{
	CWaitCursor cursor;
	m_segmenter.Segment(m_bitmap);
	m_segmented = TRUE;
	UpdateAllViews(NULL);
}
void CTFingerDoc::OnUpdateImageBinarize(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && m_segmented && !m_binarized);
}

void CTFingerDoc::OnImageBinarize()
{
	CWaitCursor cursor;
	m_binarizer.Binarize(m_bitmap);
	m_binarized = TRUE;
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnImageErode()
{
	CWaitCursor cursor;
	m_eroder.Erode(m_bitmap);
	m_eroded = TRUE;
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnUpdateImageErode(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && m_binarized && !m_eroded);
}

void CTFingerDoc::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull());
}

void CTFingerDoc::OnImageDilate()
{
	CWaitCursor cursor;
	m_dilater.Dilate(m_bitmap);
	m_dilated = TRUE;
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnUpdateImageDilate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && m_eroded && !m_dilated);
}

void CTFingerDoc::OnImageSkeletonize()
{
	CWaitCursor cursor;
	m_skeletonizer.Skeletonize(m_bitmap);
	m_skeletonized = TRUE;
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnUpdateImageSkeletonize(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && m_dilated && !m_skeletonized);
}


void CTFingerDoc::OnImageExtractMinutia()
{
	CWaitCursor cursor;
	m_minutia = m_extractor.Extract(m_bitmap);
	m_extracted = TRUE;
	UpdateAllViews(NULL);
}

void CTFingerDoc::OnUpdateImageExtractMinutia(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bitmap.IsNull() && m_skeletonized && !m_extracted);
}

