/////////////////////////////////////////////////////////////////////////////
//
//	BTREE.CPP : Disk based B-tree
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2004 KnowX.com, All Rights Reserved
//

#include "common.h"
#include "item.h"
#include "extern.h"
#include "btree.h"

/* Size of a disk page */
#define PAGE_SIZE		(4096)

/* Page type flags */
#define PTF_LEAF		(1 << 0)

/* Helper macros */
#define ISLEAF(p)		(p->header.flags & PTF_LEAF)
#define SETLEAF(p)		(p->header.flags |= PTF_LEAF)
#define SETNONLEAF(p)	(p->header.flags &= ~PTF_LEAF)
#define PAGENO(p)		(p->header.pageno)
#define CELLS(p)		(p->header.cells)

/* Maximum number of cells on a page, must be even to split a page */
#define MAXCELLS		\
	((PAGE_SIZE - sizeof(PageHeader)) / sizeof(Cell) & ~1)

/* Cell accessors */
#define CELL(p, n)		(p->data[n])
#define KEY(p, n)		(p->data[n].key)
#define ITEM(p, n)		(p->data[n].item)
#define NEXT(p, n)		(p->data[n].next)

/* Allocate a new page */
#define MKPAGE()		\
	((LPPAGE)VirtualAlloc(NULL, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE))

/* Free an allocated page */
#define FREEPAGE(p)									\
	do {											\
		VirtualFree(p, 0, MEM_RELEASE);				\
		VirtualFree(p, PAGE_SIZE, MEM_DECOMMIT);	\
		p = NULL;									\
	} while(0)

/////////////////////////////////////////////////////////////////////////////
BTree::BTree()
 : hFile(INVALID_HANDLE_VALUE)
{
	allocpages();
}

/////////////////////////////////////////////////////////////////////////////
BTree::~BTree()
{
	close();
	freepages();
}

/////////////////////////////////////////////////////////////////////////////
void BTree::allocpages()
{
	for (int i = 0; i < MAXDEPTH; i++) {
		pages[i] = MKPAGE();
	}
	frame[0] = MKPAGE();
	frame[1] = MKPAGE();
}

