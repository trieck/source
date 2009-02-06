#pragma once
#include "afxcmn.h"


// EntryPropertyPage dialog

class EntryPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(EntryPropertyPage)

public:
	EntryPropertyPage();
	virtual ~EntryPropertyPage();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Dialog Data
	enum { IDD = IDD_ENTRY_PROPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
