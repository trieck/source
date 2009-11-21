// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "miscobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IMiscellaneous properties

/////////////////////////////////////////////////////////////////////////////
// IMiscellaneous operations

CString IMiscellaneous::GetDate()
{
	CString result;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IMiscellaneous::GetTime()
{
	CString result;
	InvokeHelper(0x60020001, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IMiscellaneous::GetDateTime()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IMiscellaneous::GetDriveSpace(LPCTSTR bstrDrive)
{
	long result;
	static BYTE parms[] =
	    VTS_BSTR;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
	             bstrDrive);
	return result;
}

CString IMiscellaneous::EnumDrives()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}


