#pragma once
#pragma warning(disable:4996)	// disable deprecation warnings
#pragma warning(disable:4244)	// disable loss of data warning
#pragma warning(disable:4267)	// disable loss of data warning

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <atlbase.h>

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <algorithm>
#include <sstream>

using std::vector;
using std::map;
using std::set;
using std::string;
using std::wstring;
using std::cerr;
using std::cout;
using std::wcout;
using std::wcerr;
using std::endl;
using std::ostream;
using std::ostringstream;
using std::auto_ptr;

typedef vector<string> stringvec;

// case insensitive string comparison
//
struct stringless : std::binary_function <string, string, bool> {
    bool operator () (const string & _X, const string & _Y) const {
        return (stricmp(_X.c_str(), _Y.c_str()) > 0);
    }
};

typedef map<string, string, stringless> stringmap;

/////////////////////////////////////////////////////////////////////////////
// IRunnable interface
DECLARE_INTERFACE(IRunnable) {
public:
	virtual DWORD Execute(LPVOID) PURE;
};

/////////////////////////////////////////////////////////////////////////////
// IPeekableStream interface
DECLARE_INTERFACE_(IPeekableStream, ISequentialStream) {
public:
	virtual HRESULT STDMETHODCALLTYPE Peek(void *pv, ULONG cb,
		ULONG *pcbRead) PURE;
};

typedef CComPtr<IPeekableStream> IPeekableStreamPtr;

/////////////////////////////////////////////////////////////////////////////
// ICallable interface
template <typename T>
DECLARE_INTERFACE(ICallable) {
public:
	virtual void Call(T*) PURE;
};

/////////////////////////////////////////////////////////////////////////////
// file open modes
enum OpenMode { OM_CREATE, OM_RW, OM_RO };

#include "exception.h"
#include "util.h"
