#if !defined(AFX_COLORBUTTON_H__0180A76A_417C_44F9_8553_CEC30FD60803__INCLUDED_)
#define AFX_COLORBUTTON_H__0180A76A_417C_44F9_8553_CEC30FD60803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColorButton window

class ColorButton : public CButton {
// Construction
public:
	ColorButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetFillColor() const;
	void SetFillColor(COLORREF clr);
	BOOL IsSet() const {
		return m_Set;
	}
	virtual ~ColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(ColorButton)
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_Hilight, m_GrayText, m_Text, m_Fill;
	CBrush m_BkgndBrush;
	BOOL m_Set;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__0180A76A_417C_44F9_8553_CEC30FD60803__INCLUDED_)
