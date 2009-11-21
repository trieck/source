/////////////////////////////////////////////////////////////////////////////
//
// CACHEENTRY.H : ADF cache entry definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __CACHEENTRY_H__
#define __CACHEENTRY_H__

/////////////////////////////////////////////////////////////////////////////
class CacheEntry {
public:
	CacheEntry();
	CacheEntry(const CacheEntry &entry);
	~CacheEntry();

// Interface
	CacheEntry &operator =(const CacheEntry &e);

// Implementation
public:
	uint32_t header;	// entry block
	uint32_t size;		// file size. 0 for directory
	uint32_t protect;	// protection flags
	uint16_t days;		// date
	uint16_t mins;		// time
	uint16_t ticks;		// 1/50 secod
	int8_t type;		// ST_DIR, ST_FILE, ST_LFILE, ST_LDIR, ST_LSOFT;
	string name;		// entry name
	string comment;		// entry comment
};

#endif // __CACHEENTRY_H__