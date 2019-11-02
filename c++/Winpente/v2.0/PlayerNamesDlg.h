#if !defined(AFX_PLAYERNAMESDLG_H__1C0992A5_959C_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_PLAYERNAMESDLG_H__1C0992A5_959C_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PlayerNamesDlg.h : header file
//
#include "ResDll\resource.h"
#include "PenteDoc.h"
#include "Players.h"

/////////////////////////////////////////////////////////////////////////////
// CPlayerNamesDlg dialog

class CPlayerNamesDlg : public CDialog
{
// Construction
public:
    CPlayerNamesDlg(CWnd* pParent = NULL);   // standard constructor
    CPlayerNamesDlg(CPenteDoc* pDoc, CWnd* pParent = NULL);
    virtual ~CPlayerNamesDlg();
// Dialog Data
    //{{AFX_DATA(CPlayerNamesDlg)
    enum { IDD = IDD_PLAYERNAMES };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPlayerNamesDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    inline CComboBox&	GetPlayerOneNameList()
    {
        return * (CComboBox*) GetDlgItem(IDC_PLAYERONENAME);
    }
    inline CComboBox&	GetPlayerTwoNameList()
    {
        return * (CComboBox*) GetDlgItem(IDC_PLAYERTWONAME);
    }
    inline CButton&		GetTwoPlayerGame()
    {
        return * (CButton*) GetDlgItem(IDC_TWOPLAYERGAME);
    }

    CPenteDoc *		m_pDoc;
    LPTSTR			m_lpszComputerName;
    LPTSTR			m_lpszUserName;

    CPlayers *		m_pPlayers;

    afx_msg VOID OnTwoPlayerGame();

    // Generated message map functions
    //{{AFX_MSG(CPlayerNamesDlg)
    virtual BOOL OnInitDialog();
    virtual VOID OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERNAMESDLG_H__1C0992A5_959C_11D1_B85E_0020781268A5__INCLUDED_)
