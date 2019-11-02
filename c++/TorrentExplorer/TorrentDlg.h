#if !defined(AFX_TORRENTDLG_H__974894A1_FA2D_4F51_8320_7F93032AE653__INCLUDED_)
#define AFX_TORRENTDLG_H__974894A1_FA2D_4F51_8320_7F93032AE653__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TorrentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TorrentDlg dialog

class TorrentDlg : public CDialog, ICallable
{
// Construction
public:
    TorrentDlg(CWnd* pParent = NULL);   // standard constructor
    ~TorrentDlg();

    CFile *GetFile();

// Dialog Data
    //{{AFX_DATA(TorrentDlg)
    enum { IDD = IDD_CREATE };
    CButton	m_Create;
    CComboBox	m_SourceFiles;
    CProgressCtrl	m_Progress;
    CComboBox	m_PieceSize;
    CString	m_Trackers;
    BOOL	m_Private;
    CString	m_Comment;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TorrentDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// ICallable methods
    virtual void Call(DWORD param);

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(TorrentDlg)
    afx_msg void OnBrowse();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    TorrentMaker *m_pMaker;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TORRENTDLG_H__974894A1_FA2D_4F51_8320_7F93032AE653__INCLUDED_)
