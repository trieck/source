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
    bool boot;
    char path[MAX_PATH+1];
    char label[MAXNAMELEN+1];
};

IMPLEMENT_DYNAMIC(WaitDlg, CDialog)

WaitDlg::WaitDlg(CWnd* pParent /*=NULL*/)
    : CDialog(WaitDlg::IDD, pParent),
      m_nTimer(0), m_hThread(NULL),
      m_nSize(0), m_nFlags(0), m_Boot(false)
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

    m_nTimer = SetTimer(EVENT_ID, 100, NULL);

    ThreadParams *params = new ThreadParams;
    params->size = m_nSize;
    params->flags = m_nFlags;
    params->boot = m_Boot;

    uint32_t pathlen = min(MAX_PATH, m_Path.GetLength());
    strncpy(params->path, m_Path, pathlen);
    params->path[pathlen] = '\0';

    uint32_t labellen = min(MAXNAMELEN, m_Label.GetLength());
    strncpy(params->label, m_Label, labellen);
    params->label[labellen] = '\0';

    m_hThread = CreateThread(NULL, 0, CreateVolume, params, 0, NULL);

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

    if (m_hThread != NULL) {
        DWORD dwRet = WaitForSingleObject(m_hThread, 0);
        if (dwRet == WAIT_OBJECT_0) {
            DWORD dwExitCode;
            BOOL bRes = GetExitCodeThread(m_hThread, &dwExitCode);
            EndDialog(bRes && dwExitCode == 0 ? IDOK : IDCANCEL);
        } else if (dwRet == WAIT_TIMEOUT) {
            m_progress.StepIt();
        }
    }
}

void WaitDlg::OnDestroy()
{
    CDialog::OnDestroy();

    if (m_hThread != NULL)
        CloseHandle(m_hThread);

    KillTimer(m_nTimer);
}

void WaitDlg::SetCreateParams(uint32_t size, const CString &path,
                              const CString &label, uint32_t flags, bool boot)
{
    m_nSize = size;
    m_nFlags = flags;
    m_Path = path;
    m_Label = label;
    m_Boot = boot;
}

DWORD WINAPI WaitDlg::CreateVolume(LPVOID pv)
{
    ThreadParams *pParams = (ThreadParams*)pv;
    CString path = pParams->path;
    CString label = pParams->label;
    uint32_t flags = pParams->flags;
    uint32_t size = pParams->size;
    bool boot = pParams->boot;

    delete pParams;

    DiskPtr disk;
    try {
        Volume *pVol;
        if (size == FLOPDD_SIZE) {
            disk = Disk::create(path, FLOPPY_CYLINDERS,
                                FLOPPY_HEADS, FLOPDD_SECTORS);
            pVol = disk->createFloppy(label, flags);
        } else if (size == FLOPHD_SIZE) {
            disk = Disk::create(path, FLOPPY_CYLINDERS,
                                FLOPPY_HEADS, FLOPHD_SECTORS);
            pVol = disk->createFloppy(label, flags);
        } else {
            disk = Disk::create(path, size, 1, 1);
            pVol = disk->createHardfile(label, flags);
        }

        if (boot && (pVol != NULL)) {	// install boot block
            bootblock_t block;
            if (LoadBootblock(&block)) {
                pVol->installbootblock((uint8_t*)&block);
            }
        }
    } catch (const ADFException &e) {
        AfxMessageBox(e.getDescription().c_str());
        return -1;
    }

    return 0;
}

