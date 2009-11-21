// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IMiscellaneous wrapper class

class IMiscellaneous : public COleDispatchDriver {
public:
	IMiscellaneous() {}		// Calls COleDispatchDriver default constructor
	IMiscellaneous(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMiscellaneous(const IMiscellaneous& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetDate();
	CString GetTime();
	CString GetDateTime();
	long GetDriveSpace(LPCTSTR bstrDrive);
	CString EnumDrives();
};
