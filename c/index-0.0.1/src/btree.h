/*
 * BTREE.H
 *
 * B-tree
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __BTREE_H__
#define __BTREE_H__

/*
 * item struct
 */
struct Item {
	uint64_t key;
	uint64_t val;
};

typedef struct Item Item_t;

#ifdef _MSCVER
#pragma pack(1)
#endif				/* _MSCVER */

/*
 * cell struct
 */
struct Cell {
	uint64_t next;		/* link to next subpage */
	uint64_t key;		/* key for a cell */
	uint64_t val;		/* value for a cell */
} PACK_ONE;

typedef struct Cell Cell_t;

/*
 * page header
 */
struct PageHeader {
	uint8_t flags;		/* page flags */
	uint64_t pageno;	/* page number */
	uint16_t cells;		/* number of cells on the page */
} PACK_ONE;

typedef struct PageHeader PageHeader_t;

/*
 * page definition
 */
struct Page {
	PageHeader_t header;	/* page header */
	Cell_t data[1];		/* page data */
} PACK_ONE;

typedef struct Page Page_t;

#ifdef _MSCVER
#pragma pack()
#endif				/* _MSCVER */

/*
 * maximum depth of tree
 */
enum { MAXDEPTH = 5 };

/*
 * maximum value
 */
enum { MAXV = -1 };

/*
 * btree definition
 */
struct BTree {
	uint64_t npages;	/* # of pages */
	FILE *fp;		/* file pointer */
	Page_t *pages[MAXDEPTH];	/* pages in memory */
	Page_t *frame[2];	/* spare frames for page split */
};

typedef struct BTree BTree_t;

BTree_t *btree_open(const char *filename, int mode);
void btree_close(BTree_t * tree);
void btree_put(BTree_t * tree, Item_t item);
uint64_t btree_get(BTree_t * tree, uint64_t k);

#endif				/* __BTREE_H__ */
