/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.CPP : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "adfutil.h"
#include "disk.h"
#include "volume.h"

/////////////////////////////////////////////////////////////////////////////
Volume::Volume()
: blocksize(0), bitmapsize(0), dblocksize(0), firstblock(0), lastblock(0), 
 rootblock(0), type(0), mounted(false), bmtbl(0), bmblocks(0), disk(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Volume::~Volume()
{
	unmount();
}

/////////////////////////////////////////////////////////////////////////////
void Volume::unmount()
{
	freebitmap();
    mounted = false;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::freebitmap()
{
	if (bmtbl != NULL) {
		for (uint32_t i = 0; i < bitmapsize; i++) {
			free(bmtbl[i]);
		}

		free(bmtbl);
		bmtbl = NULL;
	}

	bitmapsize = 0;

	if (bmblocks != NULL) {
        free(bmblocks);
		bmblocks = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readblock(uint32_t blockno, void *block)
{
	// TODO: check volume is mounted
	
	// translate logical sector to physical sector
    blockno = blockno + firstblock;

	// TODO: check blockno in range

	disk->readblock(blockno, block);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbootblock(bootblock_t *boot)
{
	uint8_t buf[BOOTBLOCKSIZE];

	readblock(0, buf);
	readblock(1, buf+BSIZE);

	memcpy(boot, buf, BOOTBLOCKSIZE);
#ifdef LITTLE_ENDIAN
	boot->checksum = swap_endian(boot->checksum);
	boot->rootblock = swap_endian(boot->rootblock);
#endif	// LITTLE_ENDIAN

	if (strncmp("DOS", boot->type, 3) != 0) {
		;	// TODO: bad disk
	}

	if (boot->code[0] != 0 && bootsum(buf) != boot->checksum) {
		;	// TODO : bad checksum
		fprintf(stderr, "boot block checksum mismatch.\n");
		exit(1);
	}

	type = boot->type[3];
	if (isFFS(type)) {
		dblocksize = BSIZE;
	} else {
		dblocksize = OFS_DBSIZE;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readrootblock(rootblock_t *root)
{
	uint8_t buf[BSIZE];
	readblock(rootblock, buf);

	memcpy(root, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	root->type = swap_endian(root->type);
	root->hkey = swap_endian(root->hkey);
	root->highseq = swap_endian(root->highseq);
	root->tblsize = swap_endian(root->tblsize);
	root->firstdata = swap_endian(root->firstdata);
	root->checksum = swap_endian(root->checksum);

	uint32_t i;
	for (i = 0; i < HT_SIZE; i++)
		root->tbl[i] = swap_endian(root->tbl[i]);

	root->bmflag = swap_endian(root->bmflag);
	for (i = 0; i < BM_SIZE; i++)
		root->bmpages[i] = swap_endian(root->bmpages[i]);

	root->bmext = swap_endian(root->bmext);
	root->cdays = swap_endian(root->cdays);
	root->cmins = swap_endian(root->cmins);
	root->cticks = swap_endian(root->cticks);
	root->days = swap_endian(root->days);
	root->mins = swap_endian(root->mins);
	root->ticks = swap_endian(root->ticks);
	root->codays = swap_endian(root->codays);
	root->comins = swap_endian(root->comins);
	root->coticks = swap_endian(root->coticks);
	root->nextsamehash = swap_endian(root->nextsamehash);
	root->parent = swap_endian(root->parent);
	root->extension = swap_endian(root->extension);
	root->sectype = swap_endian(root->sectype);
#endif // LITTLE_ENDIAN
	
	if (root->type != T_HEADER && root->sectype != ST_ROOT) {
		fprintf(stderr, "bad root block.\n");
		exit(1);
    }

	if (root->checksum != adfchecksum(buf, 20, BSIZE)) {
		fprintf(stderr, "invalid checksum.\n");
		exit(1);
	}

	// copy diskname into volume
	name = string(root->diskname, root->namelen);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbitmap(rootblock_t *root)
{
	freebitmap();

	// TODO: no idea how this works yet
	uint32_t nbits = BM_MAPSIZE * BM_BLOCKS_ENTRY;

	uint32_t blockno = lastblock - firstblock + 1 - 2;
	uint32_t mapsize =  blockno / nbits;

    if (blockno % nbits != 0)
        mapsize++;	// round up?

	bitmapsize = mapsize;
	bmtbl = (bitmapblock_t**) malloc(sizeof(bitmapblock_t*) * mapsize);
	// TODO: alloc error

	bmblocks = (uint32_t*) malloc(sizeof(uint32_t) * mapsize);
	// TODO: alloc error

	uint32_t i;
	for (i = 0; i < mapsize; i++) {
        bmtbl[i] = (bitmapblock_t*)malloc(sizeof(bitmapblock_t));
		// TODO: alloc error
	}

	for (i = 0; i < BM_SIZE && root->bmpages[i] != 0; i++) {
		bmblocks[i] = root->bmpages[i];

		// TODO: check valid sector
		if (!isValidSector(bmblocks[i])) {
			fprintf(stderr, "invalid sector.\n");
			exit(1);
		}


		readbmblock(bmblocks[i], bmtbl[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbmblock(uint32_t blockno, bitmapblock_t *bm)
{
	uint8_t buf[BSIZE];

	readblock(blockno, buf);
	memcpy(bm, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	bm->checksum = swap_endian(bm->checksum);
	uint32_t i;
	for (i = 0; i < BM_MAPSIZE; i++)
		bm->map[i] = swap_endian(bm->map[i]);
#endif

	if (bm->checksum != adfchecksum(buf, 0, BSIZE)) {
		fprintf(stderr, "invalid checksum.\n");
		exit(1);
	}
}
