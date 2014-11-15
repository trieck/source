/////////////////////////////////////////////////////////////////////////////
//
// CACHEENTRY.CPP : ADF cache entry definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#include "common.h"
#include "CacheEntry.h"

/////////////////////////////////////////////////////////////////////////////
CacheEntry::CacheEntry() : days(0), header(0), mins(0), protect(0), size(0),
    ticks(0), type(0)
{
}

CacheEntry::CacheEntry(const CacheEntry &e)
{
    *this = e;
}

/////////////////////////////////////////////////////////////////////////////
CacheEntry::~CacheEntry()
{
}

/////////////////////////////////////////////////////////////////////////////
CacheEntry & CacheEntry::operator =(const CacheEntry &e)
{
    if (this != &e) {
        header = e.header;
        size = e.size;
        protect = e.protect;
        days = e.days;
        mins = e.mins;
        ticks = e.ticks;
        type = e.type;
        name = e.name;
        comment = e.comment;
    }

    return *this;
}
