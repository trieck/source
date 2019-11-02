// String.h: interface for the String class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRING_H__B0BAACE2_E6B3_4936_8619_BB3A7431AF42__INCLUDED_)
#define AFX_STRING_H__B0BAACE2_E6B3_4936_8619_BB3A7431AF42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TorrentObject.h"

class String : public TorrentObject
{
public:
    String();
    String(const String &s);
    String(const CString &s);
    String(const char *p, int nlen);

    virtual ~String();

    String &operator =(const String &s);
    operator LPCSTR() const;
    operator const CString&() const;

    virtual int GetElementType() const
    {
        return ET_STRING;
    }

    int GetLength() const
    {
        return data.GetLength();
    }

    char CharAt(int n) const;
private:
    CString data;
};

typedef String *LPSTRING;

#endif // !defined(AFX_STRING_H__B0BAACE2_E6B3_4936_8619_BB3A7431AF42__INCLUDED_)
