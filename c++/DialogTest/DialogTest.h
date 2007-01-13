// DIALOGTEST.H

#include <afxwin.h>
#include <afxcmn.h>

#define ID_EXEBTN 7
#define ID_EXITBTN 8
#define ID_REDSLIDER 9
#define ID_GREENSLIDER 10
#define ID_BLUESLIDER 11
#define ID_LISTBOX 12

// CWinApp derived class
class CDlgApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

// CFrameWnd derived class
class CDlgWin : public CFrameWnd
{
private:
	void UpdateClientColor();
	void SetWndFont(CWnd* pWnd, CString szFont, LONG lSize);
	CFont* m_pFont;
	CButton* m_pExeBtn;
	CButton* m_pExitBtn;
	CSliderCtrl* m_pRedSlider;
	CSliderCtrl* m_pGreenSlider;
	CSliderCtrl* m_pBlueSlider;
	CListBox* m_pListBox;
	LOGFONT m_lf;
protected:
	// Message handlers
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnExplorerClick();
	afx_msg void OnBtnExitClick();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	CDlgWin();
	~CDlgWin();
	void SetChildFonts(int nFirst, int nLast, CString szFont, long lSize);
	void CreateControls();
	
	DECLARE_MESSAGE_MAP();
};

// Message Map for CDlgWin
BEGIN_MESSAGE_MAP(CDlgWin, CFrameWnd)
    ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EXEBTN, OnBtnExplorerClick)
	ON_COMMAND(ID_EXITBTN, OnBtnExitClick)
END_MESSAGE_MAP()
