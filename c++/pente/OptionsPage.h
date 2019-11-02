#pragma once


// OptionsPage dialog

class OptionsPage : public CPropertyPage
{
    DECLARE_DYNAMIC(OptionsPage)

public:
    OptionsPage();
    virtual ~OptionsPage();

// Dialog Data
    enum { IDD = IDD_OPTIONS_PAGE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
    int m_TwoPlayerGame;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPlayerVsPlayer();
    afx_msg void OnPlayerVsComputer();
    virtual BOOL OnApply();
};
