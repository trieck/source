/////////////////////////////////////////////////////////////////////////////
//
//	BTREE.CPP : disk based b-tree
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include <time.h>
#include "stdint.h"
#include "item.h"
#include "RandStream.h"
#include "blockio.h"
#include "BlockMgr.h"
#include "wthread.h"
#include "LazyIO.h"
#include "btree.h"
#include "util.h"

/* Size of a disk page, must be a multiple of sector size */
#define PAGE_SIZE		(4096)

/* Page type flags */
#define PTF_LEAF		(1 << 0)
#define PTF_SPILL		(1 << 1)

/* File header accessors */
#define CURRSPILL()		(header.currspill)

/* Page header accessors */
#define PFLAGS(p)		(p->header.flags)
#define ISLEAF(p)		(p->header.flags & PTF_LEAF)
#define ISSPILL(p)		(p->header.flags & PTF_SPILL)
#define SETLEAF(p)		(p->header.flags |= PTF_LEAF)
#define SETSPILL(p)		(p->header.flags |= PTF_SPILL)
#define SETINTERNAL(p)	(p->header.flags &= ~(PTF_LEAF | PTF_SPILL))
#define PAGENO(p)		(p->header.pageno)
#define CELLS(p)		(p->header.cells)

/* Cell flags */
#define CF_LRGVAL		(1 << 0)

/* Cell accessors */
#define CELL(p, n)		(p->data[n])
#define CFLAGS(p, n)	(p->data[n].flags)
#define ISLRGVAL(p, n)	(p->data[n].flags & CF_LRGVAL)
#define SETLRGVAL(p, n)	(p->data[n].flags |= CF_LRGVAL)
#define SETSMLVAL(p, n)	(p->data[n].flags &= ~CF_LRGVAL)
#define INDEX(p, n)		(p->data[n].index)
#define KEYLEN(p, n)	(p->data[n].keylen)
#define VALLEN(p, n)	(p->data[n].vallen)
#define NEXT(p, n)		(p->data[n].next)

/* Spill cell accessors */
#define SCLEN(p)		(p->len)
#define SCTOTALLEN(p)	(p->totallen)
#define SCNEXTPG(p)		(p->next.pageno)
#define SCNEXTOFF(p)	(p->next.offset)

/* Spill cell pointer accessors */
#define SPPAGENO(p)		(p.pageno)
#define SPOFFSET(p)		(p.offset)

/* Entry accessors */
#define KEY(e)			(e->key)
#define VAL(e)			(e->val)

/* Item accessors */
#define DATA(i)			(i->data)
#define LEN(i)			(i->nlen)
#define ATTACH(i, p, n)	(i->Attach(p, n))

/* Data accessor */
#define PAGE_DATA(p, o)	(&((LPSTR)p)[o])

/* Page spill cell accessor */
#define SPILLCELL(p, o)	((PSPILLCELL)(&t->data)[o])

/* Spill page data accessor */
#define SPDATA(p, o)	((LPSTR)(SPILLCELL(p, o)+1))

/* Initialize a page */
#define INITPAGE(p)									\
	do {											\
		memset(p, 0, PAGE_SIZE);					\
	} while (0)

/* Free an allocated page */
#define FREEPAGE(p)									\
	do {											\
		free(p);									\
		p = NULL;									\
	} while(0)

/*
 * Maximum number of cells on a page.
 * This MUST be even to split a page.
 *
 * NOTE: This has been hand tuned for maximum efficiency
 * in storing cells and cell data on a 4k page.
 */

/* maximum number of cells on an internal page */
#define MAX_INTERNAL_CELLS	(14)

/* maximum number of cells on a leaf page */
#define MAX_LEAF_CELLS		(8)

/* size of one data block */
#define BLOCKSIZE(p) (ISLEAF(p) ?					\
	(MAX_KEY_LEN + MAX_VAL_LEN) :					\
	(MAX_KEY_LEN))

/* offset to key data */
#define KEYOFFSET(p, n)								\
	((PAGE_SIZE - 1) -								\
	(INDEX(p, n) * BLOCKSIZE(p)))

/* offset to value data */
#define VALOFFSET(p, n)								\
	(((PAGE_SIZE - 1) -								\
	(INDEX(p, n) * BLOCKSIZE(p))) -					\
	(MAX_KEY_LEN))

/* maximum number of cells on a page */
#define MAXCELLS(p) (ISLEAF(p) ?					\
	MAX_LEAF_CELLS : MAX_INTERNAL_CELLS)

