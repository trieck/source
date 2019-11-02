/////////////////////////////////////////////////////////////////////////////
//
// QUERY.H : Query class
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __QUERY_H__
#define __QUERY_H__

#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "btree.h"

typedef vector<UINT64> DocVector;

/////////////////////////////////////////////////////////////////////////////
class Query
{
// Construction / Destruction
public:
    Query(BTree &t);
    virtual ~Query();

// Interface
    DocVector query(IPeekableStream *pStream);

// Implementation
private:
    DocVector expr();
    DocVector lookup(const string &term);
    DocVector conj(const DocVector &left,
                   const DocVector &right, int distance) const;
    int getc();
    int lookahead();

    string term();

    BTree &btree;
    IPeekableStream *m_pStream;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __QUERY_H__