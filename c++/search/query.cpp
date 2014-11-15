/////////////////////////////////////////////////////////////////////////////
//
// QUERY.CPP : Query class
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "StdAfx.h"
#include "query.h"

/////////////////////////////////////////////////////////////////////////////
Query::Query(BTree &t)
    : btree(t), m_pStream(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
Query::~Query()
{
    if (m_pStream != NULL)
        m_pStream->Release();
}

/////////////////////////////////////////////////////////////////////////////
DocVector Query::query(IPeekableStream *pStream)
{
    m_pStream = pStream;
    m_pStream->AddRef();
    return expr();
}

/////////////////////////////////////////////////////////////////////////////
DocVector Query::expr()
{
    DocVector output;
    string t;

    for (int i = 0; lookahead() != EOF; i++) {
        t = term();
        if (output.size() > 0)
            output = conj(output, lookup(t), i);
        else
            output = lookup(t);

        if (output.size() == 0)
            break;
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
DocVector Query::lookup(const string &term)
{
    DocVector output;
    Item key(term.c_str());

    ItemPtr pVal(btree.search(&key));
    if (pVal.get()) {
        UINT nlen = pVal->nlen;
        if ((nlen % sizeof(UINT64)) != 0)
            throw Exception("document vector size mismatch!");
        UINT docs = nlen / sizeof(UINT64);
        PUINT64 pdocs = reinterpret_cast<PUINT64>(pVal->data);
        for (UINT i = 0; i < docs; i++) {
            output.push_back(*pdocs++);
        }
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
DocVector Query::conj(const DocVector &left, const DocVector &right,
                      int distance) const
{
    DocVector output;

    DocVector::const_iterator lit = left.begin();
    DocVector::const_iterator rit = right.begin();

    UINT lword, rword;
    for (;;) {
        if (lit == left.end() || rit == right.end())
            break;

        lword = (*lit & 0xFFFFFFFF00000000) >> 32;
        rword = (*rit & 0xFFFFFFFF00000000) >> 32;

        if (lword == rword - distance) {	// conjunction
            output.push_back(*lit);
            lit++;
            rit++;
        } else if (lword > rword) {
            rit++;
        } else if (rword > lword) {
            lit++;
        }
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
string Query::term()
{
    string t;

    int c;
    while ((c = getc()) != EOF) {
        if (isalnum(c)) {
            t += (char)towlower(c);
        } else if (c == '_' || c == '\'' || c == '-') {
            if (t.length()) t += c;
        } else if (c == ',') {
            continue;
        } else {
            if (t.length()) break;
        }
    }

    return t;
}

/////////////////////////////////////////////////////////////////////////////
int Query::getc()
{
    UCHAR buf[1];

    DWORD read;
    HRESULT hr = m_pStream->Read(buf, sizeof(UCHAR), &read);
    if (FAILED(hr))
        return EOF;

    if (read == 0)
        return EOF;

    return buf[0];
}

/////////////////////////////////////////////////////////////////////////////
int Query::lookahead()
{
    UCHAR buf[1];

    DWORD read;
    HRESULT hr = m_pStream->Peek(buf, sizeof(UCHAR), &read);
    if (FAILED(hr))
        return EOF;

    if (read == 0)
        return EOF;

    return buf[0];
}

