// String.cpp: implementation of the String class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "String.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

String::String()
{
}

String::String(const String &s)
{
	*this = s;
}

String::String(const CString &s)
{
	data = s;
}

String::String(const char *p, int nlen)
{
	data = CString(p, nlen);
}

String::~String()
{
}

String &String::operator =(const String &s) 
{
	if (this != &s) {
		data = s.data;
	}

	return *this;
}

String::operator LPCSTR() const
{
	return data;
}

String::operator const CString&() const
{
	return data;
}

char String::CharAt(int n) const
{
	return data.GetAt(n);
}