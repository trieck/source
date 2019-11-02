#pragma once

#include "MultirowView.h"

// MemoryView view
class MemoryView : public MultirowView
{
    DECLARE_DYNCREATE(MemoryView)

protected:
    MemoryView();           // protected constructor used by dynamic creation
    virtual ~MemoryView();

public:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnInitialUpdate();     // first time after construct

    DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
    void DrawMemory(CDC *pDC);
    CString GetLine(USHORT base);
    CFont m_Font;					// font
};


