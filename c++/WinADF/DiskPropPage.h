#pragma once


// DiskPropPage dialog

class DiskPropPage : public CPropertyPage {
	DECLARE_DYNCREATE(DiskPropPage)

public:
	DiskPropPage();
	virtual ~DiskPropPage();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Dialog Data
	enum { IDD = IDD_DISK_PROPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
