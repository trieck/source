// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "RegisterDlg.h"
#include "6502.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT registers[] = {
	IDC_E_REGA,
	IDC_E_REGX,
	IDC_E_REGY,
	IDC_E_REGPCL,
	IDC_E_REGPCH,
	IDC_E_REGS,
	IDC_E_REGP
};

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg dialog


RegisterDlg::RegisterDlg(CWnd* pParent /*=NULL*/)
{
	Create(RegisterDlg::IDD);

	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pApp->RegisterConstruct(RegisterDlg::IDD, this);

	//{{AFX_DATA_INIT(RegisterDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

RegisterDlg::~RegisterDlg()
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pApp->RegisterDestruct(RegisterDlg::IDD);
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RegisterDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void RegisterDlg::OnCancel()
{
	DestroyWindow();
}

void RegisterDlg::OnOK()
{
}

BEGIN_MESSAGE_MAP(RegisterDlg, CDialog)
	//{{AFX_MSG_MAP(RegisterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegisterDlg message handlers

void RegisterDlg::PostNcDestroy()
{
	delete this;
	CDialog::PostNcDestroy();
}

BOOL RegisterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	textFont.CreatePointFont(110, _T("Courier New"));

	for (int i = 0; i < sizeof(registers) / sizeof(UINT); i++) {
		CEdit *pWnd = (CEdit*)GetDlgItem(registers[i]);
		pWnd->SendMessage(EM_LIMITTEXT, 2, 0);
		pWnd->SetFont(&textFont);
	}

	RefreshRegisters();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL RegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_CHAR) {
		if (!IsHexChar(pMsg->wParam))
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
BOOL RegisterDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	LONG dirty;
	HWND hWnd = (HWND)lParam;

	switch (HIWORD(wParam)) {
	case BN_CLICKED:
		switch (LOWORD(wParam)) {
		case IDC_FLAGN:
		case IDC_FLAGV:
		case IDC_FLAGU:
		case IDC_FLAGB:
		case IDC_FLAGD:
		case IDC_FLAGI:
		case IDC_FLAGZ:
		case IDC_FLAGC:
			UpdateFlags(LOWORD(wParam));
		}
		break;
	case EN_UPDATE:
		SetWindowLong(hWnd, GWL_USERDATA, 1);	// dirty
		break;
	case EN_KILLFOCUS:
		dirty = GetWindowLong(hWnd, GWL_USERDATA);
		if (dirty) {
			UpdateRegister(LOWORD(wParam));
		}
		break;
	}

	return CDialog::OnCommand(wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
void RegisterDlg::UpdateRegister(int id)
{
	CEdit *pWnd = (CEdit*)GetDlgItem(id);

	CString value;
	pWnd->GetWindowText(value);

	int b = 0;
	_stscanf(value, _T("%2hx"), &b);

	CPU *cpu = CPU::instance();

	switch (id) {
	case IDC_E_REGA:
		cpu->SetA(b);
		break;
	case IDC_E_REGX:
		cpu->SetX(b);
		break;
	case IDC_E_REGY:
		cpu->SetY(b);
		break;
	case IDC_E_REGPCL:
		cpu->SetPCL(b);
		break;
	case IDC_E_REGPCH:
		cpu->SetPCH(b);
		break;
	case IDC_E_REGS:
		cpu->SetS(b);
		break;
	case IDC_E_REGP:
		cpu->SetP(b);
		break;
	}

	RefreshRegister(id);
}

/////////////////////////////////////////////////////////////////////////////
void RegisterDlg::RefreshRegisters()
{
	RefreshRegister(IDC_E_REGA);
	RefreshRegister(IDC_E_REGX);
	RefreshRegister(IDC_E_REGY);
	RefreshRegister(IDC_E_REGPCL);
	RefreshRegister(IDC_E_REGPCH);
	RefreshRegister(IDC_E_REGS);
	RefreshRegister(IDC_E_REGP);
}

/////////////////////////////////////////////////////////////////////////////
void RegisterDlg::RefreshRegister(int id)
{
	CPU *cpu = CPU::instance();

	BYTE b = 0;

	switch (id) {
	case IDC_E_REGA:
		b = cpu->GetA();
		break;
	case IDC_E_REGX:
		b = cpu->GetX();
		break;
	case IDC_E_REGY:
		b = cpu->GetY();
		break;
	case IDC_E_REGPCL:
		b = cpu->GetPCL();
		break;
	case IDC_E_REGPCH:
		b = cpu->GetPCH();
		break;
	case IDC_E_REGS:
		b = cpu->GetS();
		break;
	case IDC_E_REGP:
		b = cpu->GetP();
		RefreshFlags();
		break;
	}

	SetRegister(id, b);
}

/////////////////////////////////////////////////////////////////////////////
void RegisterDlg::SetRegister(int id, BYTE b)
{
	CEdit *pWnd = (CEdit*)GetDlgItem(id);
	pWnd->SetWindowText(ByteToHex(b));
	SetWindowLong(pWnd->m_hWnd, GWL_USERDATA, 0);	// not dirty
}

/////////////////////////////////////////////////////////////////////////////
void RegisterDlg::RefreshFlags()
{
	CPU *cpu = CPU::instance();
	BYTE b = cpu->GetP();

	CButton *btn = (CButton*)GetDlgItem(IDC_FLAGN);
	btn->SetCheck(cpu->GetNeg() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGV);
	btn->SetCheck(cpu->GetOverflow() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGU);
	btn->SetCheck(cpu->GetUnused() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGB);
	btn->SetCheck(cpu->GetBreak() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGD);
	btn->SetCheck(cpu->GetDecimal() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGI);
	btn->SetCheck(cpu->GetInterrupt() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGZ);
	btn->SetCheck(cpu->GetZero() ? 1 : 0);

	btn = (CButton*)GetDlgItem(IDC_FLAGC);
	btn->SetCheck(cpu->GetCarry() ? 1 : 0);
}

void RegisterDlg::UpdateFlags(int id)
{
	CPU *cpu = CPU::instance();

	CButton *btn = (CButton*)GetDlgItem(id);

	switch (id) {
	case IDC_FLAGN:
		btn->GetCheck() ? cpu->SetNeg() : cpu->ClearNeg();
		break;
	case IDC_FLAGV:
		btn->GetCheck() ? cpu->SetOverflow() : cpu->ClearOverflow();
		break;
	case IDC_FLAGU:
		btn->GetCheck() ? cpu->SetUnused() : cpu->ClearUnused();
		break;
	case IDC_FLAGB:
		btn->GetCheck() ? cpu->SetBreak() : cpu->ClearBreak();
		break;
	case IDC_FLAGD:
		btn->GetCheck() ? cpu->SetDecimal() : cpu->ClearDecimal();
		break;
	case IDC_FLAGI:
		btn->GetCheck() ? cpu->SetInterrupt() : cpu->ClearInterrupt();
		break;
	case IDC_FLAGZ:
		btn->GetCheck() ? cpu->SetZero() : cpu->ClearZero();
		break;
	case IDC_FLAGC:
		btn->GetCheck() ? cpu->SetCarry() : cpu->ClearCarry();
		break;
	}

	SetRegister(IDC_E_REGP, cpu->GetP());
}


