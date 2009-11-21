/*---------------------------------------
	Module Name	:	ColorPage.h
	Author		:	Thomas A. Rieck
	Purpose		:	Color Preference
					Property Page
	Date		:	08/24/1997
---------------------------------------*/

#ifndef __COLORPAGE_H__
#define __COLORPAGE_H__

#include "PenteDoc.h"
#include "ResDll\resource.h"

class CColorPage : public CPropertyPage {
	DECLARE_DYNCREATE(CColorPage);

public:
	CColorPage();
	~CColorPage();

	inline COLORREF GetBackColor() {
		return m_lBackColor;
	};
	inline COLORREF GetGridColor() {
		return m_lGridColor;
	};
protected:
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
	virtual void OnOK();

private:
	enum {IDD = IDD_COLORPAGE};
	CPenteDoc*	m_pDoc;
	BOOL		m_fUseBackColor;
private:
	inline CStatic& BackColor() {
		return *(CStatic*) GetDlgItem(IDC_BACKCOLOR);
	};
	inline CStatic& GridColor() {
		return *(CStatic*) GetDlgItem(IDC_GRIDCOLOR);
	};

	afx_msg VOID	OnPaint();
	afx_msg INT		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg VOID	OnUseBkgnd();
	afx_msg VOID	OnUseTheme();
	afx_msg VOID	OnBackColor();
	afx_msg VOID	OnGridColor();
protected:
	COLORREF	m_lBackColor;
	COLORREF	m_lGridColor;

	DECLARE_MESSAGE_MAP();
};

#endif // __COLORPAGE_H__