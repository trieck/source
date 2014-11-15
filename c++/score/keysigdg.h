#if !defined(AFX_KEYSIGDG_H__19A69123_26A3_11D3_880C_000000000000__INCLUDED_)
#define AFX_KEYSIGDG_H__19A69123_26A3_11D3_880C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// keysigdg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// KeySignatureDlg dialog

class KeySignatureDlg : public CDialog {
// Construction
public:
    KeySignatureDlg(Measure * pMeasure, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(KeySignatureDlg)
    enum { IDD = IDD_KEYSIGNATURE };
    CComboBox	m_KeySignature;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(KeySignatureDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    void SetActiveKeySignature();

    Measure * m_pMeasure;

    // Generated message map functions
    //{{AFX_MSG(KeySignatureDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYSIGDG_H__19A69123_26A3_11D3_880C_000000000000__INCLUDED_)

