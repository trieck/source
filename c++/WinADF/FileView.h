#pragma once

#include "TextView.h"

// FileView view

class FileView : public TextView
{
    DECLARE_DYNCREATE(FileView)

protected:
    FileView();           // protected constructor used by dynamic creation
    virtual ~FileView();

public:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    WinADFDoc* GetDocument() const;
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
    DECLARE_MESSAGE_MAP()
    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
};

#ifndef _DEBUG  //debug version in WinADFView.cpp
inline WinADFDoc* FileView::GetDocument() const
{
    return reinterpret_cast<WinADFDoc*>(m_pDocument);
}
#endif


