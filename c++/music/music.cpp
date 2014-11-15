// music.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "music.h"

#include "MainFrm.h"
#include "musicDoc.h"
#include "musicView.h"
#include "AddEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR MusicApp::databasePath = _T("C:\\WINNT\\Profiles\\trieck\\Personal\\music.mdb");

/////////////////////////////////////////////////////////////////////////////
// MusicApp

BEGIN_MESSAGE_MAP(MusicApp, CWinApp)
    //{{AFX_MSG_MAP(MusicApp)
    ON_COMMAND(IDM_ADDRECORD, OnAddRecord)
    ON_COMMAND(IDM_DELRECORD, OnDeleteRecord)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicApp construction

MusicApp::MusicApp()
{
    db = new CDaoDatabase();
}

MusicApp::~MusicApp()
{
    if (db)
        delete db;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only MusicApp object

MusicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// MusicApp initialization

BOOL MusicApp::InitInstance()
{
    if (!AfxOleInit())
        return FALSE;

    // VC++ 6.0 / Access 2000 workaround
    // note: must link with MFC DLL
    AfxGetModuleState()->m_dwVersion = 0x0601;

    try {
        db->Open(databasePath,
                 FALSE, FALSE);
    } catch (CDaoException *E) {
        E->ReportError(MB_OK | MB_ICONEXCLAMATION);
        E->Delete();
        return FALSE;
    }

    // Register document templates
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(MusicDoc),
        RUNTIME_CLASS(MainFrame),       // main SDI frame window
        RUNTIME_CLASS(MusicView));
    AddDocTemplate(pDocTemplate);

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// MusicApp message handlers


int MusicApp::ExitInstance()
{
    if (db->IsOpen())
        db->Close();

    return CWinApp::ExitInstance();
}

void MusicApp::OnAddRecord()
{
    _Record rec;
    AddEditDlg dlg(AddEditDlg::addMode, &rec);
    dlg.DoModal();
}

void MusicApp::OnDeleteRecord()
{
}

// global helper functions
CString LoadString(UINT resource)
{
    CString str;
    str.LoadString(resource);
    return str;
}

BOOL setButtonImage(CWnd *pParent,	/* parent dialog */
                    UINT button,				/* button resource */
                    UINT image,					/* image resource */
                    UINT imageType,				/* image type */
                    UINT cx, UINT cy,			/* image size */
                    UINT flags)					/* load flags */
{
    ASSERT_VALID(pParent);

    CButton *pBtn = (CButton*)pParent->GetDlgItem(button);
    ASSERT_VALID(pBtn);
    if (pBtn == NULL)
        return FALSE;	// no button

    HANDLE hImage = ::LoadImage(AfxGetResourceHandle(),
                                MAKEINTRESOURCE(image),
                                imageType,
                                cx, cy, flags);
    ASSERT(hImage != NULL);
    if (hImage == NULL)
        return FALSE;	// no image

    if (imageType == IMAGE_ICON)
        pBtn->SetIcon((HICON)hImage);
    else if (imageType == IMAGE_BITMAP)
        pBtn->SetBitmap((HBITMAP)hImage);
    else if (imageType == IMAGE_CURSOR)
        pBtn->SetCursor((HCURSOR)hImage);
    else return FALSE;	// image type unknown

    return TRUE;
}
