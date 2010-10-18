
// TFingerDoc.h : interface of the CTFingerDoc class
//

#pragma once

#include "GreyscaleBitmap.h"
#include "ImageSegmenter.h"
#include "ImageBinarizer.h"
#include "ImageEroder.h"
#include "ImageDilater.h"
#include "ImageSkeletonizer.h"
#include "MinutiaExtractor.h"

class CTFingerDoc : public CDocument
{
protected: // create from serialization only
	CTFingerDoc();
	DECLARE_DYNCREATE(CTFingerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTFingerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CImage *GetBitmap();
	const MinutiaVec *GetMinutia() const;
	CSize GetDocSize() const;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	GreyscaleBitmap m_bitmap;
	ImageSegmenter m_segmenter;			
	ImageBinarizer m_binarizer;
	ImageEroder m_eroder;
	ImageDilater m_dilater;
	ImageSkeletonizer m_skeletonizer;
	MinutiaExtractor m_extractor;
	MinutiaVec m_minutia;

	BOOL m_segmented;		// image has been segmented
	BOOL m_binarized;		// image has been binarized
	BOOL m_eroded;			// image has been eroded
	BOOL m_dilated;			// image has been dilated
	BOOL m_skeletonized;	// image has been skeletonized
	BOOL m_extracted;		// minutia has been extracted

public:
	afx_msg void OnUpdateImageSegment(CCmdUI *pCmdUI);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	afx_msg void OnImageSegment();
	afx_msg void OnUpdateImageBinarize(CCmdUI *pCmdUI);
	afx_msg void OnImageBinarize();
	afx_msg void OnImageErode();
	afx_msg void OnFileClose();
	afx_msg void OnUpdateImageErode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnImageDilate();
	afx_msg void OnUpdateImageDilate(CCmdUI *pCmdUI);
	afx_msg void OnImageSkeletonize();
	afx_msg void OnUpdateImageSkeletonize(CCmdUI *pCmdUI);
	afx_msg void OnImageExtractMinutia();
	afx_msg void OnUpdateImageExtractMinutia(CCmdUI *pCmdUI);
};