/////////////////////////////////////////////////////////////////////////////
void BTree::freepages()
{
	for (int i = 0; i < MAXDEPTH; i++) {
		FREEPAGE(pages[i]);
	}
	FREEPAGE(frame[0]);
	FREEPAGE(frame[1]);
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::open(const char *filename, OpenMode m)
{
	DWORD low, high[1];
	mode = m;

	if (!open(filename))
		return false;
	
	low = GetFileSize(hFile, high);
	if (low || high[0])
		return readpage(0, 0);		// read page zero

	SETLEAF(pages[0]);				// set root page to leaf
	return writepage(pages[0]);		// write page zero
}

/////////////////////////////////////////////////////////////////////////////
void BTree::close()
{
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::open(const char *filename)
{
	DWORD flags = 0, disp = 0;
	DWORD attr = FILE_ATTRIBUTE_NORMAL;

	close();

	switch(mode) {
	case OM_RW:
		attr |= FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING;
		flags |= GENERIC_READ | GENERIC_WRITE;
		disp |= OPEN_ALWAYS;
		break;
	case OM_RO:	
	default:
		flags |= GENERIC_READ;
		disp |= OPEN_EXISTING;
		break;
	}
	hFile = CreateFile(filename, flags, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, disp, attr, NULL);

	return hFile != INVALID_HANDLE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////
Item BTree::search(Key v)
{
	return searchR(pages[0], v, 0);
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::readpage(pageid page_no, int level)
{
	pageid off = page_no * PAGE_SIZE;
	DWORD read[1];

	SetFilePointer(hFile, (LONG)off, (LPLONG)(&off)+1, 
		FILE_BEGIN);
	ReadFile(hFile, pages[level], PAGE_SIZE, read, NULL);
	return read[0] == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::writepage(LPPAGE h)
{
	pageid off = PAGENO(h) * PAGE_SIZE;
	DWORD written[1];

	SetFilePointer(hFile, (LONG)off, (LPLONG)(&off)+1, 
		FILE_BEGIN);
	WriteFile(hFile, h, PAGE_SIZE, written, NULL);
	return written[0] == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::insertpage(LPPAGE h)
{
	DWORD low, high = 0, written[1];

	low = SetFilePointer(hFile, 0, (LPLONG)&high, FILE_END);
	PAGENO(h) = (low | (high << 32)) / PAGE_SIZE;
	WriteFile(hFile, h, PAGE_SIZE, written, NULL);
	return written[0] == PAGE_SIZE;	
}

/////////////////////////////////////////////////////////////////////////////
Item BTree::searchR(LPPAGE h, Key v, int level)
{
	int j;

	if (ISLEAF(h)) { // leaf page
		for (j = 0; j < CELLS(h); j++) {
			if (KEY(h, j) == v)
				return ITEM(h, j);
		}
	} else { // internal page
		for (j = 0; j < CELLS(h); j++) {
			if ((j+1 == CELLS(h) || v < KEY(h, j+1))) {
				if (!readpage(NEXT(h, j), level+1))
					return nullItem;
				return searchR(pages[level+1], v, level+1);
			}
		}
	}

	return nullItem;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::insert(Item item)
{
	LPPAGE u = insertR(pages[0], item, 0);
	if (u == 0) return;

	/* 
	 * The basic idea with the root page split is that we create a new 
	 * internal root page t with 2 links. The first link points to 
	 * the old root page and the second link points to the page that caused 
	 * the split.  The height of the tree is increased by one.
	 */
	LPPAGE t = frame[1];
	memset(t, 0, PAGE_SIZE);

	insertpage(pages[0]);	// relocate old root page

	SETNONLEAF(t);
	CELLS(t) = 2;
	KEY(t, 0) = KEY(pages[0], 0);
	KEY(t, 1) = KEY(u, 0);
	NEXT(t, 0) = PAGENO(pages[0]); NEXT(t, 1) = PAGENO(u);
	 
	memcpy(pages[0], t, PAGE_SIZE);
	writepage(pages[0]);
}

/////////////////////////////////////////////////////////////////////////////
LPPAGE BTree::insertR(LPPAGE h, Item x, int level)
{
	int i, j; Key v = x.key(); Cell t;
	t.key = v; t.item = x;
	if (ISLEAF(h)) { // leaf page
		for (j = 0; j < CELLS(h); j++) {
			if (v < KEY(h, j)) break;
		}
	} else { // internal page
		for (j = 0; j < CELLS(h); j++) {
			if ((j+1 == CELLS(h) || v < KEY(h, j+1))) {
				LPPAGE u; 
				if (!readpage(NEXT(h, j++), level+1))
					return 0;
				u = insertR(pages[level+1], x, level+1);
				if (u == 0) return 0;
				t.key = KEY(u, 0); t.next = PAGENO(u);
				break;
			}
		}
	}

	for (i = CELLS(h); i > j; i--) CELL(h, i) = CELL(h, i-1);
	CELL(h, j) = t;
	if (++CELLS(h) < MAXCELLS) {
		writepage(h);		// write dirty page
		return 0; 
	} 
	
	return split(h);	
}

/////////////////////////////////////////////////////////////////////////////
LPPAGE BTree::split(LPPAGE h)
{
	LPPAGE t = frame[0];
	memset(t, 0, PAGE_SIZE);

	t->header.flags = h->header.flags;

	for (int j = 0; j < MAXCELLS/2; j++) 
		CELL(t, j) = CELL(h, MAXCELLS/2+j);

	CELLS(h) = MAXCELLS/2; CELLS(t) = MAXCELLS/2;

	writepage(h);
	insertpage(t);

	return t;

}