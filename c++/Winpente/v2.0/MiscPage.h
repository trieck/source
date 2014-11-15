/*---------------------------------------------
	Module Name	:	MiscPage.h
	Author		:	Thomas A. Rieck
	Purpose		:	Miscellaneous Preference
					Property Page
	Date		:	01/18/1997
---------------------------------------------*/

#ifndef __MISCPAGE_H__
#define __MISCPAGE_H__

#include "ResDll\resource.h"

class CMiscPage : public CPropertyPage {
    DECLARE_DYNCREATE(CMiscPage);

public:
    CMiscPage();
    ~CMiscPage();

protected:
    virtual BOOL		OnInitDialog();
    virtual void		OnOK();
    virtual BOOL		OnApply();
    inline	CButton&	GetCheckBox() {
        return * (CButton*)GetDlgItem(IDC_DEBUGOPTIONS);
    }

private:
    enum {IDD = IDD_MISCPAGE};

    afx_msg VOID OnPaint();
    afx_msg VOID OnEnableDebug();
    afx_msg VOID OnFlushPlayers();
    afx_msg VOID OnFlushScores();

protected:
    DECLARE_MESSAGE_MAP();
};

#endif // __MISCPAGE_H__