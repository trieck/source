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

/////////////////////////////////////////////////////////////////////////////
File::File(Volume *pVol, entryblock_t *pEntry)
 : volume(pVol), pos(0), blockpos(0), nblock(0), data(&buffer[0])
{
	memcpy(&header, pEntry, sizeof(fileheader_t));
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
void File::readnext()
{
	ofsblock_t *block = (ofsblock_t*)data;

	uint32_t blockno;
	if (nblock ==0) {
        blockno = header.firstblock;
    } else if (isOFS(volume->getType())) {
        blockno = block->next;
	} else {
		/* TODO:
		if (file->nDataBlock<MAX_DATABLK)
            nSect = file->fileHdr->dataBlocks[MAX_DATABLK-1-file->nDataBlock];
        else {
            if (file->nDataBlock==MAX_DATABLK) {
                file->currentExt=(struct bFileExtBlock*)malloc(sizeof(struct bFileExtBlock));
                if (!file->currentExt) (*adfEnv.eFct)("adfReadNextFileBlock : malloc");
                adfReadFileExtBlock(file->volume, file->fileHdr->extension,
                    file->currentExt);
                file->posInExtBlk = 0;
            }
            else if (file->posInExtBlk==MAX_DATABLK) {
                adfReadFileExtBlock(file->volume, file->currentExt->extension,
                    file->currentExt);
                file->posInExtBlk = 0;
            }
            nSect = file->currentExt->dataBlocks[MAX_DATABLK-1-file->posInExtBlk];
            file->posInExtBlk++;
		*/
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
