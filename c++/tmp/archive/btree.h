/////////////////////////////////////////////////////////////////////////////
//
//	BTREE.H : Disk based B-tree
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2004 KnowX.com, All Rights Reserved
//

#ifndef __BTREE_H__
#define __BTREE_H__

// ensure one byte alignment for structures below
#pragma pack (push, 1)	

/////////////////////////////////////////////////////////////////////////////
typedef struct Cell {
	pageid next;			// link to next subpage
	Key key;				// key for a cell
	Item item;				// item for a cell
} *LPCELL;

/////////////////////////////////////////////////////////////////////////////
typedef struct PageHeader {
	unsigned char flags;	// page flags
	pageid pageno;			// page number
	unsigned short cells;	// number of cells on the page
} *LPPAGEHEADER;

/////////////////////////////////////////////////////////////////////////////
typedef struct Page {
	PageHeader header;		// page header
	Cell data[1];			// page data
} *LPPAGE;

// restore default structure alignment
#pragma pack (pop)

/////////////////////////////////////////////////////////////////////////////
class BTree {
// Construction / Destruction
public:
	BTree();
	virtual ~BTree();

// Interface
public:
	bool open(const char *filename, OpenMode m);
	void close();
	void insert(Item item);
	Item search(Key v);
	
// Implementation
private:
	/*
	 * Maximum depth of the b-tree
	 *
	 * Currently this is set to 5.
	 * The average number of probes p is about
	 * logM(N).  So, we can have about M^p 
	 * items in the tree before we exceed the depth 
	 * limits of the tree.
	 */
	enum { MAXDEPTH = 5 };

	void allocpages();
	void freepages();

	bool open(const char *filename);
	bool readpage(pageid page_no, int level);
	bool writepage(LPPAGE h);
	bool insertpage(LPPAGE h);

	Item searchR(LPPAGE h, Key v, int level);
	LPPAGE insertR(LPPAGE h, Item x, int level);
	LPPAGE split(LPPAGE h);

	HANDLE hFile;			// file handle
	OpenMode mode;			// read-write mode
	LPPAGE pages[MAXDEPTH];	// pages in memory
	LPPAGE frame[2];		// spare frames for page split
};
/////////////////////////////////////////////////////////////////////////////

#endif // __BTREE_H__