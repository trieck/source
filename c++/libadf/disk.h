/////////////////////////////////////////////////////////////////////////////
//
// DISK.H : ADF disk definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DISK_H__
#define __DISK_H__

#include "volume.h"

class Disk;
typedef auto_ptr<Disk> DiskPtr;

/////////////////////////////////////////////////////////////////////////////
class Disk
{
// Construction / destruction
private:
	Disk();
public:
	~Disk();

// Interface
	static DiskPtr create(const char *filename, 
		uint32_t cylinders, uint32_t heads, uint32_t sectors);
	static DiskPtr open(const char *filename, const char *mode);
	void close();

	Volume *mount();
	void unmount();
	string Filename() const;
	uint32_t Size() const;
	uint32_t Type() const;
	uint32_t Cylinders() const;
	uint32_t Heads() const;
	uint32_t Sectors() const;

// Implementation
private:
	void readblock(uint32_t blockno, void *block);

	uint32_t size;						// size in bytes of disk
	uint32_t type;						// disk type
	uint32_t cylinders, heads, sectors; // geometry
	string filename;					// file name
	FILE *fp;							// file pointer	
	VolumeList volumes;					// partitions
	friend class Volume;
};

inline string Disk::Filename() const {
	return filename;
}

inline uint32_t Disk::Size() const {
	return size;
}

inline uint32_t Disk::Type() const {
	return type;
}

inline uint32_t Disk::Cylinders() const {
	return cylinders;
}

inline uint32_t Disk::Heads() const {
	return heads;
}

inline uint32_t Disk::Sectors() const {
	return sectors;
}



#endif // __DISK_H__
