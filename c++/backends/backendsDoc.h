// backendsDoc.h : interface of the BackendsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKENDSDOC_H__1C78AAC6_DD05_4693_A13C_1077258762D3__INCLUDED_)
#define AFX_BACKENDSDOC_H__1C78AAC6_DD05_4693_A13C_1077258762D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef vector<CString> StringVector;

#define MAXPRODUCTS 100

typedef struct {
	unsigned fileCache;						// unused file cache
	unsigned servicePack;					// compiler service pack
	unsigned reposCount;					// repository file count
	unsigned reposSize;						// repository file size
	unsigned rawCount;						// raw input count
	TCHAR osversion[MAX_PATH];				// operating system version
	TCHAR products[MAXPRODUCTS][MAX_PATH];	// product list
	unsigned pcount;						// product count
} Config;

class BackendsDoc : public CDocument
{
protected: // create from serialization only
	BackendsDoc();
	DECLARE_DYNCREATE(BackendsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BackendsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BackendsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	StringVector::const_iterator getMachines() const;
	StringVector::const_iterator getMachinesEnd() const;
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(BackendsDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	StringVector machines;
};

/////////////////////////////////////////////////////////////////////////////
inline StringVector::const_iterator BackendsDoc::getMachines() const {
	return machines.begin(); 
}

/////////////////////////////////////////////////////////////////////////////
inline StringVector::const_iterator BackendsDoc::getMachinesEnd() const {
	return machines.end(); 
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKENDSDOC_H__1C78AAC6_DD05_4693_A13C_1077258762D3__INCLUDED_)
