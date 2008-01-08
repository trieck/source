/*
 * BLOCKIO.H
 * 
 * Block i/o interface
 * Copyright (c) 2008 Thomas A. Rieck
 */

#ifndef __BLOCKIO_H__
#define __BLOCKIO_H__

#define BLOCK_SIZE	(4096)

int readblock(FILE * fp, uint64_t blockno, void *buf);
int writeblock(FILE * fp, uint64_t blockno, const void *buf);
int insertblock(FILE * fp, const void *buf);

#endif				/* __BLOCKIO_H__ */
