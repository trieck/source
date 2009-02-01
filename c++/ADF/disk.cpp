/////////////////////////////////////////////////////////////////////////////
//
// DISK.CPP : ADF disk definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "disk.h"

#define FLOPPY_CYLINDERS	(80)
#define FLOPPY_HEADS		(2)
#define FLOPDD_SECTORS		(11)
#define FLOPHD_SECTORS		(FLOPDD_SECTORS*2)

#define FLOPDD_SIZE			\
	(BSIZE*FLOPDD_SECTORS*FLOPPY_HEADS*FLOPPY_CYLINDERS)

#define FLOPHD_SIZE			\
	(BSIZE*FLOPHD_SECTORS*FLOPPY_HEADS*FLOPPY_CYLINDERS)

namespace { int32_t getDiskType(uint32_t size); }

/////////////////////////////////////////////////////////////////////////////
Disk::Disk()
 : cylinders(0), heads(0), sectors(0), size(0), fp(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Disk::~Disk()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Disk::close()
{
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
DiskPtr Disk::open(const char *filename)
{
	Disk *pDisk = new Disk();

	struct _stat buf;
	int result = _stat(filename, &buf);

	// TODO: result error

	int32_t type = getDiskType(buf.st_size);
	
	// TODO: type error

	pDisk->fp = fopen(filename, "rb");

	// TODO : open error

	pDisk->filename = filename;
	pDisk->size = buf.st_size;
	
	switch (type) {
		case DISKTYPE_FLOPDD:
			pDisk->cylinders = FLOPPY_CYLINDERS;
			pDisk->heads = FLOPPY_HEADS;
			pDisk->sectors = FLOPDD_SECTORS;
			break;
		case DISKTYPE_FLOPHD:
			pDisk->cylinders = FLOPPY_CYLINDERS;
			pDisk->heads = FLOPPY_HEADS;
			pDisk->sectors = FLOPHD_SECTORS;
			break;
		default:	// DISKTYPE_HARDFILE
			pDisk->cylinders = pDisk->size / BSIZE;
			pDisk->heads = 1;
			pDisk->sectors = 1;
			// TODO: 
			break;
	}

	return DiskPtr(pDisk);
}

/////////////////////////////////////////////////////////////////////////////
// read a physical block from disk
void Disk::readblock(uint32_t blockno, void *block)
{
	// TODO: not open

	uint32_t offset = BSIZE * blockno;

	int result = fseek(fp, offset, SEEK_SET);

	// TODO: seek error

	result = fread(block, 1, BSIZE, fp);

	// TODO: read error
}

/////////////////////////////////////////////////////////////////////////////
// mount disk
VolumePtr Disk::mount()
{
	Volume *pVol = new Volume();

	// TODO: floppy only

	pVol->firstblock = 0;
    pVol->lastblock = (cylinders * heads * sectors)-1;
    pVol->rootblock = (pVol->lastblock+1 - pVol->firstblock) / 2;
    pVol->blocksize = BSIZE;
	pVol->disk = this;

	// read boot block for volume
	uint8_t buf[BOOTBLOCKSIZE];
	bootblock_t *boot = (bootblock_t*)buf;
	pVol->readbootblock(boot);

	// read root block for volume
	rootblock_t *root = (rootblock_t*)buf;
	pVol->readrootblock(root);

	// read bitmap for volume
	pVol->readbitmap(root);

	// TODO: add to list of disks mounted volumes

	pVol->mounted = true;

	return VolumePtr(pVol);
}

namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
int32_t getDiskType(uint32_t size)
{
	if ((size == FLOPDD_SIZE) ||
		(size == FLOPDD_SIZE+1) ||
        (size == FLOPDD_SIZE+2) ||
		(size == FLOPDD_SIZE+3)) {
        return DISKTYPE_FLOPDD;
	} else if (size == FLOPHD_SIZE) {
        return DISKTYPE_FLOPHD;
	} else if (size > FLOPHD_SIZE) {
        return DISKTYPE_HARDFILE;
	}

	return -1;
}

}	// anonymous