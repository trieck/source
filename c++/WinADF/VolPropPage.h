#pragma once
#include "afxcmn.h"


// VolPropPage dialog

class VolPropPage : public CPropertyPage
{
    DECLARE_DYNCREATE(VolPropPage)

public:
    VolPropPage();
    virtual ~VolPropPage();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Dialog Data
    enum { IDD = IDD_VOL_PROPPAGE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CProgressCtrl m_FullProgress;
};
