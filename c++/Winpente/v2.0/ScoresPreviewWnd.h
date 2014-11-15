#if !defined(AFX_SCORESPREVIEWWND_H__6C09131A_9B34_11D1_B85F_0020781268A5__INCLUDED_)
#define AFX_SCORESPREVIEWWND_H__6C09131A_9B34_11D1_B85F_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScoresPreviewWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewWnd window

class CScoresPreviewWnd : public CWnd {
// Construction
public:
    CScoresPreviewWnd();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CScoresPreviewWnd)
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CScoresPreviewWnd();

    // Generated message map functions
protected:
    VOID DrawData(CDC* pDC, INT, INT);
    VOID DrawPage(CDC*, INT, INT);
    VOID DrawPreview(CDC*, INT, INT);

    CFont m_Font;

    //{{AFX_MSG(CScoresPreviewWnd)
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORESPREVIEWWND_H__6C09131A_9B34_11D1_B85F_0020781268A5__INCLUDED_)
