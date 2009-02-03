/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.H : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __VOLUME_H__
#define __VOLUME_H__

#include "entry.h"
#include "file.h"

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
	void readblock(uint32_t blockno, void *block);
	void readbootblock(bootblock_t *boot);
	void readrootblock(rootblock_t *root);
	void readbitmap(rootblock_t *root);
	void readbmblock(uint32_t blockno, bitmapblock_t *bm);
	void readdatablock(uint32_t blockno, void *block);
	void readentry(uint32_t blockno, entryblock_t *e);
	bool isValidBlock(uint32_t blockno);
	bool isBlockFree(uint32_t blockno);

	uint32_t getRootBlock() const;
	uint32_t getDataBlockSize() const;
	uint32_t freeblocks();
	int8_t getType() const;
	
	EntryList readdir(uint32_t blockno, bool recurse);
	FilePtr openfile(const char *filename);
	void changedir(const char *name);

// Implementation
private:
	bool lookup(const char *name, entryblock_t *eblock);
	void freebitmap();

	uint32_t firstblock;	// first block of data area
    uint32_t lastblock;		// last block of data area
    uint32_t rootblock;		// root block from first block
	uint32_t dblocksize;	// datablock size
	uint32_t blocksize;		// block size
	uint32_t bitmapsize;	// bitmap size in blocks
	uint32_t currdir;		// current directory block
	int8_t type;			// FFS/OFS, DIRCACHE, INTERNATIONAL
	string name;			// volume name
	bool mounted;			// volume is mounted
	Disk *disk;				// disk mounted from
	bitmapblock_t **bmtbl;	// bitmap table
	uint32_t *bmblocks;		// bitmap blocks

	friend class Disk;
};

typedef vector<Volume*> VolumeList;

/////////////////////////////////////////////////////////////////////////////
inline bool Volume::isValidBlock(uint32_t blockno) {
	return (0 <= blockno && blockno <= (lastblock-firstblock));
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Volume::getRootBlock() const {
	return rootblock;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Volume::getDataBlockSize() const {
	return dblocksize;
}

/////////////////////////////////////////////////////////////////////////////
inline int8_t Volume::getType() const {
	return type;
}

#endif // __VOLUME_H__
