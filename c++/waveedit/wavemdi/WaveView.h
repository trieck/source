//////////////////////////////////////
// Module Name	:	WaveView.h		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave View		//
//					Declarations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#ifndef __WAVEVIEW_H__
#define __WAVEVIEW_H__

#include "stdafx.h"
#include "WaveDoc.h"

/////////////////////////////////////////////////////////////////
// The CWaveView view class

class CWaveView : public CListView {
protected:
	CWaveView();
	DECLARE_DYNCREATE(CWaveView)

	// message map entries
	afx_msg	INT	OnCreate(LPCREATESTRUCT);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Attributes
public:
	CWaveDoc* GetDocument();

// Overrides
public:
	virtual VOID OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
	virtual VOID OnUpdate(CView*, LPARAM, CObject*);
// Implementation
public:
	virtual ~CWaveView();

protected:
	static LPCTSTR	m_lpszHeaders[];

	DECLARE_MESSAGE_MAP()
};

inline CWaveDoc* CWaveView::GetDocument()
{
	return (CWaveDoc*)m_pDocument;
}

///////////////////////////////////////////////////////////////////

#endif	// __WAVEVIEW_H__