/* total number of possible cells */
#define TOTALCELLS									\
	((PAGE_SIZE - sizeof(PageHeader)) / sizeof(Cell))

/* align block to integral multiple of cell size */
#define CELLALIGN(n)								\
	(n + (sizeof(Cell) - 1) & ~(sizeof(Cell) - 1))

/* align spill cell with n bytes of storage */
#define SPILLALIGN(n)								\
	(CELLALIGN(sizeof(SpillCell) + n))

/* number of cells required for a spill entry with n bytes of storage */
#define SPILLCELLS(n)	(SPILLALIGN(n) / sizeof(Cell))

/* length of bytes needed for a spill cell pointer */
#define SPILLCELL_PTR_LEN	(sizeof(SpillCellPtr))

#define MINSPILLCELLS		(2)

/* file magic number */
const uint8_t BTree::magic_no[] = {
	'E', 'N', 'H', 'B', 'T', 'R', 'E', 'E'
};

/* version numbers */
const uint16_t BTree::majorVer = 0x0001;
const uint16_t BTree::minorVer = 0x0001;

/////////////////////////////////////////////////////////////////////////////
BTree::BTree()
	: io(PAGE_SIZE, sizeof(FileHeader))
{
	memset(&header, 0, sizeof(FileHeader));
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
		pages[i] = mkpage();
	}
	frame[0] = mkpage();
	frame[1] = mkpage();
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
bool BTree::open(LPCSTR filename, OpenMode m)
{
	if (!io.open(filename, mode = m))
		return false;

	uint64_t size = io.getFileSize();
	if (size > 0) {
		if (!readFH())				// read file header
			return false;
		return readpage(0, 0);		// read page zero
	}

	SETLEAF(pages[0]);				// set root page to leaf

	if (!insertFH())				// insert file header
		return false;

	return insertpage(pages[0]);		// write page zero
}

/////////////////////////////////////////////////////////////////////////////
void BTree::close()
{
	if (io.isOpen()) {
		flushFH();
		io.close();
	}
}

