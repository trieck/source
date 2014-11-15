/////////////////////////////////////////////////////////////////////////////
//
// BESTRING.CPP : Bencoded string class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "beobject.h"
#include "BEString.h"

/////////////////////////////////////////////////////////////////////////////
String::String(LPBYTE pdata, INT len)
{
    nlen = len;
    data = new BYTE[len + 1];	// for null terminator
    memcpy(data, pdata, len);
    data[len] = '\0';
}

/////////////////////////////////////////////////////////////////////////////
String::String(const String &str)
    : data(NULL), nlen(0)
{
    *this = str;
}

/////////////////////////////////////////////////////////////////////////////
String::~String()
{
    if (data != NULL)
        delete []data;
}

/////////////////////////////////////////////////////////////////////////////
String &String::operator =(const String &rhs)
{
    if (this != &rhs) {
        if (data != NULL)
            delete []data;
        nlen = rhs.nlen;
        data = new BYTE[rhs.nlen + 1];	// for null terminator
        memcpy(data, rhs.data, nlen);
        data[nlen] = '\0';
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////
String::operator string() const
{
    return string((LPSTR)data, nlen);
}

/////////////////////////////////////////////////////////////////////////////
BYTE String::GetAt(int i) const
{
    if (i < 0 || i >= nlen)
        return -1;

    return data[i];
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT String::Copy() const
{
    return new String(*this);
}

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPSTRING MakeString(LPBYTE data, INT nlen)
{
    return new String(data, nlen);
}

/////////////////////////////////////////////////////////////////////////////
LPSTRING MakeString(LPCSTR pstr)
{
    return MakeString((LPBYTE)pstr, strlen(pstr));
}