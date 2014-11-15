/////////////////////////////////////////////////////////////////////////////
//
//	BLOCKIO.CPP : block i/o interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "RandStream.h"
#include "blockio.h"

/////////////////////////////////////////////////////////////////////////////
blockio::blockio(uint16_t bsize, uint16_t hsize)
    : blocksize(bsize), headersize(hsize)
{
}

/////////////////////////////////////////////////////////////////////////////
blockio::~blockio()
{
    close();
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::open(LPCSTR filename, OpenMode mode)
{
    close();

    uint32_t access = 0, disp = 0;
    uint32_t attr = FILE_ATTRIBUTE_NORMAL;

    switch (mode) {
    case OM_CREATE:
        access |= GENERIC_READ | GENERIC_WRITE;
        disp |= CREATE_ALWAYS;
        break;
    case OM_RW:
        access |= GENERIC_READ | GENERIC_WRITE;
        disp |= OPEN_ALWAYS;
        break;
    case OM_RO:
    default:
        access |= GENERIC_READ;
        disp |= OPEN_EXISTING;
        break;
    }

    stream.Attach(RandomFileStream::Create(filename, access,
                                           FILE_SHARE_READ | FILE_SHARE_WRITE, disp, attr));

    return stream != NULL;
}

/////////////////////////////////////////////////////////////////////////////
void blockio::close()
{
    stream.Release();
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::read(void *pv, uint32_t len)
{
    ULONG nread;
    stream->Read(pv, len, &nread);
    return nread;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::readblock(uint64_t blockno, void *pv)
{
    if (!seekblock(blockno))
        return 0;

    return read(pv, blocksize);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::readheader(void *pv)
{
    if (!seek(0, STREAM_SEEK_SET))
        return 0;

    return read(pv, headersize);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::write(const void *pv, uint32_t len)
{
    ULONG nwritten;
    stream->Write(pv, len, &nwritten);
    return nwritten;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::writeblock(uint64_t blockno, const void *pv)
{
    if (!seekblock(blockno))
        return 0;

    return write(pv, blocksize);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::writeheader(const void *pv)
{
    if (!seek(0, STREAM_SEEK_SET))
        return 0;

    return write(pv, headersize);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::insertblock(const void *pv)
{
    if (!seek(0, STREAM_SEEK_END))
        return 0;

    return write(pv, blocksize);
}

/////////////////////////////////////////////////////////////////////////////
uint64_t blockio::tell()
{
    ULARGE_INTEGER pos;
    HRESULT hr = stream->Tell(&pos);
    if (FAILED(hr))
        return 0;

    return pos.QuadPart;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::seekblock(uint64_t blockno)
{
    off_t offset = blockno * blocksize + headersize;
    return seek(offset, STREAM_SEEK_SET);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t blockio::seek(int64_t offset, uint32_t whence)
{
    LARGE_INTEGER li;
    li.QuadPart = offset;

    HRESULT hr = stream->Seek(li, whence, NULL);
    if (FAILED(hr))
        return 0;

    return 1;
}

/////////////////////////////////////////////////////////////////////////////
uint64_t blockio::getFileSize()
{
    STATSTG stg;
    HRESULT hr = stream->Stat(&stg, STATFLAG_NONAME);
    if (FAILED(hr))
        return 0;

    return stg.cbSize.QuadPart;
}
