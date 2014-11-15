/*---------------------------------------

	Module	:	DEVICEDLG.H
	Purpose	:	Wave Dialog Declarations
	Date	:	11/22/1997

---------------------------------------*/

#ifndef __DEVICEDLG_H__
#define __DEVICEDLG_H__

#include "stdafx.h"
#include "resource.h"

class CDeviceDlg : public CDialog {
    DECLARE_DYNCREATE (CDeviceDlg)

// Construction
public:
    CDeviceDlg(CWnd* pParent = NULL);
    virtual ~CDeviceDlg();

protected:
    // Overrides
    virtual BOOL OnInitDialog();

    inline CComboBox& GetInDeviceList() {
        return * (CComboBox*)GetDlgItem(IDC_INPUTDEVICES);
    }
    inline CComboBox& GetOutDeviceList() {
        return * (CComboBox*)GetDlgItem(IDC_OUTPUTDEVICES);
    }

    inline CButton& GetQueryInput() {
        return * (CButton*)GetDlgItem(IDC_QUERYINPUT);
    }
    inline CButton& GetQueryOutput() {
        return * (CButton*)GetDlgItem(IDC_QUERYOUTPUT);
    }

    inline CComboBox& GetFormatBox() {
        return * (CComboBox*)GetDlgItem(IDC_FORMATS);
    }

    BOOL BuildInputDeviceList();
    BOOL BuildOutputDeviceList();

    VOID BuildFormats(DWORD);

    afx_msg VOID OnInputDevices();
    afx_msg VOID OnOutputDevices();
    afx_msg VOID OnQueryInput();
    afx_msg VOID OnQueryOutput();
protected:
    enum {IDD = IDD_DEVICEINFO};

    DECLARE_MESSAGE_MAP()
};

#endif // __DEVICEDLG_H__