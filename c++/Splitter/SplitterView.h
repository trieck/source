///////////////////////////////////////
// Module Name	:	SplitterView.h	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#ifndef __SPLITTERVIEW_H__
#define __SPLITTERVIEW_H__

#include "stdafx.h"
#include "SplitterDoc.h"

///////////////////////////////////////////////////////////////////
// The CSplitterView view class
class CSplitterView : public CListView
{
protected:
	CSplitterView();
	DECLARE_DYNCREATE(CSplitterView)

// Attributes
public:
   CSplitterDoc* GetDocument();
   
// Overrides
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
// Implementation
public:
	virtual ~CSplitterView();

protected:
	// message map entries
	afx_msg	INT	OnCreate(LPCREATESTRUCT);
protected:
	static LPCTSTR szHeaders[4];

	DECLARE_MESSAGE_MAP()
};       

inline CSplitterDoc* CSplitterView::GetDocument()
{ 
   return (CSplitterDoc*)m_pDocument; 
}

///////////////////////////////////////////////////////////////////
  
#endif	// __SPLITTERVIEW_H__