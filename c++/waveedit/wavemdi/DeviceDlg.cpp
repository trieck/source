/*---------------------------------------

	Module	:	DEVICEDLG.CPP
	Purpose	:	Wave Dialog
				Implementations
	Date	:	11/22/1997

---------------------------------------*/

#include "DeviceDlg.h"
#include "WaveApp.h"

IMPLEMENT_DYNCREATE (CDeviceDlg, CDialog)

BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_INPUTDEVICES, OnInputDevices)
    ON_CBN_SELCHANGE(IDC_OUTPUTDEVICES, OnOutputDevices)
    ON_COMMAND(IDC_QUERYINPUT, OnQueryInput)
    ON_COMMAND(IDC_QUERYOUTPUT, OnQueryOutput)
END_MESSAGE_MAP()

CDeviceDlg :: CDeviceDlg(CWnd* pParent) : CDialog (CDeviceDlg::IDD, pParent)
{
}

CDeviceDlg :: ~CDeviceDlg()
{
}

BOOL CDeviceDlg :: OnInitDialog()
{
    // Call the base class handler
    CDialog::OnInitDialog();

    CWaveApp* pWaveApp = (CWaveApp*)AfxGetApp();
    ASSERT(pWaveApp);

    // Set the custom icon
    HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    ::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)hIcon);

    // Build the input and output
    // device lists.
    BuildInputDeviceList();
    BuildOutputDeviceList();

    return TRUE;
}

////////////////////////////////////
//
// BuildInputDeviceList()
//
BOOL CDeviceDlg :: BuildInputDeviceList()
{
    return TRUE;
}

////////////////////////////////////
//
// BuildOutputDeviceList()
//
BOOL CDeviceDlg :: BuildOutputDeviceList()
{
    return TRUE;
}

////////////////////////////////////
//
// OnInputDevices()
//
VOID CDeviceDlg :: OnInputDevices()
{
    if (GetInDeviceList().GetCurSel() != CB_ERR)
        // Enable Query Input Device
        GetQueryInput().EnableWindow(TRUE);
    else
        GetQueryInput().EnableWindow(FALSE);
}

////////////////////////////////////
//
// OnOutputDevices()
//
VOID CDeviceDlg :: OnOutputDevices()
{
    if (GetOutDeviceList().GetCurSel() != CB_ERR)
        // Enable Query Output Device
        GetQueryOutput().EnableWindow(TRUE);
    else
        GetQueryOutput().EnableWindow(FALSE);

}

////////////////////////////////////
//
// OnQueryInput()
//
VOID CDeviceDlg :: OnQueryInput()
{
}

////////////////////////////////////
//
// OnQueryOutput()
//
VOID CDeviceDlg :: OnQueryOutput()
{
}

////////////////////////////////////
//
// BuildFormats()
//
VOID CDeviceDlg :: BuildFormats(DWORD dwFormats)
{
}
