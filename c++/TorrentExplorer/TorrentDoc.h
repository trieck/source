// TorrentDoc.h : interface of the TorrentDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTDOC_H__788EE479_4A4B_4451_8499_058539D77A02__INCLUDED_)
#define AFX_TORRENTDOC_H__788EE479_4A4B_4451_8499_058539D77A02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TorrentDoc : public CDocument
{
protected: // create from serialization only
	TorrentDoc();
	DECLARE_DYNCREATE(TorrentDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TorrentDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

	LPDICTIONARY GetTorrent() const { return m_pTorrent; }

// Implementation
public:
	virtual ~TorrentDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(TorrentDoc)
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LPDICTIONARY m_pTorrent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TORRENTDOC_H__788EE479_4A4B_4451_8499_058539D77A02__INCLUDED_)
