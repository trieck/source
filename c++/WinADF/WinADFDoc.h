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

	void SetEntry(const Entry &e);
	const Entry *GetEntry() const;

	Disk *GetDisk() const;
	Volume *GetVolume() const;

// Implementation
public:
	virtual ~WinADFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DiskPtr m_pDisk;		// ADF disk
	Volume *m_pVolume;		// mounted volume
	Entry *m_pEntry;		// current file entry

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	void chdir(Entry *pEntry);
	afx_msg void OnUpdateDiskInfo(CCmdUI *pCmdUI);
	afx_msg void OnDiskInfo();
};


