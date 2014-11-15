///////////////////////////////////////
// Module Name	:	RootView.h		 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#ifndef __ROOTVIEW_H__
#define __ROOTVIEW_H__

#include "stdafx.h"
#include "SplitterDoc.h"

///////////////////////////////////////////////////////////////////
// The CRootView view class
class CRootView : public CListView {
protected:
    CRootView();
    DECLARE_DYNCREATE(CRootView)

// Attributes
public:
    CSplitterDoc* GetDocument();

// Overrides
public:
    virtual void OnInitialUpdate();
    virtual BOOL PreCreateWindow(CREATESTRUCT&);
// Implementation
public:
    virtual ~CRootView();

protected:
    // message map entries
    afx_msg	INT	OnCreate(LPCREATESTRUCT);
protected:
    CImageList	m_ImageList;

    static LPCTSTR szHeaders[1];

    DECLARE_MESSAGE_MAP()
};

inline CSplitterDoc* CRootView::GetDocument()
{
    return (CSplitterDoc*)m_pDocument;
}

///////////////////////////////////////////////////////////////////

#endif	// __ROOTVIEW_H__