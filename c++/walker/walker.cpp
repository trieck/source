/////////////////////////////////////////////////////////////////////////////
//
// WALKER.CPP : B-tree walker
//
// Copyright (c) 2006 Thomas. A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "btree.h"
#include "walker.h"

/////////////////////////////////////////////////////////////////////////////
Walker::Walker()
{
}

/////////////////////////////////////////////////////////////////////////////
Walker::~Walker()
{
}

/////////////////////////////////////////////////////////////////////////////
void Walker::walk(LPCSTR filename)
{
	if (!btree.open(filename, OM_RO))
		throw Exception(lasterror());

	btree.Walk(this);
}

/////////////////////////////////////////////////////////////////////////////
void Walker::Call(PITEM pKey)
{
	string key = string(pKey->data, pKey->nlen);
	cout << key << endl;
}