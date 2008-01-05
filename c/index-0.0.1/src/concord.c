/*
 * CONCORD.C
 * 
 * Concordance
 */

#include <sys/stat.h>
#include <unistd.h>

#include "global.h"
#include "concord.h"

/* Size of a disk page */
#define PAGE_SIZE		(4096)

/* Page type flags */

/* file info page */
#define PTF_FILE		(1 << 0)

/* Helper macros */
#define ISFILE(p)		(p->header.flags & PTF_FILE)

#define SETFILE(p)		(p->header.flags |= PTF_FILE)
#define SETTERM(p)		(p->header.flags &= ~PTF_FILE)

#define PAGENO(p)		(p->header.pageno)
#define NEXT(p)			(p->header.next)
#define ENTRIES(p)		(p->header.nentries)

/* Maximum number of files on a page*/
#define MAXFILES		\
	((PAGE_SIZE - sizeof(ConcordHeader_t)) / sizeof(FileInfo_t))
	
/* Maximum number of terms on a page*/
#define MAXTERMS		\
	((PAGE_SIZE - sizeof(ConcordHeader_t)) / sizeof(TermInfo_t))

/* file info accessors */
#define FILENO(p, n)	(p->files[n].fileno)
#define FILENAME(p, n)	(p->files[n].filename)
#define FILELEN(p, n)	(p->files[n].filelen)

/* term info accessors */
#define HASH(p, n)		(p->terms[n].hash)
#define TERM(p, n)		(p->terms[n].term)
#define TERMLEN(p, n)	(p->terms[n].len)

