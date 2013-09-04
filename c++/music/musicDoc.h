// musicDoc.h : interface of the MusicDoc class

//

/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_MUSICDOC_H__F7CFDC39_51AB_11D4_89F0_00E098787497__INCLUDED_)

#define AFX_MUSICDOC_H__F7CFDC39_51AB_11D4_89F0_00E098787497__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000





class MusicDoc : public CDocument

{

protected: // create from serialization only

	MusicDoc();

	DECLARE_DYNCREATE(MusicDoc)



// Attributes

public:



// Operations

public:



// Overrides

	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(MusicDoc)

public:

	virtual BOOL OnNewDocument();

	virtual void Serialize(CArchive& ar);

	//}}AFX_VIRTUAL



// Implementation

public:

	virtual ~MusicDoc();

#ifdef _DEBUG

	virtual void AssertValid() const;

	virtual void Dump(CDumpContext& dc) const;

#endif



protected:



// Generated message map functions

protected:

	//{{AFX_MSG(MusicDoc)

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};



/////////////////////////////////////////////////////////////////////////////



//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_MUSICDOC_H__F7CFDC39_51AB_11D4_89F0_00E098787497__INCLUDED_)

