/////////////////////////////////////////////////////////////////////////////
//
//	EBTREE.CPP : Enhanced disk based B-tree
//
//	Adapted from Sedgewick 16.3
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "ebtree.h"

/* Size of a disk page */
#define PAGE_SIZE		(4096)

/* Page type flags */
#define PTF_LEAF		(1 << 0)

/* Helper macros */
#define ISLEAF(p)		(p->header.flags & PTF_LEAF)
#define SETLEAF(p)		(p->header.flags |= PTF_LEAF)
#define SETINTERNAL(p)	(p->header.flags &= ~PTF_LEAF)
#define PAGENO(p)		(p->header.pageno)
#define CELLS(p)		(p->header.cells)
#define CBYTES(p)		(p->header.cbytes)

/* Cell accessors */
#define CELL(p, n)		(p->data[n])
#define KEY(p, n)		(p->data[n].entry->key)

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
Item::Item()
 : nlen(0), data(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(const Item &i)
{
	*this = i;
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(LPCSTR s)
{
	nlen = strlen(s);
	data = new char[nlen + 1];
	strcpy(data, s);
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(void *p, int len)
{
	data = new char[nlen = len];
	memcpy(data, p, len);
}

/////////////////////////////////////////////////////////////////////////////
Item::~Item()
{
	delete []data;
}

/////////////////////////////////////////////////////////////////////////////
Item &Item::operator =(const Item &i)
{
	if (this != &i) {
		delete []data;
		data = new char[nlen = i.nlen];
		memcpy(data, i.data, nlen);
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
bool Item::operator < (const Item &rhs)
{
	if (data == NULL || rhs.data == NULL)
		return false;
	return memcmp(data, rhs.data, min(nlen, rhs.nlen)) < 0;
}

/////////////////////////////////////////////////////////////////////////////
EBTree::EBTree(): hFile(INVALID_HANDLE_VALUE)
{
	allocpages();
}

/////////////////////////////////////////////////////////////////////////////
EBTree::~EBTree()
{
	close();
	freepages();
}

/////////////////////////////////////////////////////////////////////////////
void EBTree::allocpages()
{
	for (int i = 0; i < MAXDEPTH; i++) {
		pages[i] = MKPAGE();
	}
	frame[0] = MKPAGE();
	frame[1] = MKPAGE();
}

/////////////////////////////////////////////////////////////////////////////
void EBTree::freepages()
{
	for (int i = 0; i < MAXDEPTH; i++) {
		FREEPAGE(pages[i]);
	}
	FREEPAGE(frame[0]);
	FREEPAGE(frame[1]);
}

/////////////////////////////////////////////////////////////////////////////
BOOL EBTree::open(LPCSTR filename, OpenMode m)
{
	DWORD low, high[1];
	mode = m;

	if (!open(filename))
		return FALSE;
	
	low = GetFileSize(hFile, high);
	if (low || high[0])
		return readpage(0, 0);		// read page zero

	SETLEAF(pages[0]);				// set root page to leaf
	return writepage(pages[0]);		// write page zero
}

/////////////////////////////////////////////////////////////////////////////
void EBTree::close()
{
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
BOOL EBTree::open(LPCSTR filename)
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
LPITEM EBTree::search(LPITEM key)
{
	return searchR(pages[0], key, 0);
}

/////////////////////////////////////////////////////////////////////////////
LPITEM EBTree::searchR(LPPAGE h, LPITEM key, int level)
{
	int j;

	if (ISLEAF(h)) {	// leaf page
		for (j = 0; j < CELLS(h); j++) {
			if (*key < *KEY(h, j)) break;
		}
	} else {			// internal page
		;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
void EBTree::insert(LPENTRY entry)
{
	LPPAGE u = insertR(pages[0], entry, 0);
	if (u == 0) return;

	// TODO: root page split
}

/////////////////////////////////////////////////////////////////////////////
LPPAGE EBTree::insertR(LPPAGE h, LPENTRY entry, int level)
{
	if (ISLEAF(h)) {	// leaf page
		;
	} else {			// internal page
		;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
BOOL EBTree::readpage(INT64 page_no, int level)
{
	INT64 off = page_no * PAGE_SIZE;
	DWORD read[1];

	SetFilePointer(hFile, (LONG)off, (LPLONG)(&off)+1, 
		FILE_BEGIN);
	ReadFile(hFile, pages[level], PAGE_SIZE, read, NULL);
	return read[0] == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL EBTree::writepage(LPPAGE h)
{
	INT64 off = PAGENO(h) * PAGE_SIZE;
	DWORD written[1];

	SetFilePointer(hFile, (LONG)off, (LPLONG)(&off)+1, 
		FILE_BEGIN);
	WriteFile(hFile, h, PAGE_SIZE, written, NULL);
	return written[0] == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
LPPAGE EBTree::split(LPPAGE h)
{
	return NULL;
}