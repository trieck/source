/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.CPP : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "adf.h"
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

