/*
 * CONCORD.H
 * 
 * Concordance
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __CONCORD_H__
#define __CONCORD_H__

#include "inverter.h"

/*
 * concordance page header 
 */
struct ConcordHeader {
	uint8_t flags;		/* page flags */
	uint64_t pageno;	/* page number */
	uint64_t next;		/* link to next page */
	uint16_t nentries;	/* number of entries on the page */
} PACK_ONE;

typedef struct ConcordHeader ConcordHeader_t;

/*
 * file info struct 
 */
struct FileInfo {
	uint16_t fileno;	/* file number */
	int8_t filename[BSIZE];	/* file name */
	uint8_t filelen;	/* length of file name */
} PACK_ONE;

typedef struct FileInfo FileInfo_t;

/*
 * file info page 
 */
struct FileInfoPage {
	ConcordHeader_t header;	/* page header */
	FileInfo_t files[1];	/* file information */
} PACK_ONE;

typedef struct FileInfoPage FileInfoPage_t;

/*
 * term info struct 
 */
struct TermInfo {
	uint64_t hash;		/* 64-bit hash of term */
	int8_t term[BSIZE];	/* term */
	uint8_t len;		/* length of term */
} PACK_ONE;

typedef struct TermInfo TermInfo_t;

/*
 * term info page 
 */
struct TermInfoPage {
	ConcordHeader_t header;	/* page header */
	TermInfo_t terms[1];	/* term information */
} PACK_ONE;

typedef struct TermInfoPage TermInfoPage_t;

/*
 * concordance definition 
 */
struct Concord {
	uint64_t npages;	/* # of pages */
	FILE *fp;		/* file pointer */
	uint8_t buf[BLOCK_SIZE];	/* page buffer */
};

typedef struct Concord Concord_t;

Concord_t *concord_open(const char *filename, int mode);
void concord_close(Concord_t * concord);
void concord_insert(Concord_t * concord, const char *term, uint32_t docid);

#endif				/* __CONCORD_H__ */
