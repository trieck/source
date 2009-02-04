// WinADFDoc.h : interface of the WinADFDoc class
//

#pragma once

#include "disk.h"

class WinADFDoc : public CDocument
{
protected: // create from serialization only
	WinADFDoc();
	DECLARE_DYNCREATE(WinADFDoc)

// Attributes
public:

// Operations
public:
	EntryList readdir();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR filename);
	virtual void DeleteContents(); // delete doc items etc

// Implementation
public:
	virtual ~WinADFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DiskPtr disk;	
	Volume *volume;	// mounted volume

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	void chdir(Entry *pEntry);
};

