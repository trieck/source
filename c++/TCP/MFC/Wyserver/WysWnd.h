/*--------------------------------------
	Module:	WYSWND.H
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/
#ifndef __WYSWND_H__
#define __WYSWND_H__

#include <afxwin.h>

// output colors
#define COLOR_RED		RGB(175, 0, 0)
#define COLOR_BLUE		RGB(0, 0, 175)
#define	COLOR_GREEN		RGB(0, 175, 0)
#define COLOR_YELLOW	RGB(255,255,0)

#define DEFAULT_FONTSIZE	10
#define DEFAULT_WEIGHT		FW_BOLD
#define DEFAULT_FACENAME	"MS Sans Serif"

typedef struct // screen line structure
{
	COLORREF	uColor;
	CString		szText;
}SCREENLINE, *LPSCREENLINE; 

// CFrameWnd derived class
class CWysWnd : public CFrameWnd
{
private:
	HICON		m_hIcon;
	CListBox*	m_pListBox;
	CFont*		m_pFont;
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnAbout();
	afx_msg void OnActiveConn();
	afx_msg void OnPreferences();
	afx_msg void OnFont();
public:
	CWysWnd ();
	CListBox* GetListBox();
	void CreateListBox();
	BOOL CreateListFont(LPLOGFONT lpLogFont = NULL);
	void AddListItem(LPSCREENLINE lpScreenLine);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CWysWnd();
	
	DECLARE_MESSAGE_MAP();
};
#endif // __WYSWND_H__