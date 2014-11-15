/*
 * BTREE.C
 *
 * B-tree
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "btree.h"
#include "blockio.h"

/*
 * Page type flags
 */
#define PTF_LEAF		(1 << 0)

/*
 * Helper macros
 */
#define ISLEAF(p)		(p->header.flags & PTF_LEAF)
#define SETLEAF(p)		(p->header.flags |= PTF_LEAF)
#define SETNONLEAF(p)	(p->header.flags &= ~PTF_LEAF)
#define PAGENO(p)		(p->header.pageno)
#define CELLS(p)		(p->header.cells)

/*
 * Maximum number of cells on a page, must be even to split a page
 */
#define MAXCELLS		\
	((BLOCK_SIZE - sizeof(PageHeader_t)) / sizeof(Cell_t) & ~1)

/*
 * Cell accessors
 */
#define CELL(p, n)		(p->data[n])
#define KEY(p, n)		(p->data[n].key)
#define VAL(p, n)		(p->data[n].val)
#define NEXT(p, n)		(p->data[n].next)

/*
 * Allocate a new page
 */
#define MKPAGE()	((Page_t*)calloc(BLOCK_SIZE, sizeof(uint8_t)))

/*
 * Free an allocated page
 */
#define FREEPAGE(p)	\
	do {			\
		free(p);	\
		p = NULL;	\
	} while(0)

static int readpage(BTree_t * tree, uint64_t pageno, uint32_t level);
static int writepage(BTree_t * tree, Page_t * page);
static uint64_t insertpage(BTree_t * tree, Page_t * page);
static uint64_t searchR(BTree_t * tree, Page_t * h, uint64_t k,
                        uint32_t level);
static Page_t *insertR(BTree_t * tree, Page_t * h, Item_t x,
                       uint32_t level);
static Page_t *split(BTree_t * tree, Page_t * h);

/*
 * open a file, returning a btree instance
 */
BTree_t *btree_open(const char *filename, int mode)
{
    BTree_t *tree;
    FILE *fp;
    struct stat buf;
    const char *pm;
    uint8_t i;

    /*
     * check for valid open mode
     */
    switch (mode) {
    case OM_READ_ONLY:
        pm = "r";
        break;
    case OM_WRITE:
        pm = "w";
        break;
    default:		/* unknown */
        return NULL;
    }

    /*
     * open underlying file
     */
    if ((fp = fopen(filename, pm)) == NULL)
        return NULL;	/* unable to open file */

    /*
     * stat underlying file
     */
    if (fstat(fileno(fp), &buf) == -1)
        return NULL;	/* can't stat file */

    /*
     * allocate tree struct
     */
    tree = (BTree_t *) malloc(sizeof(BTree_t));
    tree->fp = fp;

    /*
     * allocate pages
     */
    for (i = 0; i < MAXDEPTH; i++) {
        tree->pages[i] = MKPAGE();
    }

    tree->frame[0] = MKPAGE();
    tree->frame[1] = MKPAGE();
    tree->npages = buf.st_size / BLOCK_SIZE;

    if (buf.st_size != 0) {
        readpage(tree, 0, 0);
    } else {
        SETLEAF(tree->pages[0]);	/* set root page to leaf */
        writepage(tree, tree->pages[0]);
    }

    return tree;
}

/*
 * close btree, freeing instance
 */
void btree_close(BTree_t * tree)
{
    uint8_t i;

    if (tree->fp != NULL) {
        fclose(tree->fp);
        tree->fp = NULL;
    }

    for (i = 0; i < MAXDEPTH; i++) {
        FREEPAGE(tree->pages[i]);
    }

    FREEPAGE(tree->frame[0]);
    FREEPAGE(tree->frame[1]);

    free(tree);
}

/*
 * read a page
 */
int readpage(BTree_t * tree, uint64_t pageno, uint32_t level)
{
    return readblock(tree->fp, pageno, tree->pages[level]);
}

/*
 * write a page
 */
