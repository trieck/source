/////////////////////////////////////////////////////////////////////////////
//
//	LAZYIO.H : lazy block i/o interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LAZYIO_H__
#define __LAZYIO_H__

/////////////////////////////////////////////////////////////////////////////
class LazyIO : public IRunnable {
// Construction / Destruction
public:
    LazyIO(uint16_t bsize, uint16_t hsize);
    virtual ~LazyIO();

// Interface
    bool open(LPCSTR filename, OpenMode mode);
    void close();
    uint64_t getFileSize() {
        return io.getFileSize();
    }
    bool isOpen() const {
        return io.isOpen();
    }

    uint32_t readheader(void *pv);
    uint32_t readblock(uint64_t blockno, void *pv);
    uint32_t writeblock(uint64_t blockno, const void *pv);
    uint32_t writeheader(const void *pv);
    uint32_t insertblock(const void *pv);

    DWORD Execute(LPVOID pparam);

// Implementation
private:
    void cache(uint64_t blockno, const void *pv, bool dirty = false);

    bool remove(uint64_t &blockno);
    void flushblocks();
    bool flushblock(uint64_t blockno);
    uint16_t flushblock(Block *block);

    enum { TTL = 120 };

    blockio io;
    BlockMgr mgr;
    WorkerThread worker;
    HANDLE hEvent;
    uint16_t blocksize;
    uint16_t headersize;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __LAZYIO_H__