/////////////////////////////////////////////////////////////////////////////
//
// FILEBLOCKS.H : file block list abstraction
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __FILEBLOCKS_H__
#define __FILEBLOCKS_H__

/////////////////////////////////////////////////////////////////////////////
class FileBlocks {
// Construction / destruction
public:
    FileBlocks();
    FileBlocks(const FileBlocks &blocks);
    ~FileBlocks();

// Interface
    FileBlocks& operator = (const FileBlocks &blocks);

    uint32_t getHeader() const;
    void setHeader(uint32_t header);

    uint32_t getExtenCount() const;
    void addExten(uint32_t blockno);

    uint32_t getDataCount() const;
    void addData(uint32_t blockno);

    block_iterator getExtenBegin() const;
    block_iterator getExtenEnd() const;
    block_iterator getDataBegin() const;
    block_iterator getDataEnd() const;

// Implementation
private:
    uint32_t header;	// header block #
    blocklist extens;	// extension block list
    blocklist data;		// file data
};

/////////////////////////////////////////////////////////////////////////////
inline uint32_t FileBlocks::getHeader() const
{
    return header;
}

/////////////////////////////////////////////////////////////////////////////
inline void FileBlocks::setHeader(uint32_t header)
{
    this->header = header;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t FileBlocks::getExtenCount() const
{
    return extens.size();
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t FileBlocks::getDataCount() const
{
    return data.size();
}

#endif // __FILEBLOCKS_H__
