/*------------------------------------------
	Module Name	:	PlayerOptions.h
	Author		:	Thomas A. Rieck
	Purpose		:	Player Options Dialog
					declarations
	Date		:	09/01/1997
------------------------------------------*/

#ifndef __PLAYEROPTIONS_H__
#define __PLAYEROPTIONS_H__

#include "ResDll\resource.h"

class CPlayerOptionsDlg : public CDialog
{
    DECLARE_DYNCREATE(CPlayerOptionsDlg);

public:
    CPlayerOptionsDlg();
    ~CPlayerOptionsDlg();

protected:
    virtual BOOL	OnInitDialog();
    virtual void	OnOK();
private:
    enum {IDD = IDD_PLAYER};

    afx_msg void	OnPaint();

    DECLARE_MESSAGE_MAP();
};

#endif // __PLAYEROPTIONS_H_
