// DiskPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "DiskPropPage.h"
#include "WinADFDoc.h"
#include "disk.h"

// DiskPropPage dialog
IMPLEMENT_DYNCREATE(DiskPropPage, CPropertyPage)

#ifdef _DEBUG
void DiskPropPage::AssertValid() const
{
	CPropertyPage::AssertValid();
}

void DiskPropPage::Dump(CDumpContext& dc) const
{
	CPropertyPage::Dump(dc);
}
#endif // _DEBUG

DiskPropPage::DiskPropPage()
	: CPropertyPage(DiskPropPage::IDD)
{
}

DiskPropPage::~DiskPropPage()
{
}

void DiskPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DiskPropPage, CPropertyPage)
END_MESSAGE_MAP()


// DiskPropPage message handlers

BOOL DiskPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	WinADFDoc *pDoc = (WinADFDoc*)MDIGetActiveDoc();
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(WinADFDoc)));

	Disk *pDisk = pDoc->GetDisk();

	GetDlgItem(IDC_DISKPATH)->SetWindowText(pDisk->Filename().c_str());

	CString size;
	size.Format("%s KB", comma(pDisk->Size() / 1024).c_str());
	GetDlgItem(IDC_DISKSIZE)->SetWindowText(size);

	CString type;
	switch (pDisk->Type()) {
	case DISKTYPE_FLOPDD:
		type = "Double Density Floppy (880KB ADF)";
		break;
	case DISKTYPE_FLOPHD:
		type = "High Density Floppy (1760KB ADF)";
		break;
	default:	// hardfile
		type = "Hardfile";
		break;
	}

	GetDlgItem(IDC_DISKTYPE)->SetWindowText(type);

	CString fmt;
	fmt.Format("%s", comma(pDisk->Cylinders()).c_str());
	GetDlgItem(IDC_CYLINDERS)->SetWindowText(fmt);

	fmt.Format("%s", comma(pDisk->Heads()).c_str());
	GetDlgItem(IDC_HEADS)->SetWindowText(fmt);

	fmt.Format("%s", comma(pDisk->Sectors()).c_str());
	GetDlgItem(IDC_SECTORS)->SetWindowText(fmt);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
