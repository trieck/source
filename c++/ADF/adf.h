/////////////////////////////////////////////////////////////////////////////
//
// ADF.H : Amiga Disk File system
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#ifndef __ADF_H__
#define __ADF_H__

#define LITTLE_ENDIAN	1			/* for little endian machines */

#define BSIZE			(512)		/* logical block size */
#define OFS_DBSIZE		(488)		/* OFS data block size */
#define BOOTBLOCKSIZE	(BSIZE*2)	/* boot block size */

/////////////////////////////////////////////////////////////////////////////
// file system types

#define FSTYPE_FFS         1	/* Fast File System */
#define FSTYPE_INTL        2	/* International File System */
#define FSTYPE_DIRCACHE    4	/* Directory Cache File System */

#define isFFS(c)           ((c)&FSTYPE_FFS)
#define isOFS(c)           (!((c)&FSTYPE_FFS))
#define isINTL(c)          ((c)&FSTYPE_INTL)
#define isDIRCACHE(c)      ((c)&FSTYPE_DIRCACHE)

/////////////////////////////////////////////////////////////////////////////
// disk types
#define DISKTYPE_FLOPDD 	1
#define DISKTYPE_FLOPHD 	2
#define DISKTYPE_HARDFILE 	3

/////////////////////////////////////////////////////////////////////////////
// block constants

#define HT_SIZE				72	/* hash table size */
#define BM_SIZE				25	/* bitmap size */
#define MAX_DATABLK			72	/* maximum datablock size */

#define MAXNAMELEN			30	/* maximum name length */
#define MAXCOMMLEN			79	/* maximum comment length */

/////////////////////////////////////////////////////////////////////////////
// block primary and secondary types

#define T_HEADER			2	/* header block type */
#define T_DATA				8	/* data block type */
#define T_LIST				16	/* list block type */
#define T_DIRC				33	/* directory cache block type */

#define ST_ROOT				1	/* root secondary block type */
#define ST_DIR				2	/* directory secondary block type */
#define ST_LSOFT			3	/* soft link secondary block type */
#define ST_LDIR				4	/* directory link secondary block type */
#define ST_FILE				-3	/* file secondary block type */
#define ST_LFILE			-4	/* file link secondary block type */

/////////////////////////////////////////////////////////////////////////////
// block structures

/////////////////////////////////////////////////////////////////////////////
// boot block structure
struct bootblock_t {
	char type[4];			/* 'D''O''S' + flags */
	uint32_t checksum;		/* checksum */
	uint32_t rootblock;		/* rootblock = 880 for DD and HD */
	uint8_t code[1];		/* bootblock code */
};

/////////////////////////////////////////////////////////////////////////////
// root block structure
struct rootblock_t {
	int32_t type;					/* primary block type = T_HEADER */
	int32_t hkey;					/* UNUSED */
	int32_t highseq;				/* UNUSED */
	int32_t tblsize;				/* hash table size (= BSIZE/4 - 56), floppy disk = 0x48 */
	int32_t firstdata;				/* UNUSED */
	uint32_t checksum;				/* root block checksum */
	int32_t tbl[HT_SIZE];			/* hash table */
	int32_t bmflag;					/* bitmap flag, -1 means VALID */
	int32_t bmpages[BM_SIZE];		/* bitmap block pointers */
	int32_t bmext;					/* first bitmap extension block (hard disks only) */
	int32_t cdays;					/* filesystem creation date: days since 1 jan 78 */
	int32_t cmins;					/* filesystem creation time: minutes past midnight */
	int32_t cticks;					/* filesystem creation time: 1/50 sec past last minute */
	int8_t namelen;					/* volume name length */
	char diskname[MAXNAMELEN+1];	/* volume name */
	int8_t r2[8];					/* RESERVED (= 0) */
	int32_t days;					/* last root alteration date: days since 1 jan 78 */
	int32_t mins;					/* hours and minutes in minutes past midnight */
	int32_t ticks;					/* ticks (1/50 sec) past last minute */
	int32_t codays;					/* last disk alteration date: days since 1 jan 78 */
	int32_t comins;					/* hours and minutes in minutes past midnight */
	int32_t coticks;				/* ticks (1/50 sec) past last minute */
	int32_t nextsamehash;			/* UNUSED (= 0) */
	int32_t parent;					/* UNUSED (= 0) */
	int32_t extension;				/* FFS: first directory cache block, 0 otherwise */
	int32_t sectype;				/* block secondary type = ST_ROOT */
};

