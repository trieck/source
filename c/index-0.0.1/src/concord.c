/*
 * CONCORD.C
 *
 * Concordance
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "blockio.h"
#include "concord.h"

/*
 * Page type flags
 */

/*
 * file info page
 */
#define PTF_FILE		(1 << 0)

/*
 * Helper macros
 */
#define ISFILE(p)		(p->header.flags & PTF_FILE)

#define SETFILE(p)		(p->header.flags |= PTF_FILE)
#define SETTERM(p)		(p->header.flags &= ~PTF_FILE)

#define PAGENO(p)		(p->header.pageno)
#define NEXT(p)			(p->header.next)
#define ENTRIES(p)		(p->header.nentries)

/*
 * Maximum number of files on a page
 */
#define MAXFILES		\
	((BLOCK_SIZE - sizeof(ConcordHeader_t)) / sizeof(FileInfo_t))

/*
 * Maximum number of terms on a page
 */
#define MAXTERMS		\
	((BLOCK_SIZE - sizeof(ConcordHeader_t)) / sizeof(TermInfo_t))

/*
 * file info accessors
 */
#define FILENO(p, n)	(p->files[n].fileno)
#define FILENAME(p, n)	(p->files[n].filename)
#define FILELEN(p, n)	(p->files[n].filelen)

/*
 * term info accessors
 */
#define HASH(p, n)		(p->terms[n].hash)
#define TERM(p, n)		(p->terms[n].term)
#define TERMLEN(p, n)	(p->terms[n].len)

static int readpage(Concord_t * concord, uint64_t pageno);
static int writepage(Concord_t * concord, uint64_t pageno);
static uint64_t insertpage(Concord_t * concord);

/*
 * open concordance file returning instance
 */
Concord_t *concord_open(const char *filename, int mode)
{
    Concord_t *concord;
    FILE *fp;
    const char *pm;

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
     * allocate concordance struct
     */
    concord = (Concord_t *) malloc(sizeof(Concord_t));
    concord->fp = fp;

    memset(concord->buf, 0, BLOCK_SIZE);

    return concord;
}

/*
 * close concordance
 */
void concord_close(Concord_t * concord)
{
    if (concord->fp != NULL) {
        fclose(concord->fp);
    }

    free(concord);
}

/*
 * read a page
 */
int readpage(Concord_t * concord, uint64_t pageno)
{
    return readblock(concord->fp, pageno, concord->buf);
}

/*
 * write a page
 */
int writepage(Concord_t * concord, uint64_t pageno)
{
    return writeblock(concord->fp, pageno, concord->buf);
}

/* insert a page */
uint64_t insertpage(Concord_t * concord)
{
    ConcordHeader_t *header = (ConcordHeader_t *) concord->buf;
    header->pageno = concord->npages;

    if (!insertblock(concord->fp, concord->buf))
        return 0;

    return ++(concord->npages);
}

void concord_insert(Concord_t * concord, const char *term, uint32_t docid)
{
}