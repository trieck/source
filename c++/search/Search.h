/////////////////////////////////////////////////////////////////////////////
//
// SEARCH.H : Search class
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "btree.h"
#include "query.h"

/////////////////////////////////////////////////////////////////////////////
class Search {
// Construction / Destruction
public:
	Search(LPCSTR filename);
	virtual ~Search();

// Interface
	DocVector search(LPCSTR q);

// Implementation
private:
	void open(LPCSTR filename);
	void close();

	BTree btree;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SEARCH_H__