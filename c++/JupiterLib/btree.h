/////////////////////////////////////////////////////////////////////////////
//
//	BTREE.H : disk based b-tree
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BTREE_H__
#define __BTREE_H__

#pragma pack(1)

/////////////////////////////////////////////////////////////////////////////
typedef struct FileHeader {
    uint64_t magicno;		// magic number
    uint16_t size;			// size of file header
    uint32_t versionno;		// version number
    int32_t createdt;		// creation timestamp
    uint64_t numitems;		// number of items in b-tree
    uint64_t numblocks;		// number of blocks in b-tree
    uint64_t numinternal;	// number of internal pages
    uint64_t numleaf;		// number of leaf pages
    uint64_t numspill;		// number of spill pages
    uint64_t currspill;		// current spill page
    uint8_t pad[446];		// padding for sector alignment
} *PFILEHEADER;

/////////////////////////////////////////////////////////////////////////////
typedef struct PageHeader {
    uint8_t flags;			// page flags
    uint64_t pageno;		// page number
    uint16_t cells;			// number of cells on the page
    uint8_t pad[5];			// padding for alignment
} *PPAGEHEADER;

/////////////////////////////////////////////////////////////////////////////
typedef struct Cell {
    uint8_t flags;			// cell flags
    uint16_t index;			// index to data area
    uint16_t keylen;		// length of key
    uint16_t vallen;		// length of value (for leaf pages)
    uint64_t next;			// link to next subpage
    uint8_t pad[1];			// padding for alignment
} *PCELL;

/////////////////////////////////////////////////////////////////////////////
typedef struct SpillCellPtr {
    uint64_t pageno;		// page number of spill page
    uint16_t offset;		// offset into spill page
} *PSPILLCELLPTR;

/////////////////////////////////////////////////////////////////////////////
typedef struct SpillCell {
    uint32_t totallen;		// total length of datum
    uint16_t len;			// length of datum stored in this cell
    SpillCellPtr next;		// link where more data can be found
} *PSPILLCELL;

/////////////////////////////////////////////////////////////////////////////
typedef struct Page {
    PageHeader header;		// page header
    Cell data[1];			// page data
} *PPAGE;

#pragma pack()

/////////////////////////////////////////////////////////////////////////////
typedef ICallable<Item> IItemWalker;
typedef IItemWalker *PITEMWALKER;

/////////////////////////////////////////////////////////////////////////////
// IWalkableItem interface
class IWalkableItem {
public:
    virtual void Walk(PITEMWALKER) PURE;
};

/////////////////////////////////////////////////////////////////////////////
class BTree : public IWalkableItem {
// Construction / Destruction
public:
    BTree();
    virtual ~BTree();

// Interface
public:
    bool open(LPCSTR filename, OpenMode m);
    void close();

    void insert(PENTRY entry);
    bool append(PENTRY entry);
    PITEM search(PITEM key);
    bool exists(PITEM key);

    void writeStats(std::ostream &os) const;

    // IWalkableItem methods
    void Walk(PITEMWALKER pWalker);

// Implementation
private:
    /*
     * Maximum depth of the b-tree
     *
     * Currently this is set to 10.
     *
     * The average number of probes p is about
     * log_M(N).  So, we can have about M^p
     * items in the tree before we exceed the depth
     * limits of the tree.
     */
    enum { MAXDEPTH = 10 };

    /* maximum length of a key */
    enum { MAX_KEY_LEN = 256 };

    /* maximum length of a value */
    enum { MAX_VAL_LEN = 238 };

    void allocpages();
    void freepages();

    PPAGE mkpage();

    bool open(LPCSTR filename);
    bool readFH();
    bool insertFH();
    bool writeFH();
    bool flushFH();
    bool readpage(uint64_t page_no, uint8_t level);
    bool readpage(PPAGE h);
    bool writepage(PPAGE h);
    bool insertpage(PPAGE h);

    PPAGE insertR(PPAGE h, PENTRY entry, uint8_t level);
    void append(PPAGE h, uint16_t item, PITEM val);
    SpillCellPtr appendlarge(SpillCellPtr first, SpillCellPtr last,
                             PITEM val);

    PPAGE find(PITEM key, uint16_t &cell);
    PPAGE findR(PPAGE h, PITEM key, uint8_t level, uint16_t &cell);

    PPAGE split(PPAGE h);
    void reorder(PPAGE h);

    int compare(PITEM key, PPAGE h, uint16_t item);

    void store(PPAGE h, uint16_t item, PENTRY entry,
               PITEM newKey = NULL, uint64_t *next = NULL);
    void storeK(PPAGE h, uint16_t item, PITEM key);
    void storeV(PPAGE h, uint16_t item, PITEM val);

    void xfer(PPAGE dest, uint16_t m, PPAGE src, uint16_t n);
    void xferK(PPAGE dest, uint16_t m, PPAGE src, uint16_t n);
    void xferV(PPAGE dest, uint16_t m, PPAGE src, uint16_t n);

    void updateST(PPAGE h);
    SpillCellPtr nextspill();
    SpillCellPtr spill(LPCSTR data, uint32_t len);
    SpillCellPtr spill(PPAGE h, LPCSTR data, uint32_t len);

    PITEM key(PPAGE h, uint16_t item);
    PITEM value(PPAGE h, uint16_t item);
    PITEM largeval(PITEM pVal);

    void WalkR(PITEMWALKER pWalker, PPAGE h, uint8_t level);

    static const uint8_t magic_no[8];	// magic number
    static const uint16_t minorVer;		// version numbers
    static const uint16_t majorVer;

    blockio io;					// block i/o
    OpenMode mode;				// read-write mode
    PPAGE pages[MAXDEPTH];		// pages in memory
    PPAGE frame[2];				// spare frames for page split, spill
    FileHeader header;			// file header
    set<uint64_t> pageset;		// set of pages seen during walk
};
/////////////////////////////////////////////////////////////////////////////

#endif // __BTREE_H__
