// hexview.h : interface of the HexView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HexEdit.h"
#include <afxole.h>

class HexView : public CView
{
protected: // create from serialization only
    HexView();
    DECLARE_DYNCREATE(HexView)

    // Attributes
    HexDoc* GetDocument() const;

    // Operations
    void Update();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(HexView)
    void OnDraw(CDC* pDC) override; // overridden to draw this view
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    void OnInitialUpdate() override;
    void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) override;
protected:
    void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
    DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) override;
    BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) override;

    //}}AFX_VIRTUAL

    // Implementation
public:
    ~HexView() override;
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

protected:
    void Render(CDC* pDC, LPCBYTE pdata, UINT size);
    int FormatLine(UINT line, LPSTR buffer, LPCBYTE pdata, UINT size) const;
    void DrawGridLine(CDC* pDC, int vpos, int xextent);
    BOOL GetCellByPoint(CPoint pt, int& row, int& col) const;
    BOOL NavigateCell(UINT nChar);
    void UpdateCell();
    BOOL PrevCell();
    BOOL NextCell();
    BOOL PrevRow();
    BOOL NextRow();
    void InvalidateCell(BOOL eraseChar = TRUE);
    void RepositionCell();
    void SetSizes();
    void GetCellPos(int& row, int& col) const;
    void SetCellPos(int row, int col);
    void GetCellRect(CRect& rc) const;
    void GetCellByPos(int row, int col, CRect& rc) const;
    void ScrollToCell();

    // Generated message map functions
    //{{AFX_MSG(HexView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnViewGrid();
    afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnFont();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnBackgroundColor();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnDestroy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    CFont m_font;
    CPen m_gridpen;
    CBrush m_bgBrush;
    int m_cyChar;
    int m_cxChar;
    int m_nLinesTotal;
    int m_nXPageSize;
    int m_nYPageSize;
    int m_nDocHeight;
    int m_nDocWidth;
    BOOL m_grid;
    COLORREF m_color; // text color
    HexEdit m_edit;
    UINT m_ActiveCell;
    CPoint m_ScrollPos;
    COleDropTarget m_DropTarget;

    friend class HexEdit;
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in hexview.cpp
inline HexDoc* HexView::GetDocument() const
{
    return dynamic_cast<HexDoc*>(m_pDocument);
}
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXVIEW_H__B1B4E5FE_8F9B_11D3_88CE_000000000000__INCLUDED_)
