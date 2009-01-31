/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.H : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#ifndef __VOLUME_H__
#define __VOLUME_H__

class Disk;
class Volume;
typedef auto_ptr<Volume> VolumePtr;

/////////////////////////////////////////////////////////////////////////////
class Volume
{
// Construction / destruction
private:
	Volume();
public:
	~Volume();

// Interface
	void unmount();
	void readblock(uint32_t blockno, uint8_t *block);
	void readbootblock();
	void readrootblock();

// Implementation
private:
	uint32_t firstblock;	// first block of data area
    uint32_t lastblock;		// last block of data area
    uint32_t rootblock;		// root block from first block
	uint32_t dblocksize;	// datablock size
	uint32_t blocksize;		// block size
	uint32_t bitmapsize;	// bitmap size
	int8_t type;			// FFS/OFS, DIRCACHE, INTERNATIONAL
	string name;			// volume name
	bool mounted;			// volume is mounted
	Disk *disk;				// disk mounted from
	friend class Disk;
};

#endif // __VOLUME_H__