int writepage(BTree_t * tree, Page_t * page)
{
    return writeblock(tree->fp, PAGENO(page), page);
}

/*
 * insert a page
 */
uint64_t insertpage(BTree_t * tree, Page_t * h)
{
    PAGENO(h) = tree->npages;

    if (!insertblock(tree->fp, h))
        return 0;

    return ++(tree->npages);
}

/*
 * search tree recursively
 */
uint64_t searchR(BTree_t * tree, Page_t * h, uint64_t k, uint32_t level)
{
    int j;

    if (ISLEAF(h)) {	// leaf page
        for (j = 0; j < CELLS(h); j++) {
            if (KEY(h, j) == k)
                return VAL(h, j);
        }
    } else {		// internal page
        for (j = 0; j < CELLS(h); j++) {
            if ((j + 1 == CELLS(h) || k < KEY(h, j + 1))) {
                if (!readpage(tree, NEXT(h, j), level + 1))
                    return MAXV;
                return searchR(tree,
                               tree->pages[level + 1], k,
                               level + 1);
            }
        }
    }

    return MAXV;
}

/*
 * insert item recursively
 */
Page_t *insertR(BTree_t * tree, Page_t * h, Item_t x, uint32_t level)
{
    int i, j;
    uint64_t v = x.key;
    Cell_t t;
    t.key = v;
    t.val = x.val;

    if (ISLEAF(h)) {	// leaf page
        for (j = 0; j < CELLS(h); j++) {
            if (v < KEY(h, j))
                break;
        }
    } else {		// internal page
        for (j = 0; j < CELLS(h); j++) {
            if ((j + 1 == CELLS(h) || v < KEY(h, j + 1))) {
                Page_t *u;
                if (!readpage
                        (tree, NEXT(h, j++), level + 1))
                    return 0;
                u = insertR(tree, tree->pages[level + 1],
                            x, level + 1);
                if (u == 0)
                    return 0;
                t.key = KEY(u, 0);
                t.next = PAGENO(u);
                break;
            }
        }
    }

    for (i = CELLS(h); i > j; i--)
        CELL(h, i) = CELL(h, i - 1);
    CELL(h, j) = t;
    if (++CELLS(h) < MAXCELLS) {
        writepage(tree, h);	// write dirty page
        return 0;
    }

    return split(tree, h);
}

/*
 * split a page
 */
Page_t *split(BTree_t * tree, Page_t * h)
{
    Page_t *t = tree->frame[0];
    int j;

    memset(t, 0, BLOCK_SIZE);

    t->header.flags = h->header.flags;

    for (j = 0; j < MAXCELLS / 2; j++)
        CELL(t, j) = CELL(h, MAXCELLS / 2 + j);

    CELLS(h) = MAXCELLS / 2;
    CELLS(t) = MAXCELLS / 2;

    writepage(tree, h);
    insertpage(tree, t);

    return t;
}

/*
 * put item in tree
 */
void btree_put(BTree_t * tree, Item_t item)
{
    Page_t *u, *t;
    if ((u = insertR(tree, tree->pages[0], item, 0)) == 0)
        return;

    /*
     * The basic idea with the root page split is that we create a new
     * internal root page t with 2 links. The first link points to
     * the old root page and the second link points to the page that caused
     * the split.  The height of the tree is increased by one.
     */
    t = tree->frame[1];
    memset(t, 0, BLOCK_SIZE);

    insertpage(tree, tree->pages[0]);	// relocate old root page

    SETNONLEAF(t);
    CELLS(t) = 2;
    KEY(t, 0) = KEY(tree->pages[0], 0);
    KEY(t, 1) = KEY(u, 0);
    NEXT(t, 0) = PAGENO(tree->pages[0]);
    NEXT(t, 1) = PAGENO(u);

    memcpy(tree->pages[0], t, BLOCK_SIZE);
    writepage(tree, tree->pages[0]);
}

/*
 * get item from tree
 */
uint64_t btree_get(BTree_t * tree, uint64_t k)
{
    return searchR(tree, tree->pages[0], k, 0);
}
