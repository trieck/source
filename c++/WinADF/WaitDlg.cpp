// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WaitDlg.h"
#include "Disk.h"

// WaitDlg dialog

struct ThreadParams {
	uint32_t size;
	uint32_t flags;
	char path[MAX_PATH+1];
	char label[MAXNAMELEN+1];
};

IMPLEMENT_DYNAMIC(WaitDlg, CDialog)

WaitDlg::WaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WaitDlg::IDD, pParent), 
	m_nTimer(0), m_bDone(false), m_pThread(NULL),
	m_nSize(0), m_nFlags(0)
{
}

WaitDlg::~WaitDlg()
{
}

void WaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAIT_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(WaitDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// WaitDlg message handlers

BOOL WaitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_nTimer = SetTimer(EVENT_ID, 20, NULL);

	ThreadParams *params = new ThreadParams;
	params->size = m_nSize;
	params->flags = m_nFlags;
	
	uint32_t pathlen = min(MAX_PATH, m_Path.GetLength());
	strncpy(params->path, m_Path, pathlen);
	params->path[pathlen] = '\0';

	uint32_t labellen = min(MAXNAMELEN, m_Label.GetLength());
	strncpy(params->label, m_Label, labellen);
	params->label[labellen] = '\0';

	m_pThread = AfxBeginThread(WaitDlg::CreateVolume, params);

	m_progress.SetBarColor(COLOR_PURPLE);
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void WaitDlg::OnCancel()
{
	CDialog::OnCancel();
}

void WaitDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent != EVENT_ID)
		return;

	if (m_bDone) {
		EndDialog(IDOK);
		return;
	}
}

void WaitDlg::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(m_nTimer);
}

void WaitDlg::SetCreateParams(uint32_t size, const CString &path, 
	const CString &label, uint32_t flags)
{
	m_nSize = size;
	m_nFlags = flags;
	m_Path = path;
	m_Label = label;
}

UINT WaitDlg::CreateVolume(LPVOID pv)
{
	ThreadParams *pParams = (ThreadParams*)pv;
	if (pParams == NULL)
		return -1;

	DiskPtr disk;
	if (pParams->size == FLOPDD_SIZE) {
		try {
			disk = Disk::create(pParams->path, FLOPPY_CYLINDERS, 
				FLOPPY_HEADS, FLOPDD_SECTORS);
			//disk->createVolume(
		} catch (const ADFException &e) {
			AfxMessageBox(e.getDescription().c_str());
		}
	}

	delete pParams;

	return 0;
}