/////////////////////////////////////////////////////////////////////////////
//
// DISK.CPP : ADF disk definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "adfexcept.h"
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
 : type(0), cylinders(0), heads(0), sectors(0), size(0), fp(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Disk::~Disk()
{
	unmount();
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
void Disk::unmount()
{
	VolumeList::iterator it = volumes.begin();
	for ( ; it != volumes.end(); it++) {
		Volume *pVol = *it;
		delete pVol;
	}

	volumes.erase(volumes.begin(), volumes.end());
}

/////////////////////////////////////////////////////////////////////////////
DiskPtr Disk::create(const char *filename, uint32_t cylinders, 
	uint32_t heads, uint32_t sectors)
{
	DiskPtr pDisk = DiskPtr(new Disk());

	if ((pDisk->fp = fopen(filename, "wb")) == NULL) {
		throw ADFException();
	}

	uint32_t offset = ((cylinders * heads * sectors)-1) * BSIZE;

	if (fseek(pDisk->fp, offset, SEEK_SET) != 0) {
		throw ADFException();
	}
	 
	uint8_t buf[BSIZE];
	if (fwrite(buf, BSIZE, 1, pDisk->fp) != BSIZE) {
		throw ADFException();
	}

	pDisk->close();

	if ((pDisk->fp = fopen(filename, "rb+")) == NULL) {
		throw ADFException();
	}

	pDisk->cylinders = cylinders;
    pDisk->heads = heads;
    pDisk->sectors = sectors;
    pDisk->size = cylinders * heads * sectors * BSIZE;
	pDisk->type = getDiskType(pDisk->size);

	return pDisk;
}

/////////////////////////////////////////////////////////////////////////////
DiskPtr Disk::open(const char *filename, const char *mode)
{
	DiskPtr pDisk = DiskPtr(new Disk());

	struct _stat buf;
	if (_stat(filename, &buf) == -1) {
		throw ADFException();
	}

	int32_t type;
	if ((type = getDiskType(buf.st_size)) == -1) {
		throw ADFException("unknown disk type.");
	}
	
	if ((pDisk->fp = fopen(filename, mode)) == NULL) {
		throw ADFException();
	}

	pDisk->filename = filename;
	pDisk->size = buf.st_size;
	pDisk->type = type;

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
	if (fp == NULL) throw ADFException("disk not open.");

	uint32_t offset = BSIZE * blockno;

	if (fseek(fp, offset, SEEK_SET) != 0)
		throw ADFException();

	if (fread(block, 1, BSIZE, fp) != BSIZE)
		throw ADFException();
}

/////////////////////////////////////////////////////////////////////////////
// mount disk
Volume *Disk::mount()
{
	Volume *pVol = new Volume();
	volumes.push_back(pVol);	

	pVol->mounted = true;
	pVol->firstblock = 0;
    pVol->lastblock = (cylinders * heads * sectors)-1;
    pVol->rootblock = (pVol->lastblock+1 - pVol->firstblock) / 2;
	pVol->currdir = pVol->rootblock;
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

	return pVol;
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