/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.H : ADF volume definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __VOLUME_H__
#define __VOLUME_H__

#include "entry.h"
#include "file.h"
#include "fileblocks.h"

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
	void readextblock(uint32_t blockno, fileext_t *block);
	void readdircblock(uint32_t blockno, dircacheblock_t *block);
	bool isValidBlock(uint32_t blockno);
	bool isBlockFree(uint32_t blockno);

	uint32_t getRootBlock() const;
	uint32_t getCurrentDir() const;
	uint32_t getDataBlockSize() const;
	uint32_t getFirstBlock() const;
	uint32_t getLastBlock() const;
	uint32_t freeblocks();
	int8_t getType() const;
	string getName() const;

	void setCurrentDir(uint32_t blockno);
	EntryList readdir(uint32_t blockno, bool recurse);
	FilePtr openfile(const char *filename, const char *mode);
	FilePtr openfile(const Entry &e);
	void createFile(uint32_t parent, const char *name, fileheader_t *
		header);
	uint32_t createEntry(entryblock_t *dir, const char *name, uint32_t blockno);
	void changedir(Entry *pEntry);
	void changedir(const char *name);

	void writeblock(uint32_t blockno, void *block);
	void writebootblock(bootblock_t *boot);
	void writerootblock(uint32_t blockno, rootblock_t *root);
	void writedircblock(uint32_t blockno, dircacheblock_t *dirc);
	void writebmextblock(uint32_t blockno, bitmapextblock_t *block);
	void writebmblock(uint32_t blockno, bitmapblock_t *block);
	void writeentry(uint32_t blockno, entryblock_t *e);
	void writedirblock(uint32_t blockno, dirblock_t *block);
	void writefileblock(uint32_t blockno, fileheader_t*block);
	void installbootblock(uint8_t *code);

	bool deleteentry(uint32_t blockno, const char *name);
	void freefileblocks(fileheader_t *entry);
	
	void createbitmap();
	void setBlockFree(uint32_t blockno);
	void setBlockUsed(uint32_t blockno);
	bool writenewbitmap();
	void updatebitmap();
	bool getFreeBlocks(uint32_t blockno, blocklist &blocks);
	uint32_t getFreeBlock(); 
	void createEmptyCache(entryblock_t *parent, uint32_t blockno);
	void delFromCache(entryblock_t *parent, uint32_t blockno);
	FileBlocks getFileBlocks(fileheader_t *block);

// Implementation
private:
	uint32_t lookup(uint32_t blockno, const char *name, 
		entryblock_t *eblock, uint32_t *pupblock);

	void allocbitmap();
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
	bool readonly;			// volume is read only
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
inline uint32_t Volume::getFirstBlock() const {
	return firstblock;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Volume::getLastBlock() const {
	return lastblock;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Volume::getCurrentDir() const {
	return currdir;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Volume::getDataBlockSize() const {
	return dblocksize;
}

/////////////////////////////////////////////////////////////////////////////
inline int8_t Volume::getType() const {
	return type;
}

/////////////////////////////////////////////////////////////////////////////
inline string Volume::getName() const {
	return name;
}

#endif // __VOLUME_H__