/////////////////////////////////////////////////////////////////////////////
PITEM BTree::search(PITEM key)
{
	PPAGE h;
	uint16_t j;
	if ((h = find(key, j)))
		return value(h, j);

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::exists(PITEM key)
{
	uint16_t j;
	return (find(key, j) != NULL);
}

/////////////////////////////////////////////////////////////////////////////
PPAGE BTree::find(PITEM key, uint16_t &cell)
{
	return findR(pages[0], key, 0, cell);
}

/////////////////////////////////////////////////////////////////////////////
PPAGE BTree::findR(PPAGE h, PITEM key, uint8_t level, uint16_t &cell)
{
	uint16_t j;

	if (ISLEAF(h)) { // leaf page
		for (j = 0; j < CELLS(h); j++) {
			if (compare(key, h, j) == 0) {
				cell = j;
				return h;
			}
		}
	} else { // internal page
		for (j = 0; j < CELLS(h); j++) {
			if ((j+1 == CELLS(h) || compare(key, h, j+1) < 0)) {
				if (!readpage(NEXT(h, j), level+1))
					return NULL;
				return findR(pages[level+1], key, level+1, cell);
			}
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
PITEM BTree::key(PPAGE h, uint16_t item)
{
	uint32_t n, nlen;
	n = nlen = KEYLEN(h, item);

	uint16_t offset = KEYOFFSET(h, item);
	LPSTR pdata = PAGE_DATA(h, offset);

	PITEM pKey = new Item();
	LEN(pKey) = nlen;

	LPSTR p = DATA(pKey) = new char[nlen];

	while (n--) {
		*p++ = *pdata--;
	}

	return pKey;
}

/////////////////////////////////////////////////////////////////////////////
PITEM BTree::value(PPAGE h, uint16_t item)
{
	uint32_t n, nlen;
	n = nlen = VALLEN(h, item);

	uint16_t offset = VALOFFSET(h, item);
	LPSTR pdata = PAGE_DATA(h, offset);

	PITEM pVal = new Item();
	LEN(pVal) = nlen;

	LPSTR p = DATA(pVal) = new char[nlen];

	while (n--) {
		*p++ = *pdata--;
	}

	// check for large values
	// and retrieve data from spill page
	if (ISLRGVAL(h, item)) {
		return largeval(pVal);
	}

	return pVal;
}

/////////////////////////////////////////////////////////////////////////////
PITEM BTree::largeval(PITEM pVal)
{
	ItemPtr v(pVal);	// owns the item

	SpillCellPtr pcell;
	LPCSTR pdata = DATA(pVal);
	memcpy(&pcell, pdata+(MAX_VAL_LEN-SPILLCELL_PTR_LEN*2),
	       sizeof(SpillCellPtr));

	PPAGE t = frame[0];
	PAGENO(t) = SPPAGENO(pcell);
	if (!readpage(t))
		return NULL;

	uint16_t offset = SPOFFSET(pcell);
	PSPILLCELL cell = SPILLCELL(t, offset);

	PITEM value = new Item();
	ItemPtr u(value);
	uint32_t n = LEN(pVal) - SPILLCELL_PTR_LEN*2;
	LEN(value) = SCTOTALLEN(cell) + n;
	LPSTR pbuf = DATA(value) = new char[LEN(value)];

	// copy small value first
	while (n--) *pbuf++ = *pdata++;

	// copy data stored on this page
	n = SCLEN(cell);
	pdata = SPDATA(t, offset);
	while (n--) *pbuf++ = *pdata++;

	// follow the page chain
	while (SCNEXTPG(cell)) {
		PAGENO(t) = SCNEXTPG(cell);
		offset = SCNEXTOFF(cell);
		if (!readpage(t))
			return NULL;	// can't read

		cell = SPILLCELL(t, offset);
		n = SCLEN(cell);
		pdata = SPDATA(t, offset);
		while (n--) *pbuf++ = *pdata++;
	}

	return u.release();
}


/////////////////////////////////////////////////////////////////////////////
bool BTree::append(PENTRY entry)
{
	PPAGE h;
	uint16_t j;
	if ((h = find(KEY(entry), j))) {
		append(h, j, VAL(entry));
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::append(PPAGE h, uint16_t item, PITEM val)
{
	LPSTR p1, p2, p3, buf;

	uint16_t vlen = VALLEN(h, item), offset = VALOFFSET(h, item);
	uint32_t nlen = LEN(val), ntotal = nlen + vlen, m, n;

	SpillCellPtr first, last;

	if (ISLRGVAL(h, item)) {	// large value
		p1 = PAGE_DATA(h, offset) - (MAX_VAL_LEN-SPILLCELL_PTR_LEN*2);
		p2 = (LPSTR)&first;
		n = SPILLCELL_PTR_LEN;
		while (n--) *p2++ = *p1--;

		p2 = (LPSTR)&last;
		n = SPILLCELL_PTR_LEN;
		while (n--) *p2++ = *p1--;

		last = appendlarge(first, last, val);

		p1 = PAGE_DATA(h, offset) - (MAX_VAL_LEN-SPILLCELL_PTR_LEN);
		p2 = (LPSTR)&last;
		n = SPILLCELL_PTR_LEN;
		while (n--) *p1-- = *p2++;
	} else {	// small value
		p1 = PAGE_DATA(h, offset) - vlen;
		p2 = DATA(val);
		if (ntotal <= MAX_VAL_LEN) {	// will fit in cell
			VALLEN(h, item) = ntotal;
			while (nlen--) *p1-- = *p2++;
		} else {	// won't fit
			SETLRGVAL(h, item);	// value becomes large
			m = MAX_VAL_LEN - vlen;	// number of bytes left in the cell
			if (m < SPILLCELL_PTR_LEN*2) {
				// Move n bytes off the cell area
				// to make space for the spill cell pointers
				m = n = SPILLCELL_PTR_LEN*2 - m;
				p3 = buf = new char[n + nlen];
				for (p1 += n; n--; ) *p3++ = *p1--;
				memcpy(p3, p2, nlen);
				ATTACH(val, buf, m + nlen);
				p1 += m;
				p2 = DATA(val);
				nlen = LEN(val);
			} else {	// store what we can in the remaining space
				n = m - SPILLCELL_PTR_LEN*2;
				for ( ; n--; nlen--) *p1-- = *p2++;
			}

			VALLEN(h, item) = MAX_VAL_LEN;

			SpillCellPtr ptr = nextspill();
			LPSTR pp = (LPSTR)&ptr;
			for (n = SPILLCELL_PTR_LEN; n--; ) *p1-- = *pp++;

			ptr = spill(p2, nlen);
			pp = (LPSTR)&ptr;

			for (n = SPILLCELL_PTR_LEN; n--; ) *p1-- = *pp++;
		}
	}

	writepage(h);
}

/////////////////////////////////////////////////////////////////////////////
SpillCellPtr BTree::appendlarge(SpillCellPtr first, SpillCellPtr last,
                                PITEM val)
{
	// read first spill cell
	PPAGE t = frame[0], u = frame[1];
	PAGENO(t) = SPPAGENO(first);

	readpage(t);

	uint16_t offset = SPOFFSET(first);
	PSPILLCELL cell = SPILLCELL(t, offset);

	// update new total length on first spill cell
	uint32_t nlen = LEN(val), ntotal = SCTOTALLEN(cell) + nlen;
	SCTOTALLEN(cell) = ntotal;
	writepage(t);

	// append new data starting at last spill cell
	PAGENO(t) = SPPAGENO(last);
	readpage(t);

	offset = SPOFFSET(last);
	cell = SPILLCELL(t, offset);
	SCTOTALLEN(cell) = ntotal;

	uint32_t len = SCLEN(cell), n;
	uint32_t extra = CELLALIGN(len) - len;
	LPSTR pdata = SPDATA(t, offset) + len;
	LPSTR data = DATA(val);

	if (extra > 0) {	// can append in current cell
		n = min(extra, nlen);
		SCLEN(cell) += n;
		for ( ; n--; nlen--) *pdata++ = *data++;
	}

	if (nlen == 0) {	// done
		writepage(t);
		return last;
	}

	uint32_t req = CELLALIGN(nlen) / sizeof(Cell);
	uint32_t avail = TOTALCELLS - CELLS(t);

	n = offset + SPILLCELLS(len);
	if (n == CELLS(t) && avail > 0) {	// more contiguous space exists
		if (req <= avail) {
			SCLEN(cell) += nlen;
			while (nlen--) *pdata++ = *data++;
			CELLS(t) += req;
			writepage(t);
			return last;
		} else {
			// create a new spill page
			INITPAGE(u);
			SETSPILL(u);
			insertpage(u);

			// store what we can on the current page
			SCLEN(cell) += n = avail * sizeof(Cell);
			SCNEXTPG(cell) = CURRSPILL() = PAGENO(u);
			SCNEXTOFF(cell) = CELLS(u);

			for ( ; n--; nlen--) *pdata++ = *data++;
			CELLS(t) = TOTALCELLS;	// close full page
			writepage(t);
			memcpy(t, u, PAGE_SIZE);
		}
	} else {
		// create a new spill page and link it in
		INITPAGE(u);
		SETSPILL(u);
		insertpage(u);

		SCNEXTPG(cell) = CURRSPILL() = PAGENO(u);
		SCNEXTOFF(cell) = CELLS(u);

		writepage(t);
		memcpy(t, u, PAGE_SIZE);
	}

	return spill(t, data, nlen);
}

/////////////////////////////////////////////////////////////////////////////
void BTree::insert(PENTRY entry)
{
	PPAGE u = insertR(pages[0], entry, 0);
	header.numitems++;
	if (u == 0) return;

	/*
	 * The basic idea with the root page split is that we create a new
	 * internal root page t with 2 links. The first link points to
	 * the old root page and the second link points to the page that caused
	 * the split.  The height of the tree is increased by one.
	 */
	PPAGE t = frame[1];
	INITPAGE(t);

	insertpage(pages[0]);	// relocate old root page

	SETINTERNAL(t);
	CELLS(t) = 2;

	INDEX(t, 0) = 0;
	INDEX(t, 1) = 1;

	xferK(t, 0, pages[0], 0);
	xferK(t, 1, u, 0);

	NEXT(t, 0) = PAGENO(pages[0]);
	NEXT(t, 1) = PAGENO(u);

	// page zero always holds root page
	memcpy(pages[0], t, PAGE_SIZE);
	writepage(pages[0]);
}

/////////////////////////////////////////////////////////////////////////////
void BTree::xfer(PPAGE dest, uint16_t m, PPAGE src, uint16_t n)
{
	xferK(dest, m, src, n);
	if (ISLEAF(dest) && ISLEAF(src))
		xferV(dest, m, src, n);
}

/////////////////////////////////////////////////////////////////////////////
void BTree::xferK(PPAGE dest, uint16_t m, PPAGE src, uint16_t n)
{
	uint16_t srcoffset = KEYOFFSET(src, n);
	uint16_t destoffset = KEYOFFSET(dest, m);
	uint32_t len = KEYLEN(dest, m) = KEYLEN(src, n);

	LPSTR psrc = PAGE_DATA(src, srcoffset);
	LPSTR pdest = PAGE_DATA(dest, destoffset);

	while (len--) *pdest-- = *psrc--;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::xferV(PPAGE dest, uint16_t m, PPAGE src, uint16_t n)
{
	uint16_t srcoffset = VALOFFSET(src, n);
	uint16_t destoffset = VALOFFSET(dest, m);
	uint32_t len = VALLEN(dest, m) = VALLEN(src, n);

	LPSTR psrc = PAGE_DATA(src, srcoffset);
	LPSTR pdest = PAGE_DATA(dest, destoffset);

	while (len--) *pdest-- = *psrc--;
}

/////////////////////////////////////////////////////////////////////////////
PPAGE BTree::insertR(PPAGE h, PENTRY e, uint8_t level)
{
	PITEM v = KEY(e);
	ItemPtr pKey;
	uint64_t *pnext(NULL);
	uint16_t i, j;

	if (ISLEAF(h)) {	// leaf page
		for (j = 0; j < CELLS(h); j++) {
			if (compare(v, h, j) < 0) break;
		}
	} else {			// internal page
		for (j = 0; j < CELLS(h); j++) {
			if ((j+1 == CELLS(h) || compare(v, h, j+1) < 0)) {
				if (!readpage(NEXT(h, j++), level+1))
					return 0;
				PPAGE u = insertR(pages[level+1], e, level+1);
				if (u == 0) return 0;
				pKey = ItemPtr(key(u, 0));
				pnext = &PAGENO(u);
				break;
			}
		}
	}

	for (i = CELLS(h); i > j; i--) CELL(h, i) = CELL(h, i-1);

	store(h, j, e, pKey.get(), pnext);

	if (++CELLS(h) < MAXCELLS(h)) {
		writepage(h);		// write dirty page
		return 0;			// don't split page
	}

	return split(h);
}

/////////////////////////////////////////////////////////////////////////////
int BTree::compare(PITEM key, PPAGE h, uint16_t item)
{
	uint16_t keylen = KEYLEN(h, item);
	uint16_t offset = KEYOFFSET(h, item);

	char *p1 = DATA(key);
	char *p2 = PAGE_DATA(h, offset);

	uint32_t n = min(LEN(key), keylen);

	while (n--) {
		if (*p1 != *p2)
			return *p1 - *p2;
		p1++;
		p2--;
	}

	return LEN(key) - keylen;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::store(PPAGE h, uint16_t item, PENTRY e, PITEM newKey,
                  uint64_t *next)
{
	INDEX(h, item) = CELLS(h);

	PITEM pKey = newKey == NULL ? KEY(e) : newKey;

	if (next) NEXT(h, item) = *next;

	storeK(h, item, pKey);
	if (ISLEAF(h)) {
		storeV(h, item, VAL(e));
	}
}

/////////////////////////////////////////////////////////////////////////////
void BTree::storeK(PPAGE h, uint16_t item, PITEM key)
{
	uint32_t n = KEYLEN(h, item) = min(MAX_KEY_LEN, LEN(key));
	uint16_t offset = KEYOFFSET(h, item);

	LPSTR pdata = PAGE_DATA(h, offset);
	LPSTR pkey = DATA(key);

	while (n--) *pdata-- = *pkey++;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::storeV(PPAGE h, uint16_t item, PITEM val)
{
	uint32_t n = VALLEN(h, item) = min(MAX_VAL_LEN, LEN(val));

	uint16_t offset = VALOFFSET(h, item);
	LPSTR pdata = PAGE_DATA(h, offset);
	LPSTR pval = DATA(val);

	// If the length of the value exceeds MAX_VAL_LEN,
	// additional data is stored on the active spill page.
	// In this case, we only store MAX_VAL_LEN - (SPILLCELL_PTR_LEN * 2)
	// bytes in the data area.  The last SPILLCELL_PTR_LEN * 2 bytes are
	// used to store the page numbers and offsets of the first and last
	// spill pages where additional data can be found.
	if (LEN(val) > MAX_VAL_LEN) {
		SETLRGVAL(h, item);
		while (n-- > SPILLCELL_PTR_LEN*2) *pdata-- = *pval++;
		SpillCellPtr ptr = nextspill();
		LPSTR pp = (LPSTR)&ptr;
		for (++n; n-- > SPILLCELL_PTR_LEN; ) *pdata-- = *pp++;
		n = LEN(val) - (MAX_VAL_LEN - SPILLCELL_PTR_LEN*2);
		ptr = spill(pval, n);
		pp = (LPSTR)&ptr;
		for (n = SPILLCELL_PTR_LEN; n--; ) *pdata-- = *pp++;
	} else {
		SETSMLVAL(h, item);
		while (n--) *pdata-- = *pval++;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::readFH()
{
	uint32_t nread = io.readheader(&header);
	if (nread != sizeof(FileHeader))
		return false;

	if (memcmp(&header.magicno, magic_no, sizeof(uint64_t)) != 0)
		return false;	// magic number mismatch

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::insertFH()
{
	memcpy(&header.magicno, magic_no, sizeof(uint64_t));
	header.createdt = time(NULL);
	header.size = sizeof(FileHeader);
	header.versionno = (minorVer << 16) | majorVer;
	header.numblocks = header.numleaf = 1;	// initial leaf page zero
	return writeFH();
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::writeFH()
{
	uint32_t nwritten = io.writeheader(&header);
	return nwritten == sizeof(FileHeader);
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::flushFH()
{
	// flush file header changes to disk
	if (mode != OM_RO) {
		return writeFH();
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::readpage(uint64_t page_no, uint8_t level)
{
	uint32_t nread = io.readblock(page_no, pages[level]);
	return nread == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::readpage(PPAGE h)
{
	uint32_t nread = io.readblock(PAGENO(h), h);
	return nread == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::writepage(PPAGE h)
{
	uint32_t nwritten = io.writeblock(PAGENO(h), h);
	return nwritten == PAGE_SIZE;
}

/////////////////////////////////////////////////////////////////////////////
bool BTree::insertpage(PPAGE h)
{
	uint64_t off = io.getFileSize();
	PAGENO(h) = (off - sizeof(FileHeader)) / PAGE_SIZE;

	uint32_t nwritten = io.insertblock(h);
	if (nwritten != PAGE_SIZE)
		return false;

	updateST(h);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::updateST(PPAGE h)
{
	// update b-tree statistics

	if (ISLEAF(h)) {
		header.numleaf++;
	} else if (ISSPILL(h)) {
		header.numspill++;
	} else {
		header.numinternal++;
	}

	header.numblocks++;
}

/////////////////////////////////////////////////////////////////////////////
PPAGE BTree::split(PPAGE h)
{
	PPAGE t = frame[0];
	INITPAGE(t);
	PFLAGS(t) = PFLAGS(h);

	uint16_t n = MAXCELLS(h) / 2;
	CELLS(h) = CELLS(t) = n;

	for (uint16_t j = 0; j < n; j++) {
		CELL(t, j) = CELL(h, n + j);
		INDEX(t, j) = j;
		xfer(t, j, h, n + j);
	}

	reorder(h);
	writepage(h);
	insertpage(t);

	return t;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::reorder(PPAGE h)
{
	/*
	 * Reorder a split page, so that the data offsets
	 * correspond to the cells.  we need to do this
	 * because a split page contains invalid indexes
	 * with respect to the real number of cells on the
	 * new split page.
	 */

	PPAGE t = frame[1];
	INITPAGE(t);

	PAGENO(t) = PAGENO(h);
	PFLAGS(t) = PFLAGS(h);
	CELLS(t) = CELLS(h);

	for (uint16_t i = 0; i < CELLS(h); i++) {
		CELL(t, i) = CELL(h, i);
		INDEX(t, i) = i;
		xfer(t, i, h, i);
	}

	memcpy(h, t, PAGE_SIZE);
}

/////////////////////////////////////////////////////////////////////////////
PPAGE BTree::mkpage()
{
	PPAGE pPage = (PPAGE)malloc(PAGE_SIZE);
	INITPAGE(pPage);
	return pPage;
}

/////////////////////////////////////////////////////////////////////////////
SpillCellPtr BTree::nextspill()
{
	// return address of next available spill location
	SpillCellPtr ptr;
	PPAGE t = frame[0];

	/* check for no currently active page */
	if ((SPPAGENO(ptr) = CURRSPILL()) == 0) {
		PPAGE t = frame[0];
		INITPAGE(t);
		SETSPILL(t);
		insertpage(t);
		SPPAGENO(ptr) = CURRSPILL() = PAGENO(t);
		SPOFFSET(ptr) = 0;
	} else {
		PAGENO(t) = SPPAGENO(ptr);
		readpage(t);

		// no space on current page
		if (TOTALCELLS - CELLS(t) <= MINSPILLCELLS) {
			CELLS(t) = TOTALCELLS;			// close page
			writepage(t);					// write page
			INITPAGE(t);
			SETSPILL(t);
			insertpage(t);					// create a new spill page
			SPPAGENO(ptr) = CURRSPILL() = PAGENO(t);
		};

		SPOFFSET(ptr) = CELLS(t);
	}

	return ptr;
}

/////////////////////////////////////////////////////////////////////////////
SpillCellPtr BTree::spill(LPCSTR data, uint32_t len)
{
	PPAGE t = frame[0];

	PAGENO(t) = CURRSPILL();
	readpage(t);

	return spill(t, data, len);
}

/////////////////////////////////////////////////////////////////////////////
SpillCellPtr BTree::spill(PPAGE h, LPCSTR data, uint32_t len)
{
	SpillCellPtr last;

	PPAGE t = h, u = frame[1], v;
	uint32_t req, avail, offset, nlen, ntotal = len;
	PSPILLCELL cell;
	LPSTR pdata;

	SPPAGENO(last) = PAGENO(t);

	for (;;) {
		req = SPILLCELLS(len);
		avail = TOTALCELLS - CELLS(t);
		offset = SPOFFSET(last) = CELLS(t);
		cell = SPILLCELL(t, offset);
		SCTOTALLEN(cell) = ntotal;
		pdata = SPDATA(t, offset);
		if (req <= avail) {	// can fit whole datum
			SCLEN(cell) = len;
			while (len--) *pdata++ = *data++;
			CELLS(t) += req;
			writepage(t);
			break;
		} else {	// can't fit whole datum
			// create a new spill page
			INITPAGE(u);
			SETSPILL(u);
			insertpage(u);

			// store what we can on the current page
			len -= SCLEN(cell) = nlen = (avail-1) * sizeof(Cell);
			SCNEXTPG(cell) = SPPAGENO(last) = CURRSPILL() = PAGENO(u);
			SCNEXTOFF(cell) = SPOFFSET(last) = CELLS(u);

			while (nlen--) *pdata++ = *data++;
			CELLS(t) = TOTALCELLS;	// close full page
			writepage(t);

			// swap page buffers
			v = t;
			t = u;
			u = v;
		}
	}

	return last;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::writeStats(std::ostream &os) const
{
	char buf[128], output[256];
	strftime(buf, sizeof(buf), "%m/%d/%Y %I:%M:%S %p",
	         localtime((time_t*)&header.createdt));

	sprintf(output, "\n   creation date:\t\t%s\n"
	        "   number of items:\t\t%s\n"
	        "   number of blocks:\t\t%s\n"
	        "   number of internal pages:\t%s\n"
	        "   number of leaf pages:\t%s\n"
	        "   number of spill pages:\t%s\n"
	        "   current spill page:\t\t%s\n\n",
	        buf,
	        comma(header.numitems).c_str(),
	        comma(header.numblocks).c_str(),
	        comma(header.numinternal).c_str(),
	        comma(header.numleaf).c_str(),
	        comma(header.numspill).c_str(),
	        comma(header.currspill).c_str());

	os << output << std::flush;
}

/////////////////////////////////////////////////////////////////////////////
void BTree::Walk(PITEMWALKER pWalker)
{
	pageset.clear();
	WalkR(pWalker, pages[0], 0);
}

/////////////////////////////////////////////////////////////////////////////
void BTree::WalkR(PITEMWALKER pWalker, PPAGE h, uint8_t level)
{
	uint16_t j;
	if (ISLEAF(h)) { // leaf page
		ItemPtr pKey;
		for (j = 0; j < CELLS(h); j++) {
			pKey = ItemPtr(key(h, j));
			pWalker->Call(pKey.get());
		}
	} else { // internal page
		uint64_t nextpg;
		for (j = 0; j < CELLS(h); j++) {
			nextpg = NEXT(h, j);
			if (pageset.find(nextpg) != pageset.end())
				continue;
			pageset.insert(nextpg);
			if (!readpage(NEXT(h, j), level+1))
				continue;
			WalkR(pWalker, pages[level+1], level+1);
		}
	}
}