/////////////////////////////////////////////////////////////////////////////
// file header block structure
struct fileheader_t {
	int32_t type;						/* primary block type = T_HEADER */
	int32_t key;						/* current block number */
	int32_t nblocks;					/* number of data blocks in this header block */
	int32_t datasize;					/* UNUSED (= 0) */
	int32_t firstblock;					/* pointer to first data block */
	uint32_t checksum;					/* checksum */
	int32_t datablocks[MAX_DATABLK];	/* data block pointers (first at BSIZE-204). size = (BSIZE/4)-56 */
	int32_t r1;							/* RESERVED (= 0) */
	int32_t r2;							/* RESERVED (= 0) */
	int32_t access;						/* protection flags (set to 0 by default) */
	uint32_t fsize;						/* file size in bytes */
	uint8_t commlen;					/* file comment length */
	char comment[MAXCOMMLEN+1];			/* comment (max. 79 chars permitted) */
	int8_t r3[13];						/* RESERVED (= 0) */
	int32_t	days;						/* date of last change (days since 1 jan 78) */
	int32_t mins;						/* time of last change (mins since midnight) */
	int32_t ticks;						/* time of last change (1/50ths of a second since last min) */
	uint8_t namelen;					/* filename length */
	char filename[MAXNAMELEN+1];		/* filename (max. 30 chars permitted) */
	int32_t r4;							/* RESERVED (= 0) */
	int32_t real;						/* UNUSED (= 0) */
	int32_t nextlink;					/* linked list of hard link (first = newest) */
	int32_t r5[5];						/* RESERVED (= 0) */
	int32_t nexthash;					/* next entry with same hash */
	int32_t parent;						/* parent directory */
	int32_t extension;					/* pointer to first extension block */
	int32_t sectype;					/* secondary type = ST_FILE */
};

/////////////////////////////////////////////////////////////////////////////
// file header extension block structure
struct fileext_t {
	int32_t type;						/* primary block type = T_LIST */
	int32_t key;						/* self pointer */
	int32_t highseq;					/* number of data block pointers stored */
	int32_t datasize;					/* UNUSED (= 0) */
	int32_t firstdata;					/* UNUSED (= 0) */
	uint32_t checksum;					/* checksum */
	int32_t blocks[MAX_DATABLK];		/* data block pointer (first at BSIZE-204). size = (BSIZE/4) - 56 */
	int32_t	r[45];						/* RESERVED	*/
	int32_t info;						/* UNUSED (= 0) */
	int32_t nexthash;					/* UNUSED (= 0) */
	int32_t parent;						/* file header block */
	int32_t extension;					/* next file header extension block. 0 for the last */
	int32_t sectype;					/* secondary block type = ST_FILE */
};

