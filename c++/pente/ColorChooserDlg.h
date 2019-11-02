#pragma once

#include "ColorChooserWnd.h"

// CColorChooserDlg dialog

class CColorChooserDlg : public CDialog
{
    DECLARE_DYNAMIC(CColorChooserDlg)

public:
    CColorChooserDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CColorChooserDlg();

    COLORREF GetSelectedColor() const;

// Dialog Data
    enum { IDD = IDD_COLOR_CHOOSER };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
private:
    CColorChooserWnd m_ColorsWnd;
public:
    virtual BOOL OnInitDialog();
};
