/////////////////////////////////////////////////////////////////////////////
//
//	BLOCKMGR.CPP : thread-safe block management interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "blockmgr.h"
#include "CSHolder.h"

/////////////////////////////////////////////////////////////////////////////
tagBlock::tagBlock()
    : blockno(0), dirty(false), pv(0), size(0), laccess(0)
{
}

/////////////////////////////////////////////////////////////////////////////
tagBlock::~tagBlock()
{
}

/////////////////////////////////////////////////////////////////////////////
tagBlock::tagBlock(const tagBlock &rhs)
{
    *this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
tagBlock &tagBlock::operator =(const tagBlock &rhs)
{
    if (this != &rhs) {
        blockno = rhs.blockno;
        dirty = rhs.dirty;
        pv = rhs.pv;
        size = rhs.size;
        laccess = rhs.laccess;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////
BlockMgr::BlockMgr()
{
}

/////////////////////////////////////////////////////////////////////////////
BlockMgr::~BlockMgr()
{
    freeblocks();
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::exists(uint64_t blockno)
{
    CSHolder lock(cs);
    return blocks.find(blockno) != blocks.end();
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::isDirty(uint64_t blockno)
{
    CSHolder lock(cs);

    CBlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    const Block &block = (*it).second;
    return block.dirty;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::setDirty(uint64_t blockno, bool dirty)
{
    CSHolder lock(cs);

    BlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    Block &block = (*it).second;
    block.dirty = dirty;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::setLastAccessed(uint64_t blockno, time_t t)
{
    CSHolder lock(cs);

    BlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    Block &block = (*it).second;
    block.laccess = t;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::getLastAccessed(uint64_t blockno, time_t *pt)
{
    CSHolder lock(cs);

    CBlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    const Block &block = (*it).second;
    *pt = block.laccess;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::setData(uint64_t blockno, const void *pv)
{
    CSHolder lock(cs);

    BlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    Block &block = (*it).second;
    memcpy(block.pv, pv, block.size);

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::getData(uint64_t blockno, void *pv)
{
    CSHolder lock(cs);

    CBlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    const Block &block = (*it).second;
    memcpy(pv, block.pv, block.size);

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::remove(uint64_t &blockno)
{
    CSHolder lock(cs);

    BlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    Block &block = (*it).second;

    free(block.pv);
    if ((it = blocks.erase(it)) != blocks.end())
        blockno = (*it).first;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::insert(const Block &block)
{
    CSHolder lock(cs);

    BlockIterator it = blocks.find(block.blockno);
    if (it != blocks.end())
        return false;	// already exists

    blocks[block.blockno] = block;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::getFirst(uint64_t &blockno)
{
    CSHolder lock(cs);

    CBlockIterator it = blocks.begin();
    if (it == blocks.end())
        return false;

    blockno = (*it).first;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BlockMgr::getNext(uint64_t &blockno)
{
    CSHolder lock(cs);

    CBlockIterator it = blocks.find(blockno);
    if (it == blocks.end())
        return false;

    if (++it == blocks.end())
        return false;	// last block

    blockno = (*it).first;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
Block *BlockMgr::Lock(uint64_t blockno)
{
    cs.Lock();

    BlockIterator it = blocks.find(blockno);
    if (it == blocks.end()) {
        cs.Unlock();
        return NULL;
    }

    Block *block = &(*it).second;

    // Keep Lock held

    return block;
}

/////////////////////////////////////////////////////////////////////////////
void BlockMgr::Release()
{
    cs.Unlock();
}

/////////////////////////////////////////////////////////////////////////////
void BlockMgr::freeblocks()
{
    BlockIterator it = blocks.begin();
    while (it != blocks.end()) {
        Block &block = (*it).second;
        free(block.pv);
        it = blocks.erase(it);
    }
}
