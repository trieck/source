/////////////////////////////////////////////////////////////////////////////
//
// FILE.CPP : ADF file definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#include "common.h"
#include "adf.h"
#include "volume.h"
#include "file.h"
#include "adfwarn.h"
#include "adfutil.h"
#include "adfexcept.h"

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, fileheader_t *pheader)
 : volume(pVol), pos(0), blockpos(0), extentpos(0), nblock(0), data(&buffer[0])
{
	memcpy(&header, pheader, sizeof(fileheader_t));
	memset(buffer, 0, BSIZE);
	memset(&extent, 0, sizeof(fileext_t));
}

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, entryblock_t *pEntry)
 : volume(pVol), pos(0), blockpos(0), extentpos(0), nblock(0), data(&buffer[0])
{
	memcpy(&header, pEntry, sizeof(fileheader_t));
	memset(buffer, 0, BSIZE);
	memset(&extent, 0, sizeof(fileext_t));
}

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, const Entry &e)
 : volume(pVol), pos(0), blockpos(0), nblock(0), data(&buffer[0])
{
	memset(buffer, 0, BSIZE);
	memset(&extent, 0, sizeof(fileext_t));
	volume->readblock(e.blockno, &header);	
#ifdef LITTLE_ENDIAN
	swapfileblock(&header);
#endif	
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
	if (pos + n > header.bytesize) {
		n = header.bytesize - pos;
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
uint32_t File::write(uint32_t n, const void *buf)
{
	if (n == 0)
		return 0;

	uint32_t blocksize = volume->getDataBlockSize();

	uint8_t *pdata;
	if (isOFS(volume->getType())) {
		pdata = ((ofsblock_t*)data)->data;
	} else {
		pdata = data;
	}

	uint8_t *pbuf = (uint8_t*)buf;
	uint32_t written = 0, size;

	while (written < n) {
		if (pos == 0 || blockpos == blocksize) {
			createnext();
			blockpos = 0;
		}

		size = min(n - written, blocksize - blockpos);
		memcpy(pdata + blockpos, pbuf, size);
		pbuf += size;
		pos += size;
		written += size;
		blockpos += size;
	}

	return written;
}

/////////////////////////////////////////////////////////////////////////////
void File::readnext()
{
	ofsblock_t *block = (ofsblock_t*)data;

	uint32_t blockno;
	if (nblock ==0) {
        blockno = header.firstblock;
    } else if (isOFS(volume->getType())) {
        blockno = block->next;
	} else {	// FFS
		if (nblock < MAX_DATABLK) {
			blockno = header.datablocks[MAX_DATABLK-1-nblock];
		} else {
			if (nblock == MAX_DATABLK) {	// extension block
				volume->readextblock(header.extension, &extent);
				extentpos = 0;
			} else if (extentpos == MAX_DATABLK) {
				volume->readextblock(extent.extension, &extent);
				extentpos = 0;
			}
			blockno = extent.blocks[MAX_DATABLK-1-extentpos];
			extentpos++;
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
void File::createnext()
{
	uint32_t blocksize = volume->getDataBlockSize();

	ofsblock_t *block = (ofsblock_t*)data;

	uint32_t blockno, extblock;

	// the first data blocks pointers are inside the file header block
	if (nblock < MAX_DATABLK) {
		if ((blockno = volume->getFreeBlock()) == -1)
			throw ADFException("can't allocate data block.");

		if (nblock == 0)
			header.firstblock = blockno;
		header.datablocks[MAX_DATABLK-1-nblock] = blockno;
		header.nblocks++;
	} else {
		// one more sector is needed for one file extension block
		if ((nblock % MAX_DATABLK) == 0) {
			if ((extblock = volume->getFreeBlock()) == -1)
				throw ADFException("can't allocate extension block.");

			// first extension block
			if (nblock == MAX_DATABLK) {
				header.extension = extentpos;
			}

			// not the first : save current one and link it in
			if (nblock >= 2 * MAX_DATABLK) {
				extent.extension = extblock;
				volume->writefileextblock(extent.key, &extent);
			}

			// initializes a file extension block
			uint32_t i;
            for (i = 0; i < MAX_DATABLK; i++)
                extent.blocks[i] = 0;

            extent.key = extblock;
            extent.parent = header.key;
            extent.highseq = 0;
            extent.extension = 0;
			extentpos = 0;
		}

		if ((blockno = volume->getFreeBlock()) == -1)
			throw ADFException("can't allocate extension block.");

		extent.blocks[MAX_DATABLK-1-extentpos] = blockno;
		extent.highseq++;
		extentpos++;
	}	

	// build OFS header
	if (isOFS(volume->getType()) {
		// write previous data block and link it
		if (pos >= blocksize) {
			block->next = blockno;
			volume->writedatablock(

	/*

    // builds OFS header
    if (isOFS(file->volume->dosType)) {
        // writes previous data block and link it
        if (file->pos>=blockSize) {
            data->nextData = nSect;
            adfWriteDataBlock(file->volume, file->curDataPtr, file->currentData);


        }
        // initialize a new data block 
        for(i=0; i<(int)blockSize; i++)
            data->data[i]=0;
        data->seqNum = file->nDataBlock+1;
        data->dataSize = blockSize;
        data->nextData = 0L;
        data->headerKey = file->fileHdr->headerKey;
    }
    else
        if (file->pos>=blockSize) {
            adfWriteDataBlock(file->volume, file->curDataPtr, file->currentData);


            memset(file->currentData,0,512);
        }
            

    file->curDataPtr = nSect;
    file->nDataBlock++;

    return(nSect);
}

*/
}

/////////////////////////////////////////////////////////////////////////////
bool File::isEOF() const
{
	return pos == header.bytesize;
}

/////////////////////////////////////////////////////////////////////////////
Entry File::getEntry() const
{
	entryblock_t *pentry = (entryblock_t*)&header;
	return Entry(*pentry);
}
