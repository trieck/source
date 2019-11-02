#pragma once

#include "BigScrollView.h"

class MultirowView : public BigScrollView
{
    DECLARE_DYNCREATE(MultirowView)
protected:
    MultirowView();	// protected constructor used by dynamic creation
    virtual ~MultirowView();

public:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
    void SetNumLines(int lines)
    {
        m_nLines = lines;
    }
private:
    void InvalidateHighlightRect(BOOL clear = FALSE);

    int m_Highlight;		// highlighted line
    CPen m_GridPen;			// grid pen
    CPen m_HighlightPen;	// highlight pen
protected:
    int m_nLines;		// number of lines
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


