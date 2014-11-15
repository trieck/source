// DLGWND.H

#include <afxwin.h>
#include <afxcmn.h>
#include <afxext.h>
#include "ColorCombo.h"

#ifndef ID_OPENBTN
#define ID_OPENBTN 7
#define ID_EXITBTN 8
#define ID_REDSLIDER 9
#define ID_GREENSLIDER 10
#define ID_BLUESLIDER 11
#define ID_LISTBOX 12
#define ID_EDIT 13
#define ID_COMBOBOX 14
#define ID_PROGRESSCTRL 15
#endif

// CFrameWnd derived class
class CDlgWin : public CFrameWnd {
private:
    void UpdateClientColor();
    void SetWndFont(CWnd* pWnd, CString szFont, LONG lSize);
    CStdioFile* m_pFile;
    CFont* m_pFont;
    CButton* m_pOpenBtn;
    CButton* m_pExitBtn;
    CSliderCtrl* m_pRedSlider;
    CSliderCtrl* m_pGreenSlider;
    CSliderCtrl* m_pBlueSlider;
    CListBox* m_pListBox;
    CEdit* m_pEdit;
    CColorCombo* m_pComboBox;
    CProgressCtrl* m_pProgressCtrl;
    LOGFONT m_lf;
protected:
    // Message handlers
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnBtnOpenClick();
    afx_msg void OnBtnExitClick();
    afx_msg void OnLBSelChange();
    afx_msg void OnLBDblClick();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
    CDlgWin();
    virtual ~CDlgWin();
    void SetChildFonts(int nFirst, int nLast, CString szFont, long lSize);
    void CreateControls();

    DECLARE_MESSAGE_MAP();
};

