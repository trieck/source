// EntryPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "EntryPropertyPage.h"
#include "EntryPropertySheet.h"

uint32_t access[][3] = {
	{ ACCMASK_R, IDC_CHK_READ, 1 },
	{ ACCMASK_W, IDC_CHK_WRITE, 1 },
	{ ACCMASK_E, IDC_CHK_EXEC, 1 },
	{ ACCMASK_D, IDC_CHK_DELETE, 1 },

	{ ACCMASK_A, IDC_CHK_ARCH, 0 },
	{ ACCMASK_P, IDC_CHK_PURE, 0 },
	{ ACCMASK_S, IDC_CHK_SCRIPT, 0 },
	{ ACCMASK_H, IDC_CHK_HOLD, 0 }
};

// EntryPropertyPage dialog

IMPLEMENT_DYNCREATE(EntryPropertyPage, CPropertyPage)

#ifdef _DEBUG
void EntryPropertyPage::AssertValid() const
{
	CPropertyPage::AssertValid();
}

void EntryPropertyPage::Dump(CDumpContext& dc) const
{
	CPropertyPage::Dump(dc);
}
#endif // _DEBUG

EntryPropertyPage::EntryPropertyPage()
		: CPropertyPage(EntryPropertyPage::IDD)
{

}

EntryPropertyPage::~EntryPropertyPage()
{
}

void EntryPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(EntryPropertyPage, CPropertyPage)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int EntryPropertyPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	EntryPropertySheet *pSheet = (EntryPropertySheet*)GetParent();
	ASSERT_VALID(pSheet);

	if (pSheet->GetEntry() == NULL)
		return -1;

	return 0;
}

BOOL EntryPropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	EntryPropertySheet *pSheet = (EntryPropertySheet*)GetParent();
	ASSERT_VALID(pSheet);

	Entry *pEntry = pSheet->GetEntry();

	uint32_t nbits = sizeof(access) / (sizeof(uint32_t) * 3);
	uint32_t state;

	CButton *pButton;
	for (uint32_t i = 0; i < nbits; i++) {
		state = pEntry->access & access[i][0];
		state = access[i][2] == 0 ? state : !state;

		pButton = (CButton*)GetDlgItem(access[i][1]);
		ASSERT(pButton != NULL);
		pButton->SetCheck(state ? BST_CHECKED : BST_UNCHECKED);
	}

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_FILENAME);
	pEdit->SetWindowText(pEntry->name.c_str());

	pEdit = (CEdit*)GetDlgItem(IDC_COMMENT);
	pEdit->SetWindowText(pEntry->comment.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
