/////////////////////////////////////////////////////////////////////////////
//
//	BTREEIMPL.H : String based btree implementation
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BTREEIMPL_H__
#define __BTREEIMPL_H__

/////////////////////////////////////////////////////////////////////////////
class BTreeImpl {
// Construction / Destruction
public:
    BTreeImpl();
    ~BTreeImpl();

// Interface
    BOOL open(LPCSTR filename, OpenMode m);
    void close();

    string search(const string &key);
    void insert(const string &key, const string &val);
    BOOL append(const string &key, const string &val);

    void writeStats(std::ostream &os) const;

// Implementation
private:
    BTree btree;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __BTREEIMPL_H__