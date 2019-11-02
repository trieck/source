// Dictionary.h: interface for the Dictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__FF42601D_54B3_468D_8F3A_A1C0112047FA__INCLUDED_)
#define AFX_DICTIONARY_H__FF42601D_54B3_468D_8F3A_A1C0112047FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TorrentObject.h"

class Dictionary : public TorrentObject
{
public:
    Dictionary();
    virtual ~Dictionary();
    void Set(LPCSTR k, LPTORRENTOBJECT v);
    LPTORRENTOBJECT Get(LPCSTR k) const;
    LPCSTR GetString(LPCSTR k) const;

    KeyVec GetKeys() const;
    KeyVec GetKeysSorted() const;

    virtual int GetElementType() const
    {
        return ET_DICT;
    }

private:
    CMap<CString, LPCSTR, LPTORRENTOBJECT, LPTORRENTOBJECT> map;
};

typedef Dictionary *LPDICTIONARY;

#endif // !defined(AFX_DICTIONARY_H__FF42601D_54B3_468D_8F3A_A1C0112047FA__INCLUDED_)
