#pragma once

#include "HexView.h"

// BinaryFileView view

class BinaryFileView : public HexView {
	DECLARE_DYNCREATE(BinaryFileView)

protected:
	BinaryFileView();           // protected constructor used by dynamic creation
	virtual ~BinaryFileView();

public:
	WinADFDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
public:
};

#ifndef _DEBUG
inline WinADFDoc* BinaryFileView::GetDocument() const
{
	return reinterpret_cast<WinADFDoc*>(m_pDocument);
}
#endif	// _DEBUG
