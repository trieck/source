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

	uint32_t written = 0;
	while (written < n) {
		if (pos == 0 || blockpos == blocksize) {
			createnext();
			blockpos = 0;
		}
	}

	/*
	long bytesWritten;
    unsigned char *dataPtr, *bufPtr;
    int size, blockSize;
    struct bOFSDataBlock *dataB;

    if (n==0) return (n);

    blockSize = file->volume->datablockSize;
    if (isOFS(file->volume->dosType)) {
        dataB =(struct bOFSDataBlock *)file->currentData;
        dataPtr = dataB->data;
    }
    else
        dataPtr = file->currentData;

    if (file->pos==0 || file->posInDataBlk==blockSize) {
        if (adfCreateNextFileBlock(file)==-1)
            (*adfEnv.wFct)("adfWritefile : no more free sector availbale");                        
        file->posInDataBlk = 0;
    }

    bytesWritten = 0; bufPtr = buffer;
    while( bytesWritten<n ) {
        size = min(n-bytesWritten, blockSize-file->posInDataBlk);
        memcpy(dataPtr+file->posInDataBlk, bufPtr, size);
        bufPtr += size;
        file->pos += size;
        bytesWritten += size;
        file->posInDataBlk += size;
        if (file->posInDataBlk==blockSize && bytesWritten<n) {
            if (adfCreateNextFileBlock(file)==-1)
                (*adfEnv.wFct)("adfWritefile : no more free sector availbale");                        
            file->posInDataBlk = 0;
        }
    }
    return( bytesWritten );
}
*/
	return 0;
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
