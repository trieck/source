/////////////////////////////////////////////////////////////////////////////
//
//	BLOCKMGR.H : thread-safe block management interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BLOCKMGR_H__
#define __BLOCKMGR_H__

/////////////////////////////////////////////////////////////////////////////
typedef struct tagBlock {
	tagBlock();
	tagBlock(const tagBlock &rhs);
	~tagBlock();

	tagBlock &operator =(const tagBlock &rhs);

	uint64_t blockno;	// block number
	bool dirty;			// block is dirty?
	void *pv;			// block data
	uint16_t size;		// block data size
	time_t laccess;		// last access time
} Block;

/////////////////////////////////////////////////////////////////////////////
class BlockMgr 
{
// Construction / Destruction
public:
	BlockMgr();
	virtual ~BlockMgr();

// Interface
	bool exists(uint64_t blockno);
	bool isDirty(uint64_t blockno);
	bool setDirty(uint64_t blockno, bool dirty);
	bool setLastAccessed(uint64_t blockno, time_t t);
	bool getLastAccessed(uint64_t blockno, time_t *pt);
	bool setData(uint64_t blockno, const void *pv);
	bool getData(uint64_t blockno, void *pv);

	bool remove(uint64_t &blockno);
	bool insert(const Block &block);

	bool getFirst(uint64_t &blockno);
	bool getNext(uint64_t &blockno);

	Block *Lock(uint64_t blockno);
	void Release();

// Implementation
private:
	void freeblocks();

	typedef map<uint64_t, Block> BlockMap;
	typedef BlockMap::const_iterator CBlockIterator;
	typedef BlockMap::iterator BlockIterator;

	CComAutoCriticalSection cs;
	BlockMap blocks;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __BLOCKMGR_H__