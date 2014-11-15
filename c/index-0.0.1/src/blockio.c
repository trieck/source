/*
 * BLOCKIO.C
 *
 * Block i/o interface
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "blockio.h"

#ifdef _MSC_VER
extern int __cdecl _fseeki64(FILE * stream, __int64 offset, int whence);
#endif				/* _MSC_VER
 
/* read a block */
int readblock(FILE * fp, uint64_t blockno, void *buf)
{
    uint64_t offset = blockno * BLOCK_SIZE;

    if (FSEEK(fp, offset, SEEK_SET) == EOF)
        return 0;	/* can't seek */

    if (fread(buf, BLOCK_SIZE, 1, fp) != 1)
        return 0;	/* can't read */

    return 1;
}

/*
 * write a block
 */
int writeblock(FILE * fp, uint64_t blockno, const void *buf)
{
    uint64_t offset = blockno * BLOCK_SIZE;

    if (FSEEK(fp, offset, SEEK_SET) == EOF)
        return 0;	/* can't seek */

    if (fwrite(buf, BLOCK_SIZE, 1, fp) != 1)
        return 0;	/* can't write */

    return 1;
}

/* insert a block */
int insertblock(FILE * fp, const void *buf)
{
    if (FSEEK(fp, 0, SEEK_END) == EOF)
        return 0;	/* can't seek */

    if (fwrite(buf, BLOCK_SIZE, 1, fp) != 1)
        return 0;	/* can't write */

    return 1;
}
