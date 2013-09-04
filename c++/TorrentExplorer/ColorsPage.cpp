// ColorsPage.cpp : implementation file
//

#include "stdafx.h"
#include "torrentexplorer.h"
#include "ColorsPage.h"
#include "ColorChooserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorsPage property page

IMPLEMENT_DYNCREATE(ColorsPage, CPropertyPage)

ColorsPage::ColorsPage()
	: CPropertyPage(ColorsPage::IDD), m_ModFlags(0)
{
	//{{AFX_DATA_INIT(ColorsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ColorsPage::~ColorsPage()
{
}

void ColorsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColorsPage)
	DDX_Control(pDX, IDC_HILIGHT_BORDER, m_HilightBorderColor);
	DDX_Control(pDX, IDC_TEXT_COLOR, m_TextColor);
	DDX_Control(pDX, IDC_GRID_COLOR, m_GridColor);
	DDX_Control(pDX, IDC_BKGND_COLOR, m_BkgndColor);
	DDX_Control(pDX, IDC_HILIGHT_COLOR, m_HilightColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorsPage, CPropertyPage)
	//{{AFX_MSG_MAP(ColorsPage)
	ON_BN_CLICKED(IDC_BKGND_COLOR, OnBkgndColor)
	ON_BN_CLICKED(IDC_GRID_COLOR, OnGridColor)
	ON_BN_CLICKED(IDC_TEXT_COLOR, OnTextColor)
	ON_BN_CLICKED(IDC_HILIGHT_COLOR, OnHilightColor)
	ON_BN_CLICKED(IDC_HILIGHT_BORDER, OnHilightBorder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorsPage message handlers

void ColorsPage::OnBkgndColor()
{
	ColorChooserDlg dlg(&m_BkgndColor);
	if (dlg.DoModal() == IDOK) {
		m_BkgndColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= BKGND_COLOR;
		SetModified();
	}
}

void ColorsPage::OnGridColor()
{
	ColorChooserDlg dlg(&m_GridColor);
	if (dlg.DoModal() == IDOK) {
		m_GridColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= GRID_COLOR;
		SetModified();
	}
}

void ColorsPage::OnTextColor()
{
	ColorChooserDlg dlg(&m_TextColor);
	if (dlg.DoModal() == IDOK) {
		m_TextColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= TEXT_COLOR;
		SetModified();
	}
}


void ColorsPage::OnHilightColor()
{
	ColorChooserDlg dlg(&m_HilightColor);
	if (dlg.DoModal() == IDOK) {
		m_HilightColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= HILIGHT_COLOR;
		SetModified();
	}
}

void ColorsPage::OnHilightBorder()
{
	ColorChooserDlg dlg(&m_HilightBorderColor);
	if (dlg.DoModal() == IDOK) {
		m_HilightBorderColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= HILIGHT_BORDER_COLOR;
		SetModified();
	}
}

void ColorsPage::OnOK()
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (m_ModFlags & BKGND_COLOR) {
		pApp->PutSetting("ui_bkgnd_color", m_BkgndColor.GetFillColor());
	}
	if (m_ModFlags & TEXT_COLOR) {
		pApp->PutSetting("ui_text_color", m_TextColor.GetFillColor());
	}
	if (m_ModFlags & GRID_COLOR) {
		pApp->PutSetting("ui_grid_color", m_GridColor.GetFillColor());
	}
	if (m_ModFlags & HILIGHT_COLOR) {
		pApp->PutSetting("ui_hilight_color", m_HilightColor.GetFillColor());
	}
	if (m_ModFlags & HILIGHT_BORDER_COLOR) {
		pApp->PutSetting("ui_hilight_border_color", m_HilightBorderColor.GetFillColor());
	}

	if (m_ModFlags)
		pApp->m_pMainWnd->SendMessage(WM_SETTING_CHANGE);

	m_ModFlags = 0;
}

BOOL ColorsPage::OnApply()
{
	return CPropertyPage::OnApply();
}

BOOL ColorsPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (pApp->IsSetting("ui_bkgnd_color"))
		m_BkgndColor.SetFillColor(pApp->GetIntSetting("ui_bkgnd_color"));
	if (pApp->IsSetting("ui_text_color"))
		m_TextColor.SetFillColor(pApp->GetIntSetting("ui_text_color"));
	if (pApp->IsSetting("ui_grid_color"))
		m_GridColor.SetFillColor(pApp->GetIntSetting("ui_grid_color"));
	if (pApp->IsSetting("ui_hilight_color"))
		m_HilightColor.SetFillColor(pApp->GetIntSetting("ui_hilight_color"));
	if (pApp->IsSetting("ui_hilight_border_color"))
		m_HilightBorderColor.SetFillColor(
		    pApp->GetIntSetting("ui_hilight_border_color"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



