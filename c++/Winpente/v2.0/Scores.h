#if !defined(AFX_SCORES_H__AC1FFC63_9A43_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_SCORES_H__AC1FFC63_9A43_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Scores.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScores window

class CScores : public CObject
{
// Construction
public:
	CScores();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScores)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL	FlushScores();
	BOOL	GetScoreItem(INT nIndex, INT nItem, CString&);
	INT		GetScoreCount();
	BOOL	AddScore(const CString &);
	BOOL	Init();
	virtual ~CScores();

	// Generated message map functions
protected:
	VOID			BuildScoresArray();
protected:
	BOOL UpdateRegistry();
	BOOL			m_fInitialized;
	CStringArray *	m_pScoresArray;

	//{{AFX_MSG(CScores)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORES_H__AC1FFC63_9A43_11D1_B85E_0020781268A5__INCLUDED_)
