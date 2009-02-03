// WinADFDoc.h : interface of the WinADFDoc class
//


#pragma once


class WinADFDoc : public CDocument
{
protected: // create from serialization only
	WinADFDoc();
	DECLARE_DYNCREATE(WinADFDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~WinADFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


