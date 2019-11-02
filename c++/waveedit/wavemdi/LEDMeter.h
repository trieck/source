#if !defined(AFX_LEDMETER_H__6D6B9783_6F28_11D1_80C8_00207812120D__INCLUDED_)
#define AFX_LEDMETER_H__6D6B9783_6F28_11D1_80C8_00207812120D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LEDMeter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLEDMeter window

#define COLOR_GREEN		RGB(0, 0xFF, 0)
#define COLOR_YELLOW	RGB(0xFF, 0xFF, 0)
#define COLOR_RED		RGB(0xFF, 0, 0)

class CLEDMeter : public CProgressCtrl
{
// Construction
public:
    CLEDMeter();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLEDMeter)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual UINT StepIt();
    virtual ~CLEDMeter();

    // Generated message map functions
    virtual UINT SetStep(UINT nStep);
    virtual UINT SetPos(UINT nPos);
    virtual UINT OffsetPos(UINT nPos);
    virtual void SetRange(UINT nLower, UINT nUpper);
protected:
    COLORREF m_nBackColor;
    UINT m_nGapSize;
    VOID DrawChunks(CDC* pDC);
    UINT m_nLowerRange;
    UINT m_nUpperRange;
    UINT m_nPosition;
    UINT m_nStep;
    //{{AFX_MSG(CLEDMeter)
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDMETER_H__6D6B9783_6F28_11D1_80C8_00207812120D__INCLUDED_)
