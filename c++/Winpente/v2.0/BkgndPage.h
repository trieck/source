/*------------------------------------------
	Module Name	:	BkgndPage.h	
	Author		:	Thomas A. Rieck 
	Purpose		:	Backgrounds Preference
					Property Page
	Date		:	08/30/1997
------------------------------------------*/

#ifndef __BKGNDPAGE_H__
#define __BKGNDPAGE_H__

#include "PenteView.h"
#include "BkgndBitmap.h"
#include "ResDll\resource.h"
#include "resource.h"

class CBkgndPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBkgndPage);
public:
	CBkgndPage();
	~CBkgndPage();
		
	CBkgndBitmap *	m_pCurrentBitmap;
	VOID RedrawBitmaps();

protected:
	// Virtual Overrides
	virtual BOOL	OnInitDialog();
	virtual void	OnOK();
	virtual BOOL	OnApply();

	CBkgndBitmap*	GetBkgndBitmapFromRes(UINT);

	enum {IDD = IDD_BKGNDPAGE};
	
	static const UINT	ctlIDs[];
	static const UINT	resIDs[];
	static const RECT	rcs[];
	
	CPenteView*		m_pView;
	LPCTSTR			m_lpszClassName;

	CBkgndBitmap *	m_pBkgndBitmaps[6];
	
	// Message Handlers
	afx_msg VOID	OnPaletteChanged(CWnd*);
	afx_msg BOOL	OnQueryNewPalette();

	DECLARE_MESSAGE_MAP();
};

#endif // __BKGNDPAGE_H__