// pentedoc.h : interface of the PenteDoc class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_PENTEDOC_H__84460EDC_8E6D_11D4_9013_00010275679A__INCLUDED_)
#define AFX_PENTEDOC_H__84460EDC_8E6D_11D4_9013_00010275679A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "game.h"

class PenteDoc : public CDocument
{
protected: // create from serialization only
	PenteDoc();
	DECLARE_DYNCREATE(PenteDoc)
// Attributes
public:
	bool addPiece(const CPoint & square);
// Operations
public:
	PenteGame *getGame();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PenteDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PenteDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(PenteDoc)
	afx_msg void OnBoardbkgcolor();
	afx_msg void OnGridColor();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptions(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void onUpdateTurn(CCmdUI *pCmdUI);
	PenteGame game;
};
/////////////////////////////////////////////////////////////////////////////
inline PenteGame* PenteDoc::getGame() {
	return &game;
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_PENTEDOC_H__84460EDC_8E6D_11D4_9013_00010275679A__INCLUDED_)
