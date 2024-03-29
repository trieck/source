/////////////////////////////////////////////////////////////////////////////
//
//	DBDLG.C : database dialog
//

#include "common.h"
#include "winapp.h"
#include "dbdlg.h"
#include "resource.h"

static INT_PTR CALLBACK DbDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam,
                                     LPARAM lParam);

static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
static BOOL onInit(HWND hwnd, HWND hwndFocus, LPARAM lParam);
static void onCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
static void onOK(HWND hWnd);
static void onCancel(HWND hWnd);

DbInfo dbinfo;

/////////////////////////////////////////////////////////////////////////////
// TODO: fix: cannot hook dialog successfully
DbDialog * createDbDialog(void)
{
    DbDialog *pdlg;
    HGLOBAL hDialogTemplate;
    HRSRC hResource;
    LPCDLGTEMPLATE lpDialogTemplate;

    // load resource
    hResource = FindResource(App->hInstance, MAKEINTRESOURCE(IDD_DATABASE), RT_DIALOG);
    if (hResource == NULL)
        return NULL;

    hDialogTemplate = LoadResource(App->hInstance, hResource);
    lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);

    pdlg = (DbDialog*)malloc(sizeof(DbDialog));
    if (pdlg == NULL) {
        UnlockResource(hDialogTemplate);
        FreeResource(hResource);
        return NULL;
    }

    pdlg->parent = App->hWndMain;
    pdlg->proc = DbDialogProc;

    pdlg->hWnd = CreateDialogIndirect(App->hInstance,
                                      lpDialogTemplate,
                                      pdlg->parent,
                                      pdlg->proc);

    if (pdlg->hWnd == NULL) { // creation failure
        deleteDbDialog(pdlg);
        UnlockResource(hDialogTemplate);
        FreeResource(hResource);
        return NULL;
    }

    UnlockResource(hDialogTemplate);
    FreeResource(hResource);

    return pdlg;
}

/////////////////////////////////////////////////////////////////////////////
BOOL DbDialogDisplay(const DbDialog *pdlg)
{
    if (pdlg == NULL || !IsWindow(pdlg->hWnd))
        return FALSE;

    ShowWindow(pdlg->hWnd, SW_SHOW);
    UpdateWindow(pdlg->hWnd);

    // Enter modal loop
    enterModalLoop(pdlg->hWnd);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void deleteDbDialog(DbDialog * pdlg)
{
    free(pdlg);
}

/////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK DbDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                              LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG:
        return HANDLE_WM_INITDIALOG(hWnd, wParam, lParam, onInit);
    case WM_COMMAND:
        return HANDLE_WM_COMMAND(hWnd, wParam, lParam, onCommand);
    default:
        break;
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL onInit(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
    SetDlgItemText(hWnd, IDC_SERVER, dbinfo.server);
    SetDlgItemText(hWnd, IDC_UID, dbinfo.uid);
    SetDlgItemText(hWnd, IDC_PWD, dbinfo.pwd);

    return centerWindow(hWnd, App->hWndMain);
}

/////////////////////////////////////////////////////////////////////////////
void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case IDOK:
        onOK(hWnd);
        break;
    case IDCANCEL:
        onCancel(hWnd);
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
void onOK(HWND hWnd)
{
    GetDlgItemText(hWnd, IDC_SERVER, dbinfo.server, _MAX_FNAME);
    GetDlgItemText(hWnd, IDC_UID, dbinfo.uid, _MAX_FNAME);
    GetDlgItemText(hWnd, IDC_PWD, dbinfo.pwd, _MAX_FNAME);

    endModalLoop(hWnd);
    EndDialog(hWnd, IDOK);
}

/////////////////////////////////////////////////////////////////////////////
void onCancel(HWND hWnd)
{
    endModalLoop(hWnd);
    EndDialog(hWnd, IDCANCEL);
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code == HCBT_CREATEWND) {
        CBT_CREATEWND *pcwnd = (CBT_CREATEWND *)lParam;
        HWND hWnd = (HWND)wParam;
    }

    return 0;
}