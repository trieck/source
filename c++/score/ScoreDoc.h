#if !defined(AFX_SCOREDOC_H__D6153891_15D4_11D3_823B_00207812120D__INCLUDED_)
#define AFX_SCOREDOC_H__D6153891_15D4_11D3_823B_00207812120D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreDoc.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// Hints enumeration
typedef enum {
    measureHint = 0x0001,
    noteHint = 0x0002,
	modifierHint = 0x0003
} Hints;

/////////////////////////////////////////////////////////////////////////////
// ScoreDoc document
class ScoreDoc : public CDocument
{
protected:
	ScoreDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ScoreDoc)

// Attributes
public:
    void SelectMeasure (Measure * pMeasure);
    BOOL AddNote(Measure * pMeasure, Note * pNote);
    BOOL RemoveNote(Measure * pMeasure, Note * pNote);
    BOOL ModifyNote(Measure * pMeasure, Note * pNote, const Tool & tool);

// Operations
public:
    inline const Staff * GetStaff() const { return &m_Staff; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScoreDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ScoreDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ScoreDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void DeselectAllMeasures();
    Staff m_Staff; // The staff
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOREDOC_H__D6153891_15D4_11D3_823B_00207812120D__INCLUDED_)
