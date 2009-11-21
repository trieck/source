/////////////////////////////////////////////////////////////////////////////
//
// SEARCH.CPP : Search class
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "Search.h"
#include "StrStream.h"

/////////////////////////////////////////////////////////////////////////////
Search::Search(LPCSTR filename)
{
	open(filename);
}

/////////////////////////////////////////////////////////////////////////////
Search::~Search()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Search::open(LPCSTR filename)
{
	if (!btree.open(filename, OM_RO))
		throw Exception(lasterror());
}

/////////////////////////////////////////////////////////////////////////////
void Search::close()
{
	btree.close();
}

/////////////////////////////////////////////////////////////////////////////
DocVector Search::search(LPCSTR q)
{
	StrStream *pStream = StrStream::newInstance();
	pStream->Write(q);
	pStream->Reset();

	IPeekableStreamPtr stream;
	stream.Attach(pStream);

	Query query(btree);
	return query.query(stream);
}