/////////////////////////////////////////////////////////////////////////////
//
//	EBTREE.H : Enhanced disk based B-tree
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __EBTREE_H__
#define __EBTREE_H__

/////////////////////////////////////////////////////////////////////////////
typedef struct Item {

// Construction / Destruction
	Item();
	Item(const Item &i);
	Item(LPCSTR s);
	Item(void *p, int len);
	~Item();

// Interface
	Item &operator =(const Item &i);
	bool operator < (const Item &rhs);

// Implementation
	int nlen;				// length of data
	char *data;				// data for the item	
} *LPITEM;

typedef auto_ptr<Item> ItemPtr;

/////////////////////////////////////////////////////////////////////////////
typedef struct Entry {
	LPITEM key;				// key for entry
	LPITEM val;				// value for entry
} *LPENTRY;

/////////////////////////////////////////////////////////////////////////////
typedef struct Cell {
	INT64 next;				// link to next subpage
	LPENTRY entry;			// entry for cell
} *LPCELL;

// ensure one byte alignment for structures below
#pragma pack (push, 1)	

/////////////////////////////////////////////////////////////////////////////
typedef struct PageHeader {
	unsigned char flags;	// page flags
	INT64 pageno;			// page number
	unsigned short cells;	// number of cells on the page
	unsigned short cbytes;	// number of total bytes taken up by cells
} *LPPAGEHEADER;

/////////////////////////////////////////////////////////////////////////////
typedef struct Page {
	PageHeader header;		// page header
	Cell data[1];			// page data
} *LPPAGE;

// restore default structure alignment
#pragma pack (pop)

/* open mode */
enum OpenMode { OM_RW, OM_RO };

/////////////////////////////////////////////////////////////////////////////
class EBTree {
// Construction / Destruction
public:
	EBTree();
	virtual ~EBTree();
	
// Interface
public:
	BOOL open(LPCSTR filename, OpenMode m);
	void close();
	
	void insert(LPENTRY entry);
	LPITEM search(LPITEM key);
	
// Implementation
private:
	/*
	 * Maximum depth of the b-tree
	 *
	 * Currently this is set to 5.
	 *
	 * The average number of probes p is about
	 * log_M(N).  So, we can have about M^p 
	 * items in the tree before we exceed the depth 
	 * limits of the tree.
	 */
	enum { MAXDEPTH = 5 };

	void allocpages();
	void freepages();

	BOOL open(LPCSTR filename);
	BOOL readpage(INT64 page_no, int level);
	BOOL writepage(LPPAGE h);
	BOOL insertpage(LPPAGE h);
	
	LPITEM searchR(LPPAGE h, LPITEM key, int level);
	LPPAGE insertR(LPPAGE h, LPENTRY entry, int level);
	LPPAGE split(LPPAGE h);

	HANDLE hFile;			// file handle
	OpenMode mode;			// read-write mode
	LPPAGE pages[MAXDEPTH];	// pages in memory
	LPPAGE frame[2];		// spare frames for page split
};
/////////////////////////////////////////////////////////////////////////////	

#endif // __EBTREE_H__
