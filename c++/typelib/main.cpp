/////////////////////////////////////////////////////////////////////////////
//
//	MAIN.CPP : main entry point
//
//	Copyright (c) 2001, Thomas A. Rieck, All Rights Reserved
//

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
#include <atlbase.h>
#include <comdef.h>
#include <iostream>
#include <strstream>
#include <string>

using namespace std;

bool loadTypeLibrary(LPCTSTR path, ITypeLib **pptypelib) throw (_com_error);
bool describeTypeLibrary(ITypeLibPtr ptypelib) throw (_com_error);
string BSTRtoString(const CComBSTR &bstr);
string streamToString(ostrstream &ss);
string guidToString(const GUID &guid);

/////////////////////////////////////////////////////////////////////////////
int _tmain (int argc, TCHAR *argv[])
{
	if (argc < 2) {
		cerr << "usage: typelib filename" << endl;
		return 1;
	}

	try {
		ITypeLibPtr ptypelib;

		loadTypeLibrary(argv[1], &ptypelib);
		describeTypeLibrary(ptypelib);

	} catch (const _com_error &E) {
		bstr_t desc = E.Description();
		if (desc.length())
			cerr << (LPCTSTR)desc << endl;
		else cerr << E.ErrorMessage() << endl;
		return 1;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
bool loadTypeLibrary(LPCTSTR path, ITypeLib **pptypelib) throw (_com_error)
{
	*pptypelib = NULL;

	USES_CONVERSION;

	HRESULT hr = LoadTypeLib(T2OLE(path), pptypelib);
	if (FAILED(hr))
		throw _com_error(hr);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool describeTypeLibrary(ITypeLibPtr ptypelib) throw (_com_error)
{
	// print documentation for type library
	CComBSTR name, docstring, helpfile;
	DWORD context;

	_com_util::CheckError(ptypelib->GetDocumentation(-1, &name, &docstring,
	                      &context, &helpfile));

	ostrstream ss;
	ss << "Name: " << BSTRtoString(name) << endl;
	ss << "Description: " << BSTRtoString(docstring) << endl;
	ss << "Help File: " << BSTRtoString(helpfile) << endl;
	ss << "Context: "<< context << ends;

	cout << streamToString(ss) << endl;

	// get type library attributes
	TLIBATTR *attribs;
	_com_util::CheckError(ptypelib->GetLibAttr(&attribs));

	cout << "GUID: " << guidToString(attribs->guid) << endl;
	cout << "Version: " << attribs->wMajorVerNum << '.' << attribs->wMinorVerNum << endl;

	// release type library attributes
	ptypelib->ReleaseTLibAttr(attribs);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
string BSTRtoString(const CComBSTR &bstr)
{
	if (BSTR(bstr) == NULL)
		return "";

	USES_CONVERSION;

	return OLE2T(bstr);
}

/////////////////////////////////////////////////////////////////////////////
string streamToString(ostrstream &ss)
{
	LPTSTR pstr = ss.str();

	string output = pstr;

	delete [] pstr;

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string guidToString(const GUID &guid)
{
	LPOLESTR str;
	HRESULT hr = StringFromCLSID(guid, &str);
	if (hr != S_OK)
		return _T("");	// out of memory

	USES_CONVERSION;

	string output = OLE2T(str);

	CoTaskMemFree(str);

	return output;
}

