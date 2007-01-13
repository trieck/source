// TorrentWriter.cpp: implementation of the TorrentWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "torrentexplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "TorrentWriter.h"
#include "TorrentMaker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TorrentWriter::TorrentWriter()
{

}

TorrentWriter::~TorrentWriter()
{

}

void TorrentWriter::Write(LPDICTIONARY torrent, CArchive &ar)
{
	TorrentMaker maker(NULL, ar.GetFile());
	maker.Make(torrent);
}
