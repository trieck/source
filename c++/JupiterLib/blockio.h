/////////////////////////////////////////////////////////////////////////////
//
//	BLOCKIO.H : block i/o interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BLOCKIO_H__
#define __BLOCKIO_H__

/////////////////////////////////////////////////////////////////////////////
class blockio {
// Construction / Destruction
public:
    blockio(uint16_t blocksize = 4096, uint16_t headersize = 0);
    virtual ~blockio();

// Interface
    uint32_t open(LPCSTR filename, OpenMode mode);

    void close();

    uint32_t readblock(uint64_t blockno, void *pv);
    uint32_t readheader(void *pv);
    uint32_t writeblock(uint64_t blockno, const void *pv);
    uint32_t writeheader(const void *pv);
    uint32_t insertblock(const void *pv);
    uint32_t seekblock(uint64_t blockno);

    uint64_t tell();
    uint16_t getBlockSize() const {
        return blocksize;
    }
    uint16_t getHeaderSize() const {
        return headersize;
    }
    uint64_t getFileSize();

    bool isOpen() const {
        return stream != NULL;
    }

// Implementation
private:
    uint32_t read(void *pv, uint32_t len);
    uint32_t write(const void *pv, uint32_t len);
    uint32_t seek(int64_t offset, uint32_t whence);

    uint16_t headersize, blocksize;
    RandomFileStreamPtr stream;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __BLOCKIO_H__