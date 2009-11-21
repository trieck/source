#if !defined(AFX_PLAYERS_H__AC1FFC62_9A43_11D1_B85E_0020781268A5__INCLUDED_)
#define AFX_PLAYERS_H__AC1FFC62_9A43_11D1_B85E_0020781268A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Players.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayers window

class CPlayers : public CObject {
// Construction
public:
	CPlayers();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayers)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL	GetPlayer(INT nIndex, CString&);
	BOOL	AddPlayer(const CString&);
	INT		GetPlayerCount();
	BOOL	FlushPlayers();
	BOOL	Init();
	virtual ~CPlayers();

	// Generated message map functions
protected:
	CStringArray *	m_pPlayersArray;
	BOOL			m_fInitialized;

	VOID BuildPlayersArray();
	BOOL UpdateRegistry();

	//{{AFX_MSG(CPlayers)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERS_H__AC1FFC62_9A43_11D1_B85E_0020781268A5__INCLUDED_)
