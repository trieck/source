/////////////////////////////////////////////////////////////////////////////
//
// DISK.H : ADF disk definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
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
	static DiskPtr open(const char *filename);
	void close();

	VolumePtr mount();
	
// Implementation
private:
	void readblock(uint32_t blockno, void *block);

	uint32_t size;						// size in bytes of disk
	uint32_t cylinders, heads, sectors; // geometry
	string filename;					// file name
	FILE *fp;							// file pointer		
	friend class Volume;
};

#endif // __DISK_H__
