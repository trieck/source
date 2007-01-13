/////////////////////////////////////////////////////////////////////////////
//
//	INDEX.H : Generate index
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __INDEX_H__
#define __INDEX_H__

#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "btree.h"
#include "lexer.h"
#include "NoiseList.h"

/////////////////////////////////////////////////////////////////////////////
class Index
{
// Construction / Destruction
public:
	Index();
	virtual ~Index();

// Interface
	void index(LPCSTR filename);
	void writeStats(ostream &os) const;

// Implementation
private:
	void close();
	void index();
	void insert(const Token &tok);

	IPeekableStreamPtr stream;	// input stream
	BTree btree;				// enhanced b-tree
	NoiseList noise;			// noise word list
};
/////////////////////////////////////////////////////////////////////////////

#endif // __INDEX_H__

