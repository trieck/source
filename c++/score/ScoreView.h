// ScoreView.h : interface of the ScoreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOREVIEW_H__1FC3C62A_FDCF_11D2_822C_00207812120D__INCLUDED_)
#define AFX_SCOREVIEW_H__1FC3C62A_FDCF_11D2_822C_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ScoreView window

class ScoreView : public CScrollView
{
// Construction
protected:
	ScoreView();

// Attributes
public:
public:
	ScoreDoc* GetDocument();

// Operations
public:
	void SetTool(Tool * pTool);
	inline const Tool * GetTool() const {		return &m_Tool;	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScoreView)
public:
	virtual void OnInitialUpdate();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ScoreView();

	// Generated message map functions
protected:
	//{{AFX_MSG(ScoreView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdatePlayMeasure(CCmdUI* pCmdUI);
	afx_msg void OnPlayMeasure();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMode(UINT);
	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);
	afx_msg void OnPlayAll();
	afx_msg void OnUpdatePlayAll(CCmdUI* pCmdUI);
	afx_msg void OnSetMeasureTempo();
	afx_msg void OnUpdateSetMeasureTempo(CCmdUI* pCmdUI);
	afx_msg void OnToolbox();
	afx_msg void OnKeySignature();
	afx_msg void OnUpdateKeySignature(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(ScoreView)

	void InvalidateNote(const Note *);
	void DPtoLP(CPoint &);
	BOOL AddNote(Measure *, const CPoint &);
	BOOL ModifyNote(Note *);

	Note * m_pLastNote;             // The last note played
	Tool m_Tool;                    // The current tool
	Note * m_pSelectedNote;         // The currently selected note
	Measure * m_pSelectedMeasure;   // The currently selected measure
	CPoint m_ptPrev;                // Previously selected point
	UINT m_nMode;                   // Selection mode
};

#ifndef _DEBUG  // debug version in Compound ScoreView.cpp
inline ScoreDoc* ScoreView::GetDocument()
{	return (ScoreDoc*)m_pDocument;}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOREVIEW_H__1FC3C62A_FDCF_11D2_822C_00207812120D__INCLUDED_)

