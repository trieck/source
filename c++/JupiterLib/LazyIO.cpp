/////////////////////////////////////////////////////////////////////////////
//
//	LAZYIO.CPP : lazy block i/o interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "RandStream.h"
#include "blockio.h"
#include "BlockMgr.h"
#include "wthread.h"
#include "lazyio.h"
#include <time.h>

/////////////////////////////////////////////////////////////////////////////
LazyIO::LazyIO(uint16_t bsize, uint16_t hsize)
 : io(bsize, hsize), blocksize(bsize), headersize(hsize), worker(this)
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

/////////////////////////////////////////////////////////////////////////////
LazyIO::~LazyIO()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void LazyIO::close()
{
	if (hEvent != NULL) {
		SetEvent(hEvent);		
		CloseHandle(hEvent);
		flushblocks();
		hEvent = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool LazyIO::open(LPCSTR filename, OpenMode mode)
{
	if (!io.open(filename, mode))
		return false;

	worker.Start();

	return true;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t LazyIO::readblock(uint64_t blockno, void *pv)
{
	Block *block;
	if (block = mgr.Lock(blockno)) {
		memcpy(pv, block->pv, blocksize);
		block->laccess = time(NULL);
		mgr.Release();
		return blocksize;
	}

	uint32_t nread = io.readblock(blockno, pv);

	cache(blockno, pv);

	return nread;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t LazyIO::writeblock(uint64_t blockno, const void *pv)
{
	Block *block;
	if (block = mgr.Lock(blockno)) {
		uint32_t nwritten = blocksize;
		if (block->dirty) nwritten = flushblock(block);
		memcpy(block->pv, pv, blocksize);
		block->laccess = time(NULL);
		block->dirty = true;
		mgr.Release();
		return nwritten;
	}

	cache(blockno, pv, true);

	return blocksize;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t LazyIO::readheader(void *pv)
{
	return io.readheader(pv);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t LazyIO::writeheader(const void *pv)
{
	return io.writeheader(pv);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t LazyIO::insertblock(const void *pv)
{
	uint64_t off = io.getFileSize();
	uint64_t blockno = (off - headersize) / blocksize;

	uint32_t nwritten = io.insertblock(pv);
	
	cache(blockno, pv);

	return nwritten;
}

/////////////////////////////////////////////////////////////////////////////
void LazyIO::cache(uint64_t blockno, const void *pv, bool dirty)
{
	Block block;
	block.blockno = blockno;
	block.dirty = dirty;
	block.pv = malloc(blocksize);
	block.laccess = time(NULL);
	block.size = blocksize;
	memcpy(block.pv, pv, blocksize);
	mgr.insert(block);
}

/////////////////////////////////////////////////////////////////////////////
void LazyIO::flushblocks()
{
	uint64_t blockno;
	if (!mgr.getFirst(blockno))
		return;
	
	do {
		flushblock(blockno);
	} while (mgr.getNext(blockno));
}

/////////////////////////////////////////////////////////////////////////////
bool LazyIO::flushblock(uint64_t blockno)
{
	Block *block;
	if (block = mgr.Lock(blockno)) {
		flushblock(block);
		mgr.Release();
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
uint16_t LazyIO::flushblock(Block *block)
{
	uint32_t nwritten = 0;

	if (block->dirty) {
		nwritten = io.writeblock(block->blockno, block->pv);
		block->dirty = false;
	}

	return nwritten;
}

/////////////////////////////////////////////////////////////////////////////
bool LazyIO::remove(uint64_t &blockno)
{
	bool ret = false;

	Block *block;
	if (block = mgr.Lock(blockno)) {
		flushblock(block);
		ret = mgr.remove(blockno); 
		mgr.Release();
	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////
DWORD LazyIO::Execute(LPVOID pparam)
{
	uint64_t blockno; time_t laccess;

	while (WaitForSingleObject(hEvent, 0) != WAIT_OBJECT_0) {
		if (!mgr.getFirst(blockno))
			continue;

		while (mgr.getLastAccessed(blockno, &laccess)) {
			if ((time(NULL) - laccess) > TTL) {
				if (!remove(blockno)) {
					if (!mgr.getNext(blockno))
						break;
				} 
			} else 
				if (!mgr.getNext(blockno))
					break;
		}			 		
	}

	return 0;
}