/////////////////////////////////////////////////////////////////////////////
//
// DISK.CPP : ADF disk definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#include "common.h"
#include "adf.h"
#include "adfexcept.h"
#include "adfutil.h"
#include "disk.h"

namespace { int32_t getDiskType(uint32_t size); }

/////////////////////////////////////////////////////////////////////////////
Disk::Disk()
 : type(0), cylinders(0), heads(0), sectors(0), size(0), fp(0), 
 readonly(false)
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
	memset(buf, 0, BSIZE);
	if (fwrite(buf, BSIZE, 1, pDisk->fp) != 1) {
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
	bootblock_t boot;
	pVol->readbootblock(&boot);

	// read root block for volume
	rootblock_t root;
	pVol->readrootblock(&root);

	// read bitmap for volume
	pVol->readbitmap(&root);

	return pVol;
}

/////////////////////////////////////////////////////////////////////////////
Volume *Disk::createFloppy(const char *name, uint32_t type)
{
	Volume *pVol = createVolume(0, FLOPPY_CYLINDERS, name, type);
	pVol->blocksize = BSIZE;
	pVol->mounted = true;
	volumes.push_back(pVol);	
	return pVol;
}

/////////////////////////////////////////////////////////////////////////////
Volume *Disk::createHardfile(const char *name, uint32_t type)
{
	Volume *pVol = createVolume(0, cylinders, name, type);
	pVol->blocksize = BSIZE;
	pVol->mounted = true;
	volumes.push_back(pVol);
	return pVol;
}

/////////////////////////////////////////////////////////////////////////////
Volume *Disk::createVolume(uint32_t start, uint32_t len, const char *name, 
	uint32_t type)
{
	VolumePtr pVol = VolumePtr(new Volume());

	pVol->disk = this;
	pVol->firstblock = heads * sectors * start;
	pVol->lastblock = (pVol->firstblock + (heads * sectors) * len) - 1;
	pVol->rootblock = (pVol->lastblock - pVol->firstblock + 1) / 2;

	pVol->currdir = pVol->rootblock;
	pVol->readonly = readonly;
	pVol->mounted = true;
	
	uint32_t namelen = min(MAXNAMELEN, strlen(name));
	pVol->name = string(name, namelen);

	bootblock_t boot;
	memset(&boot, 0, BOOTBLOCKSIZE);
	boot.type[3] = type;
	pVol->writebootblock(&boot);

	pVol->createbitmap();

	vector<uint32_t> blocks;
	blocks.resize(2);
	if (isDIRCACHE(type)) {
		pVol->getFreeBlocks(2, blocks);
	} else {
		pVol->getFreeBlocks(1, blocks);
	}

	rootblock_t root;
	memset(&root, 0, BSIZE);

	root.namelen = namelen;
	memcpy(root.diskname, pVol->name.c_str(), namelen);

	ADFDateTime dt = adfGetCurrentTime();
	adfTime2AmigaTime(dt, root.codays, root.comins, root.coticks);

	// dircache block 
    if (isDIRCACHE(type) ) {
        root.extension = 0;
        root.sectype = ST_ROOT; 
		pVol->createEmptyCache((entryblock_t*)&root, blocks[1]);
    }

	pVol->writerootblock(blocks[0], &root);
	
	pVol->writenewbitmap();

	pVol->updatebitmap();

	pVol->freebitmap();

	pVol->mounted = false;

	return pVol.release();
}

/////////////////////////////////////////////////////////////////////////////
void Disk::writeblock(uint32_t blockno, void *block)
{
	if (fp == NULL) throw ADFException("disk not open.");
	
	uint32_t offset = BSIZE * blockno;

	if (fseek(fp, offset, SEEK_SET) != 0)
		throw ADFException();

	if (fwrite(block, 1, BSIZE, fp) != BSIZE)
		throw ADFException();
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