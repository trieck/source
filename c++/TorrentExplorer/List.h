// List.h: interface for the List class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__2D23CE16_8491_4A9E_91C7_93C67A2626DA__INCLUDED_)
#define AFX_LIST_H__2D23CE16_8491_4A9E_91C7_93C67A2626DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TorrentObject.h"

class List : public TorrentObject
{
public:
    List();
    virtual ~List();

    void append(LPTORRENTOBJECT t);
    UINT size() const;
    LPTORRENTOBJECT GetAt(UINT n) const;
    virtual int GetElementType() const
    {
        return ET_LIST;
    }

private:
    CList<LPTORRENTOBJECT, LPTORRENTOBJECT> list;
};

typedef List *LPLIST;

#endif // !defined(AFX_LIST_H__2D23CE16_8491_4A9E_91C7_93C67A2626DA__INCLUDED_)
