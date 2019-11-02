#pragma once
#include "afxcmn.h"

// WaitDlg dialog

class WaitDlg : public CDialog
{
public:
    DECLARE_DYNAMIC(WaitDlg)
    WaitDlg(CWnd* pParent = NULL);   // standard constructor
public:
    virtual ~WaitDlg();

// Dialog Data
    enum { IDD = IDD_WAIT };

    void SetCreateParams(uint32_t size,
                         const CString &path,
                         const CString &label,
                         uint32_t flags,
                         bool boot);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
private:
    CProgressCtrl m_progress;
protected:
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnNcDestroy();
protected:
    virtual void OnCancel();
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
private:
    UINT m_nTimer;
    HANDLE m_hThread;
    static DWORD WINAPI CreateVolume(LPVOID pv);

    enum { EVENT_ID = 0xFFFFFFFF };

    uint32_t m_nSize, m_nFlags;
    CString m_Path, m_Label;
    bool m_Boot;
};
