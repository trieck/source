// ToolboxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "ToolboxDlg.h"
#include "ScoreDoc.h"
#include "ScoreView.h"
#include "resource.h"
#include "neptune.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Tool array
const static Tool Tools[] = {
	NoteTool, IDC_WHOLENOTE, IDI_WHOLENOTE, IDC_WNOTE, WholeNote,
	NoteTool, IDC_HALFNOTE, IDI_HALFNOTE, IDC_HNOTE, HalfNote,
	NoteTool, IDC_QUARTERNOTE, IDI_QUARTERNOTE, IDC_QNOTE, QuarterNote,
	NoteTool, IDC_EIGTHNOTE, IDI_EIGTHNOTE, IDC_8NOTE, EigthNote,
	NoteTool, IDC_SIXTEENTHNOTE, IDI_SIXTEENTHNOTE, IDC_16NOTE, SixteenthNote,
	NoteTool, IDC_THIRTYSECONDNOTE, IDI_THIRTYSECONDNOTE, IDC_32NOTE, ThirtySecondNote,
	ModifierTool, IDC_FLATTEN, IDI_FLAT, IDC_FLAT, -1,
	ModifierTool, IDC_SHARPEN, IDI_SHARP, IDC_SHARP, 1,
	ModifierTool, IDC_NATURALIZE, IDI_NATURAL, IDC_NATURAL, 0
};

/////////////////////////////////////////////////////////////////////////////
// ToolboxDlg dialog


ToolboxDlg::ToolboxDlg(CWnd * pParent)
	: CDialog(ToolboxDlg::IDD, pParent)
{
	ASSERT_VALID(pParent);

	//{{AFX_DATA_INIT(ToolboxDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//
// Destructor
//
ToolboxDlg::~ToolboxDlg()
{
}

void ToolboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToolboxDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolboxDlg, CDialog)
	//{{AFX_MSG_MAP(ToolboxDlg)
	ON_BN_CLICKED(IDC_QUARTERNOTE, OnQuarterNote)
	ON_BN_CLICKED(IDC_EIGTHNOTE, OnEigthNote)
	ON_BN_CLICKED(IDC_SIXTEENTHNOTE, OnSixteenthNote)
	ON_BN_CLICKED(IDC_THIRTYSECONDNOTE, OnThirtysecondNote)
	ON_BN_CLICKED(IDC_HALFNOTE, OnHalfNote)
	ON_BN_CLICKED(IDC_WHOLENOTE, OnWholeNote)
	ON_BN_CLICKED(IDC_SHARPEN, OnSharpen)
	ON_BN_CLICKED(IDC_FLATTEN, OnFlatten)
	ON_BN_CLICKED(IDC_NATURALIZE, OnNaturalize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolboxDlg message handlers

//
// OnInitDialog
//
BOOL ToolboxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadImages();

	SetActiveButton();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//
// LoadImages
//
void ToolboxDlg::LoadImages()
{
	int Count = sizeof(Tools) / sizeof(Tool);

	// Set the images
	for (int i = 0; i < Count; i++) {
		CButton * pButton = (CButton *)GetDlgItem(Tools[i].button);
		ASSERT_VALID(pButton);
		pButton->SetIcon((HICON)Neptune::LoadImage(Tools[i].icon, IMAGE_ICON));
		::SetWindowLong(*pButton, GWL_USERDATA, (LONG)&Tools[i]);
	}
}

//
// SetActiveButton
//
void ToolboxDlg::SetActiveButton()
{
	int Count = sizeof(Tools) / sizeof(Tool);

	const Tool * pTool = ((ScoreView*)m_pParentWnd)->GetTool();
	ASSERT(pTool != NULL);

	for (int i = 0; i < Count; i++) {
		if (Tools[i].cursor == pTool->cursor) {
			CButton * pButton = (CButton*)GetDlgItem(Tools[i].button);
			ASSERT_VALID(pButton);
			pButton->SetCheck(1);
			break;
		}
	}
}

//
// PostNcDestroy
//
void ToolboxDlg::PostNcDestroy()
{
	ASSERT_VALID(this);
	delete this;

	CDialog::PostNcDestroy();
}

//
// OnCancel
//
void ToolboxDlg::OnCancel()
{
	DestroyWindow();
}

//
// OnWholeNote
//
void ToolboxDlg::OnWholeNote()
{
	SetTool(IDC_WHOLENOTE);
}

//
// OnHalfNote
//
void ToolboxDlg::OnHalfNote()
{
	SetTool(IDC_HALFNOTE);
}

//
// OnQuarterNote
//
void ToolboxDlg::OnQuarterNote()
{
	SetTool(IDC_QUARTERNOTE);
}

//
// OnEigthNote
//
void ToolboxDlg::OnEigthNote()
{
	SetTool(IDC_EIGTHNOTE);
}

//
// OnSixteenthNote
//
void ToolboxDlg::OnSixteenthNote()
{
	SetTool(IDC_SIXTEENTHNOTE);
}

//
// OnThirtySecondNote
//
void ToolboxDlg::OnThirtysecondNote()
{
	SetTool(IDC_THIRTYSECONDNOTE);
}

//
// OnSharpen
//
void ToolboxDlg::OnSharpen()
{
	SetTool(IDC_SHARPEN);
}

//
// OnFlatten
//
void ToolboxDlg::OnFlatten()
{
	SetTool(IDC_FLATTEN);
}

//
// OnNaturalize
//
void ToolboxDlg::OnNaturalize()
{
	SetTool(IDC_NATURALIZE);
}

//
// SetTool
//
void ToolboxDlg::SetTool(UINT nButton)
{
	CButton * pButton = (CButton*)GetDlgItem(nButton);
	ASSERT_VALID(pButton);

	ScoreView * pView = (ScoreView *)m_pParentWnd;
	ASSERT_VALID(pView);

	HICON hIcon = pButton->GetIcon();
	ASSERT(hIcon != NULL);

	Tool * pTool = (Tool *)::GetWindowLong(*pButton, GWL_USERDATA);
	ASSERT(pTool != NULL);

	pView->SetTool(pTool);
}

