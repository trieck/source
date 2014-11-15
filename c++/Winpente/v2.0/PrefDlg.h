/*---------------------------------------
	Module Name	:	PrefDlg.h
	Author		:	Thomas A. Rieck
	Purpose		:	Preferences Dialog
					declarations
	Date		:	08/24/1997
---------------------------------------*/

#ifndef __PREFDLG_H__
#define __PREFDLG_H__

#include "ColorPage.h"
#include "PiecePage.h"
#include "BkgndPage.h"
#include "ResDll\resource.h"

class CPrefDlg : public CPropertySheet {
    friend CBkgndPage;

    // Construction / Destruction
public:
    CPrefDlg(UINT nIDCaption, CWnd* pParentWnd = NULL,
             UINT iSelectPage = 0);
    virtual ~CPrefDlg();
    VOID	Init();
protected:
    VOID	BuildPages();
    virtual BOOL OnInitDialog();
protected:
    CColorPage* m_pColorPage;
    CPiecePage* m_pPiecePage;
    CBkgndPage* m_pBkgndPage;
    HBITMAP		m_hBitmaps[6];		// Used for Background page
    HPALETTE	m_hPalettes[6];
};

#endif // __PREF_DLG_H