/*
 * BLOCKIO.C
 * 
 * Block i/o interface
 */

#include <sys/stat.h>
#include <unistd.h>
#include "global.h"
#include "blockio.h"

/*
 * read a block 
 */
int readblock(FILE * fp, uint64_t blockno, void *buf)
{
	uint64_t offset = blockno * BLOCK_SIZE;

	if (fseek(fp, offset, SEEK_SET) == EOF)
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

	if (fseek(fp, offset, SEEK_SET) == EOF)
		return 0;	/* can't seek */

	if (fwrite(buf, BLOCK_SIZE, 1, fp) != 1)
		return 0;	/* can't write */

	return 1;
}

/* insert a block */
int insertblock(FILE * fp, const void *buf)
{
	if (fseek(fp, 0, SEEK_END) == EOF)
		return 0;	/* can't seek */

	if (fwrite(buf, BLOCK_SIZE, 1, fp) != 1)
		return 0;	/* can't write */

	return 1;
}
