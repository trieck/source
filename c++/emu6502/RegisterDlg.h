#if !defined(AFX_REGISTERDLG_H__EF408421_6C4C_4871_8B01_6E6BD9E5287C__INCLUDED_)
#define AFX_REGISTERDLG_H__EF408421_6C4C_4871_8B01_6E6BD9E5287C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg dialog

class RegisterDlg : public CDialog {
// Construction
public:
    RegisterDlg(CWnd* pParent = NULL);   // standard constructor
    ~RegisterDlg();

// Dialog Data
    //{{AFX_DATA(RegisterDlg)
    enum { IDD = IDD_REGISTERS };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(RegisterDlg)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void OnCancel();
    virtual void OnOK();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(RegisterDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    void UpdateRegister(int id);
    void RefreshRegisters();
    void RefreshRegister(int id);
    void UpdateFlags(int id);
    void RefreshFlags();
    void SetRegister(int id, BYTE b);
    CFont textFont;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERDLG_H__EF408421_6C4C_4871_8B01_6E6BD9E5287C__INCLUDED_)
