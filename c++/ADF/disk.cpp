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

	// TODO: floppy only
	pDisk->cylinders = 80;
	pDisk->heads = 2;
	pDisk->sectors = type == DISKTYPE_FLOPDD ? 11 : 22;

	return DiskPtr(pDisk);
}

/////////////////////////////////////////////////////////////////////////////
// read a physical block from disk
void Disk::readblock(uint32_t blockno, uint8_t *block)
{
	// TODO: not open

	uint32_t offset = BSIZE * blockno;

	int result = fseek(fp, offset, SEEK_SET);

	// TODO: seek error

	result = fread(block, 1, BSIZE, fp);

	// TODO: read error
	


}

namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
int32_t getDiskType(uint32_t size)
{
	if ((size == 512*11*2*80) ||
		(size == 512*11*2*81) ||
        (size == 512*11*2*82) ||
		(size == 512*11*2*83)) {
        return DISKTYPE_FLOPDD;
	} else if (size == 512*22*2*80) {
        return DISKTYPE_FLOPHD;
	} else if (size > 512*22*2*80) {
        return DISKTYPE_HARDDISK;
	}

	return -1;
}

}	// anonymous