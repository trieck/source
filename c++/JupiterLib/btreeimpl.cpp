/////////////////////////////////////////////////////////////////////////////
//
//	BTREEIMPL.CPP : String based btree implementation
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "BlockMgr.h"
#include "wthread.h"
#include "LazyIO.h"
#include "btree.h"
#include "btreeimpl.h"

/////////////////////////////////////////////////////////////////////////////
BTreeImpl::BTreeImpl()
{
}

/////////////////////////////////////////////////////////////////////////////
BTreeImpl::~BTreeImpl()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
BOOL BTreeImpl::open(LPCSTR filename, OpenMode m)
{
	return btree.open(filename, m);
}

/////////////////////////////////////////////////////////////////////////////
void BTreeImpl::close()
{
	btree.close();
}

/////////////////////////////////////////////////////////////////////////////
string BTreeImpl::search(const string &s)
{
	Item key(s.c_str());
	string val;

	ItemPtr pVal(btree.search(&key));
	if (pVal.get() != NULL) {
		val = string(pVal->data, pVal->nlen);
	}

	return val;
}

/////////////////////////////////////////////////////////////////////////////
void BTreeImpl::insert(const string &key, const string &val)
{
	Entry entry;
	Item keyItem(key.c_str()), valItem(val.c_str());
	entry.key = &keyItem;
	entry.val = &valItem;

	btree.insert(&entry);
}

/////////////////////////////////////////////////////////////////////////////
BOOL BTreeImpl::append(const string &key, const string &val)
{
	Entry entry;
	Item keyItem(key.c_str()), valItem(val.c_str());
	entry.key = &keyItem;
	entry.val = &valItem;

	return btree.append(&entry);
}

/////////////////////////////////////////////////////////////////////////////
void BTreeImpl::writeStats(std::ostream &os) const
{
	btree.writeStats(os);
}