/////////////////////////////////////////////////////////////////////////////
// directory block structure
struct dirblock_t {
	int32_t	type;						/* primary block type = T_HEADER */
	int32_t	key;						/* self pointer */
	int32_t	highseq;					/* UNUSED (= 0 */
	int32_t	tblsize;					/* UNUSED (= 0) */
	int32_t	r1;							/* RESERVED (= 0) */
	uint32_t checksum;					/* checksum */
	int32_t	tbl[HT_SIZE];				/* hash table (entry block number). size = (BSIZE/4) - 56 */
	int32_t	r2[2];						/* RESERVED */
	int32_t	access;						/* protection flags (set to 0 by default) */
	int32_t	r4;							/* RESERVED (= 0) */
	int8_t commlen;						/* directory comment length */
	char comment[MAXCOMMLEN+1];			/* comment (max. 79 chars permitted) */
	int8_t r5[13];						/* UNUSED (= 0) */
	int32_t	days;						/* last access date (days since 1 jan 78) */
	int32_t	mins;						/* last access time (mins since midnight) */
	int32_t	ticks;						/* last access time (1/50ths of a second since last min) */
	int8_t namelen;						/* directory name length */
	char dirname[MAXNAMELEN+1];			/* directory name (max. 30 chars permitted) */
	int32_t	r6;							/* RESERVED (=0) */
	int32_t	real;						/* UNUSED (=0) */
	int32_t	nextlink;					/* FFS: linked list of hard links (first = newest) */
	int32_t	r7[5];						/* RESERVED (=0) */
	int32_t	nextsamehash;				/* next entry pointer with same hash */
	int32_t	parent;						/* parent directory */
	int32_t	extension;					/* FFS: first directory cache block */
	int32_t	sectype;					/* secondary type = ST_DIR */
};

/////////////////////////////////////////////////////////////////////////////
// old file system data block structure
struct ofsblock_t {
	int32_t type;		/* primary block type = T_DATA */ 
	int32_t key;		/* pointer to file header block */
	int32_t seqnum;		/* file data block number (first is 1) */
	int32_t size;		/* data size (<= BSIZE-24) */
	int32_t next;		/* next data block (0 for last) */
	uint32_t checksum;	/* checksum */
	uint8_t data[1];	/* file data  */
};	

/////////////////////////////////////////////////////////////////////////////
// bitmap block structure
struct bitmapblock_t {
	uint32_t checksum;	/* checksum */
	uint32_t map[127];	/* map */
};

/////////////////////////////////////////////////////////////////////////////
// bitmap extension block structure
struct bitmapextblock_t {
	int32_t pages[127];	/* bitmap block pointers */
	int32_t next;		/* next block (0 for last) */
};

/////////////////////////////////////////////////////////////////////////////
// link block structure
struct linkblock_t {
	int32_t type;				/* primary block type = T_HEADER */
	int32_t key;				/* self pointer */
	int32_t r1[3];				/* RESERVED (= 0) */
	uint32_t checksum;			/* checksum */
	char realName[64];			/* Hard Link: UNUSED (= 0). Size = (BSIZE/4) - 54. For floppy disk = 74.
								 * Soft Link: Path name to referenced object. Size = (BSIZE - 224) - 1).
                				 * For floppy disk = 288 - 1 chars */
	int32_t r2[83];				/* RESERVED (= 0) */
	int32_t	days;				/* last access date (days since 1 jan 78) */
	int32_t mins;				/* last access time (mins since midnight) */
	int32_t ticks;				/* last access time (1/50ths of a second since last min) */
	uint8_t namelen;			/* link name length */
	char name[MAXNAMELEN+1];	/* link name */
	int32_t r3;					/* RESERVED (= 0) */
	int32_t realentry;			/* Hard Link: FFS: pointer to "real" file or directory.
								 * Soft Link: UNUSED (= 0) */
	int32_t next;				/* Hard Link: FFS : linked list of hardlinks (first = newest).
								 * Soft Link: UNUSED (= 0) */
	int32_t r4[5];				/* RESERVED (= 0) */
	int32_t nextsamehash;		/* next entry ptr with same hash */
	int32_t parent;				/* parent directory */
	int32_t r5;					/* RESERVED (= 0) */
	int32_t sectype;			/* secondary block type:
								 * Hard Link: ST_LINKFILE or T_LINKDIR.
								 * Soft Link: ST_SOFTLINK */
};

/////////////////////////////////////////////////////////////////////////////
// directory cache block structure
struct dircacheblock_t {
	int32_t type;				/* T_DIRC */
	int32_t key;				/* self pointer */
	int32_t parent;				/* parent directory */
	int32_t nrecs;				/* number of directory entry records in this block */
	int32_t next;				/* directory cache linked list */
	uint32_t checksum;			/* checksum */
	uint8_t records[1];			/* list of entries */
};

#endif // __ADF_H__