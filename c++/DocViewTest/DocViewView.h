//////////////////////////////////////
// Module Name	:	DocViewView.h	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#ifndef __DOCVIEWVIEW_H__
#define __DOCVIEWVIEW_H__

#include "stdafx.h"
#include "DocViewDoc.h"

///////////////////////////////////////////////////////////////////
// The CDocViewView view class

class CDocViewView : public CView {
protected:
	CDocViewView();
	DECLARE_DYNCREATE(CDocViewView)

// Attributes
public:
	CDocViewDoc* GetDocument();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
// Implementation
public:
	virtual ~CDocViewView();

protected:
	// message map entries
	afx_msg	INT	OnCreate(LPCREATESTRUCT);

	DECLARE_MESSAGE_MAP()
};

inline CDocViewDoc* CDocViewView::GetDocument()
{
	return (CDocViewDoc*)m_pDocument;
}

///////////////////////////////////////////////////////////////////

#endif	// __DOCVIEWVIEW_H__