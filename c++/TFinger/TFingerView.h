
// TFingerView.h : interface of the CTFingerView class
//

#pragma once

class CTFingerView : public CScrollView {
protected: // create from serialization only
    CTFingerView();
    DECLARE_DYNCREATE(CTFingerView)

// Attributes
public:
    CTFingerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
    virtual ~CTFingerView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
    void DrawMinutia(CDC *pDC, const MinutiaVec *pMinutia);
    CPen m_endingPen;
    CPen m_bifurPen;
    CBrush m_endingBrush;
    CBrush m_bifurBrush;
};

#ifndef _DEBUG  // debug version in TFingerView.cpp
inline CTFingerDoc* CTFingerView::GetDocument() const
{
    return reinterpret_cast<CTFingerDoc*>(m_pDocument);
}
#endif

