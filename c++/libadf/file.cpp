/////////////////////////////////////////////////////////////////////////////
//
// FILE.CPP : ADF file definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "volume.h"
#include "file.h"
#include "adfwarn.h"
#include "adfutil.h"
#include "adfexcept.h"

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, entryblock_t *pEntry)
 : volume(pVol), pos(0), blockpos(0), nblock(0), data(&buffer[0])
{
	memcpy(&header, pEntry, sizeof(fileheader_t));
	entry = *pEntry;
	memset(buffer, 0, BSIZE);
}

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, const Entry &e)
 : volume(pVol), pos(0), blockpos(0), nblock(0), data(&buffer[0])
{
	entry = e;
	volume->readblock(entry.blockno, &header);	
#ifdef LITTLE_ENDIAN
	header.type = swap_endian(header.type);
	header.key = swap_endian(header.key);
	header.nblocks = swap_endian(header.nblocks);
	header.firstblock = swap_endian(header.firstblock);
	header.checksum = swap_endian(header.checksum);

	for (uint32_t i = 0; i < MAX_DATABLK; i++)
		header.datablocks[i] = swap_endian(header.datablocks[i]);
	header.extension = swap_endian(header.extension);
	header.parent = swap_endian(header.parent);
	header.sectype = swap_endian(header.sectype);
#endif
	memset(buffer, 0, BSIZE);
}

/////////////////////////////////////////////////////////////////////////////
File::~File()
{
}

/////////////////////////////////////////////////////////////////////////////
uint32_t File::read(uint32_t n, void *buf)
{
	if (n == 0)
		return 0;

	uint32_t blocksize = volume->getDataBlockSize();

	// calculate remaining bytes to read
	if (pos + n > entry.size) {
		n = entry.size - pos;
	}

	uint8_t *pdata = isOFS(volume->getType()) ?
		data+(BSIZE-OFS_DBSIZE) : data;

	uint8_t *pbuf = (uint8_t*)buf;
	uint32_t read = 0, size;

	while (read < n) {
		if (pos == 0 || blockpos == blocksize) {
			readnext();
		}

		size = min(n - read, blocksize - blockpos);
		memcpy(pbuf, pdata + blockpos, size);
		pbuf += size;
		pos += size;
		read += size;
		blockpos += size;		
	}
	
    return read;
}

/////////////////////////////////////////////////////////////////////////////
void File::readnext()
{
	ofsblock_t *block = (ofsblock_t*)data;

	uint32_t blockno;
	if (nblock ==0) {
        blockno = entry.firstblock;
    } else if (isOFS(volume->getType())) {
        blockno = block->next;
	} else {	// FFS
		if (nblock < MAX_DATABLK) {
			blockno = header.datablocks[MAX_DATABLK-1-nblock];
		} else {
			;
		}
	}

	volume->readdatablock(blockno, data);

	if (isOFS(volume->getType()) && block->seqnum != nblock+1) {
		ADFWarningDispatcher::dispatch("sequence number incorrect.");
	}

	blockpos = 0;

	nblock++;
}

/////////////////////////////////////////////////////////////////////////////
bool File::isEOF() const
{
	return pos == entry.size;
}
