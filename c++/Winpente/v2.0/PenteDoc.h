/*---------------------------------------
	Module Name	:	PenteDoc.h
	Author		:	Thomas A. Rieck 
	Purpose		:	Pente Document
					declarations
	Date		:	08/21/1997
---------------------------------------*/

#ifndef __PENTEDOC_H__
#define __PENTEDOC_H__

#include "OurTypes.h"

///////////////////////////////////////////////////////////////////
// The CPenteDoc document class
class CPenteDoc : public CDocument
{
protected: 
	DECLARE_SERIAL(CPenteDoc)
public:
	CPenteDoc();
	virtual ~CPenteDoc();

	// Overrides
	virtual	BOOL		OnNewDocument();
	virtual	VOID		DeleteContents();
	virtual	VOID		Serialize(CArchive&);
	virtual	BOOL		CanCloseFrame(CFrameWnd*);

	BOOL	WhichSquare(CPoint&, CPoint*);
	BOOL	MarkPiece(CPoint&);
	VOID	RenderData(CDC* pDC);
	BOOL	GetSquareDims(CPoint&, CRect*);
	VOID	ChangeTurns();
	UINT	CheckCapture(LPPOINT);
	UINT	CheckFiveInARow(CPoint&);
	VOID	SetPlayerOneRes(INT);
	VOID	SetPlayerTwoRes(INT);
	BOOL	IsValidDocument(CString&);
	BOOL	CheckWinByCapture();
	VOID	ComputerMove();

	inline	COLORREF	GetBackColor(){return m_lBackColor;}
	inline	COLORREF	GetGridColor(){return m_lGridColor;}
	inline	VOID		SetBackColor(COLORREF lColor){m_lBackColor = lColor;}
	inline	VOID		SetGridColor(COLORREF lColor){m_lGridColor = lColor;}
	inline	VOID		GetBoard(CRect *pRc){pRc->CopyRect(m_rcBoard);}
	inline	INT			GetPlayerOneRes(){return m_nPlayerOneRes;}
	inline	INT			GetPlayerTwoRes(){return m_nPlayerTwoRes;}
	inline  UINT		GetCurrentTurn(){return m_nCurrentTurn;}
	inline  UINT		GetPlayMode(){return m_nPlayMode;}
	inline	VOID		SetPlayMode(UINT nPlayMode){m_nPlayMode = nPlayMode;}
	inline	VOID		SetPlayerOneName(CString& strPlayerOneName) { m_strPlayerOneName = strPlayerOneName; }
	inline	VOID		SetPlayerTwoName(CString& strPlayerTwoName) { m_strPlayerTwoName = strPlayerTwoName; }
	inline	CString		GetPlayerOne() { return m_strPlayerOneName; }
	inline	CString		GetPlayerTwo() { return m_strPlayerTwoName; }
protected:
	static short	m_nFileMarker;
	UINT			m_nPlayMode;
	CRect			m_rcBoard;
	COLORREF		m_lBackColor;
	COLORREF		m_lGridColor;
	UINT			m_nCurrentTurn;
	UINT			m_nPlayerOneCaptures;
	UINT			m_nPlayerTwoCaptures;
	CString			m_strPlayerOneName;
	CString			m_strPlayerTwoName;
	HICON			m_hPlayerOneIcon;
	HICON			m_hPlayerTwoIcon;
	INT				m_nPlayerOneRes;
	INT				m_nPlayerTwoRes;
	SQUARE			(*m_pSquares)[19];
public:
	BOOL			m_fUseBackColor;
protected:
	VOID			Initialize();
	VOID			SetSquares();
	VOID			AddCapture(UINT);

	BOOL			CopyBoardToDLLFormat(PPVOID);
	BOOL			CopyBoardFromDLLFormat(INT[][19]);

	afx_msg VOID	OnPreferences();
	afx_msg VOID	OnUpdateFileSave(CCmdUI*);
	afx_msg VOID	OnUpdatePlayerOptions(CCmdUI*);
	afx_msg VOID	OnUpdatePlayerTurn(CCmdUI*);
	afx_msg VOID	OnUpdatePlayerOneCaptures(CCmdUI*);
	afx_msg VOID	OnUpdatePlayerTwoCaptures(CCmdUI*);

	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////

#endif	// __PENTEDOC_H__
