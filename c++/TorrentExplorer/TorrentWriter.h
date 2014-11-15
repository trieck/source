// TorrentWriter.h: interface for the TorrentWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTWRITER_H__652C9543_3590_4110_8466_D1C2A61C832A__INCLUDED_)
#define AFX_TORRENTWRITER_H__652C9543_3590_4110_8466_D1C2A61C832A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TorrentWriter {
private:
    TorrentWriter();
    virtual ~TorrentWriter();

public:
    static void Write(LPDICTIONARY torrent, CArchive &ar);
};

#endif // !defined(AFX_TORRENTWRITER_H__652C9543_3590_4110_8466_D1C2A61C832A__INCLUDED_)
