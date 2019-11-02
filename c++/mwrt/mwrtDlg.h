// mwrtDlg.h : header file
//

#pragma once

#include "database.h"
#include "logfile.h"
#include "afxwin.h"

// CmwrtDlg dialog
class CmwrtDlg : public CDialog
{
// Construction
public:
    CmwrtDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_MWRT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    CString m_Status;
    afx_msg void OnBnClickedCancel();
private:
    CString m_Detail;
    CButton m_Go;
    Database m_db;
    LogFile m_logfile;
private:
    void process() throw();
    void processFiles(uint32_t id) throw();
    void processRegistry(uint32_t id);

    CString expandString(LPCTSTR input);
    bool removeFile(LPCTSTR filename);
    void removeRegValue(LPCTSTR regKey, uint32_t type, LPCTSTR valName,
                        LPCTSTR value);
    HKEY splitKey(LPCTSTR regKey, CString & path);
};
