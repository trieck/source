/*---------------------------------------
	Module Name	:	PiecePage.h
	Author		:	Thomas A. Rieck
	Purpose		:	Pieces Preference
					Property Page
	Date		:	08/24/1997
---------------------------------------*/

#ifndef __PIECEPAGE_H__
#define __PIECEPAGE_H__

#include "PenteDoc.h"
#include "ResDll\resource.h"
#include "OurTypes.h"

class CPiecePage : public CPropertyPage
{
    DECLARE_DYNCREATE(CPiecePage);

public:
    CPiecePage();
    ~CPiecePage();

protected:
    virtual BOOL	OnInitDialog();
    virtual void	OnOK();
    virtual BOOL	OnApply();

    VOID	FramePlayerPiece(CWnd*, COLORREF);
    INT		GetPieceOneResFromWnd(CWnd*);
    INT		GetPieceTwoResFromWnd(CWnd*);
    VOID	RedrawPieces();
private:
    enum {IDD = IDD_PIECEPAGE};

    CPenteDoc*	m_pDoc;
    CWnd*		m_pCurrentPlayerOne;
    CWnd*		m_pCurrentPlayerTwo;

    PLAYERPIECE	*m_pPlayerOnePieces;
    PLAYERPIECE	*m_pPlayerTwoPieces;

    afx_msg VOID	OnPaint();
    afx_msg VOID	OnPlayerOnePiece1();
    afx_msg VOID	OnPlayerOnePiece2();
    afx_msg VOID	OnPlayerOnePiece3();
    afx_msg VOID	OnPlayerOnePiece4();
    afx_msg VOID	OnPlayerOnePiece5();
    afx_msg VOID	OnPlayerTwoPiece1();
    afx_msg VOID	OnPlayerTwoPiece2();
    afx_msg VOID	OnPlayerTwoPiece3();
    afx_msg VOID	OnPlayerTwoPiece4();
    afx_msg VOID	OnPlayerTwoPiece5();

    static UINT PlayerOneCtrls[];
    static UINT PlayerTwoCtrls[];
public:
    static	UINT nRes[];
protected:
    DECLARE_MESSAGE_MAP();
};

#endif // __PIECEPAGE_H__