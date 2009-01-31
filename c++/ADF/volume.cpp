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
 rootblock(0), type(0), mounted(false), disk(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Volume::~Volume()
{
}

/////////////////////////////////////////////////////////////////////////////
void Volume::unmount()
{
	// TODO: unmount
	mounted = false;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readblock(uint32_t blockno, uint8_t *block)
{
	// TODO: check volume is mounted
	
	// translate logical sector to physical sector
    blockno = blockno + firstblock;

	// TODO: check blockno in range

	disk->readblock(blockno, block);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbootblock()
{
	uint8_t buf[BOOTBLOCKSIZE];
	bootblock_t *boot = (bootblock_t*)buf;

	readblock(0, buf);
	readblock(1, buf+BSIZE);

#ifdef LITTLE_ENDIAN
	boot->checksum = swap_endian(boot->checksum);
	boot->rootblock = swap_endian(boot->rootblock);
#endif	// LITTLE_ENDIAN

	if (strncmp("DOS", boot->type, 3) != 0) {
		;	// TODO: bad disk
	}

	if (boot->code[0] != 0 && bootsum(buf) != boot->checksum) {
		;	// TODO : bad checksum
	}

	type = boot->type[3];
	if (isFFS(type)) {
		dblocksize = BSIZE;
	} else {
		dblocksize = OFS_DBSIZE;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readrootblock()
{
	uint8_t buf[BSIZE];
	rootblock_t *root = (rootblock_t*)buf;
	readblock(rootblock, buf);

	// copy diskname into volume
	name = string(root->diskname, root->namelen);

	// TODO: read bitmap

	//nBlock = vol->lastBlock - vol->firstBlock +1 - 2;
	//adfReadBitmap( vol, nBlock, &root );
}