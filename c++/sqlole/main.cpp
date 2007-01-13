
#define WIN32_LEAN_AND_MEAN
#define DBINITCONSTANTS

#include <comdef.h>
#include <OleDb.h>
#include <SqlOleDb.h>
#include <iostream>

using namespace std;

struct _oleinit {
	_oleinit() { CoInitialize(NULL); }
	~_oleinit() { CoUninitialize(); }
} oleinit;

int main(int argc, wchar_t *argv[])
{
	int retcode = 0;

	_COM_SMARTPTR_TYPEDEF(IDBInitialize, __uuidof(IDBInitialize));
	_COM_SMARTPTR_TYPEDEF(IDBProperties, __uuidof(IDBProperties));
	
	IDBInitializePtr init;
	DBPROP props[4];

	VariantInit(&props[0].vValue);
	VariantInit(&props[1].vValue);
	VariantInit(&props[2].vValue);
	VariantInit(&props[3].vValue);

	// Server
	props[0].dwPropertyID  = DBPROP_INIT_DATASOURCE;
	props[0].vValue.vt     = VT_BSTR;
	props[0].vValue.bstrVal= SysAllocString(L"KXTRIECK");
	props[0].dwOptions     = DBPROPOPTIONS_REQUIRED;
	props[0].colid         = DB_NULLID;
	
	// Database
	props[1].dwPropertyID  = DBPROP_INIT_CATALOG;
	props[1].vValue.vt     = VT_BSTR;
	props[1].vValue.bstrVal= SysAllocString(L"Survey");
	props[1].dwOptions     = DBPROPOPTIONS_REQUIRED;
	props[1].colid         = DB_NULLID;
	
	// Username
	props[2].dwPropertyID  = DBPROP_AUTH_USERID; 
	props[2].vValue.vt     = VT_BSTR;
	props[2].vValue.bstrVal= SysAllocString(L"trieck");
	props[2].dwOptions     = DBPROPOPTIONS_REQUIRED;
	props[2].colid         = DB_NULLID;
	
	// Password
	props[3].dwPropertyID  = DBPROP_AUTH_PASSWORD;
	props[3].vValue.vt     = VT_BSTR;
	props[3].vValue.bstrVal= SysAllocString(L"erskine1");
	props[3].dwOptions     = DBPROPOPTIONS_REQUIRED;
	props[3].colid         = DB_NULLID;

	DBPROPSET propset;
	propset.guidPropertySet = DBPROPSET_DBINIT;	
    propset.cProperties = 4;
    propset.rgProperties = props;

	try {
		HRESULT hr = init.CreateInstance(CLSID_SQLOLEDB);
		if (FAILED(hr))
			throw _com_error(hr);
		
		IDBPropertiesPtr dbprops = init;
		if (dbprops == NULL)
			throw _com_error(E_NOINTERFACE);

		hr = dbprops->SetProperties(1, &propset); 
		if (FAILED(hr))
			throw _com_error(hr);

		dbprops.Release();

		// establish the connection to the data source
		hr = init->Initialize();
		if (FAILED(hr))
			throw _com_error(hr);

	}catch (_com_error & E) {
		bstr_t desc = E.Description();
		if (desc.length() == 0)
			desc = E.ErrorMessage();
		cerr << (LPCTSTR)desc << endl;

		retcode = 1;
	}

	VariantClear(&props[0].vValue);
	VariantClear(&props[1].vValue);
	VariantClear(&props[2].vValue);
	VariantClear(&props[3].vValue);

	return retcode;
}