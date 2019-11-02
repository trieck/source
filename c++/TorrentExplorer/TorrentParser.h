// TorrentParser.h: interface for the TorrentParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTPARSER_H__D00A29C7_17DD_4D2B_B663_91F8595F7CD6__INCLUDED_)
#define AFX_TORRENTPARSER_H__D00A29C7_17DD_4D2B_B663_91F8595F7CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TorrentParser
{
private:
    TorrentParser();
    virtual ~TorrentParser();

public:
    static LPDICTIONARY Parse(CArchive &ar);
};

#endif // !defined(AFX_TORRENTPARSER_H__D00A29C7_17DD_4D2B_B663_91F8595F7CD6__INCLUDED_)
