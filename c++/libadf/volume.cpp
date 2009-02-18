/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.CPP : ADF volume definition
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#include "common.h"
#include "adf.h"
#include "adfutil.h"
#include "adfexcept.h"
#include "disk.h"
#include "volume.h"
#include "adfwarn.h"
#include "CacheEntry.h"

uint32_t bitmask[BM_BLOCKS_ENTRY] = { 
    0x1, 0x2, 0x4, 0x8,
	0x10, 0x20, 0x40, 0x80,
    0x100, 0x200, 0x400, 0x800,
	0x1000, 0x2000, 0x4000, 0x8000,
	0x10000, 0x20000, 0x40000, 0x80000,
	0x100000, 0x200000, 0x400000, 0x800000,
	0x1000000, 0x2000000, 0x4000000, 0x8000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000 
};

namespace { 
	CacheEntry getCacheEntry(dircacheblock_t *block, int32_t *offset);
}

/////////////////////////////////////////////////////////////////////////////
Volume::Volume()
: blocksize(0), bitmapsize(0), dblocksize(0), firstblock(0), lastblock(0), 
 rootblock(0), type(0), mounted(false), bmtbl(0), bmblocks(0), disk(0),
 currdir(0), readonly(true)
{
}

/////////////////////////////////////////////////////////////////////////////
Volume::~Volume()
{
	unmount();
}

/////////////////////////////////////////////////////////////////////////////
void Volume::unmount()
{
	freebitmap();
    mounted = false;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::freebitmap()
{
	if (bmtbl != NULL) {
		for (uint32_t i = 0; i < bitmapsize; i++) {
			free(bmtbl[i]);
		}

		free(bmtbl);
		bmtbl = NULL;
	}

	bitmapsize = 0;

	if (bmblocks != NULL) {
        free(bmblocks);
		bmblocks = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readblock(uint32_t blockno, void *block)
{
	if (!mounted) throw ADFException("volume not mounted.");
	
	// translate logical sector to physical sector
    blockno = blockno + firstblock;

	if (!isValidBlock(blockno))
		throw ADFException("sector out of range.");

	disk->readblock(blockno, block);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readdatablock(uint32_t blockno, void *block)
{
	uint8_t buf[BSIZE];
    
	readblock(blockno, buf);
	memcpy(block, buf, BSIZE);

	if (isOFS(type)) {
		ofsblock_t *dblock = (ofsblock_t*)block;

#ifdef LITTLE_ENDIAN
		swapofsblock(dblock);
#endif // LITTLE_ENDIAN

		if (dblock->checksum != adfchecksum(buf, 20, sizeof(ofsblock_t))) {
			ADFWarningDispatcher::dispatch("invalid checksum.");
		}

		if (dblock->type != T_DATA) {
			ADFWarningDispatcher::dispatch("bad datablock type.");
		}

		if (dblock->size < 0 || dblock->size > OFS_DBSIZE) {
			ADFWarningDispatcher::dispatch("datablock size incorrect.");
		}

		if (!isValidBlock(dblock->key)) {
			ADFWarningDispatcher::dispatch("header key out of range.");
		}

		if (!isValidBlock(dblock->next)) {
			ADFWarningDispatcher::dispatch("next block out of range.");
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbootblock(bootblock_t *boot)
{
	uint8_t buf[BOOTBLOCKSIZE];

	readblock(0, buf);
	readblock(1, buf+BSIZE);

	memcpy(boot, buf, BOOTBLOCKSIZE);
#ifdef LITTLE_ENDIAN
	boot->checksum = swap_endian(boot->checksum);
	boot->rootblock = swap_endian(boot->rootblock);
#endif	// LITTLE_ENDIAN

	if (strncmp("DOS", boot->type, 3) != 0) {
		ADFWarningDispatcher::dispatch("dos id not found.");
	}

	if (boot->code[0] != 0 && bootsum(buf) != boot->checksum) {
		ADFWarningDispatcher::dispatch("bad checksum.");
	}

	type = boot->type[3];
	if (isFFS(type)) {
		dblocksize = BSIZE;
	} else {
		dblocksize = OFS_DBSIZE;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readrootblock(rootblock_t *root)
{
	uint8_t buf[BSIZE];
	readblock(rootblock, buf);

	memcpy(root, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	swaprootblock(root);
#endif // LITTLE_ENDIAN
	
	if (root->type != T_HEADER && root->sectype != ST_ROOT) {
		ADFWarningDispatcher::dispatch("bad root block type.");
    }

	if (root->checksum != adfchecksum(buf, 20, BSIZE)) {
		ADFWarningDispatcher::dispatch("bad checksum.");
	}

	// copy diskname into volume
	name = string(root->diskname, root->namelen);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::allocbitmap()
{
	freebitmap();

	// total number of blocks in bitmap block
	uint32_t blocksmap = BM_MAPSIZE * BM_BLOCKS_ENTRY;

	// total number of blocks for volume minus bootblock
	uint32_t nblocks = lastblock - firstblock + 1 - 2;

	// bitmap size in blocks
	uint32_t mapsize = nblocks / blocksmap;

    if (nblocks % blocksmap != 0)
        mapsize++;	

	bitmapsize = mapsize;
	bmtbl = (bitmapblock_t**) xmalloc(sizeof(bitmapblock_t*) * mapsize);
	bmblocks = (uint32_t*) xmalloc(sizeof(uint32_t) * mapsize);

	uint32_t i;
	for (i = 0; i < mapsize; i++) {
        bmtbl[i] = (bitmapblock_t*)xmalloc(sizeof(bitmapblock_t));
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbitmap(rootblock_t *root)
{
	allocbitmap();

	uint32_t i;
	for (i = 0; i < BM_SIZE && root->bmpages[i] != 0; i++) {
		bmblocks[i] = root->bmpages[i];

		if (!isValidBlock(bmblocks[i])) {
			ADFWarningDispatcher::dispatch("invalid sector.");
		}
		readbmblock(bmblocks[i], bmtbl[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readbmblock(uint32_t blockno, bitmapblock_t *bm)
{
	uint8_t buf[BSIZE];

	readblock(blockno, buf);
	memcpy(bm, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	swapbmblock(bm);
#endif	// LITTLE_ENDIAN

	if (bm->checksum != adfchecksum(buf, 0, BSIZE)) {
		ADFWarningDispatcher::dispatch("bad checksum.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readentry(uint32_t blockno, entryblock_t *e)
{
	uint8_t buf[BSIZE];

	readblock(blockno, buf);
	memcpy(e, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	swapentry(e);
#endif // LITTLE_ENDIAN

	if (e->checksum != adfchecksum(buf, 20, BSIZE)) {
		ADFWarningDispatcher::dispatch("bad checksum.");
	}

	if (e->type != T_HEADER) {
		ADFWarningDispatcher::dispatch("bad entry type.");
	}

	if (e->namelen > MAXNAMELEN || e->commlen > MAXCOMMLEN) {
		ADFWarningDispatcher::dispatch("bad name or comment length.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readextblock(uint32_t blockno, fileext_t *block)
{
	uint8_t buf[BSIZE];

	readblock(blockno, buf);
	memcpy(block, buf, sizeof(fileext_t));

#ifdef LITTLE_ENDIAN
	swapfileext(block);
#endif // LITTLE_ENDIAN

	if (block->checksum != adfchecksum(buf, 20, BSIZE)) {
		ADFWarningDispatcher::dispatch("bad checksum.");
	}

	if (block->type != T_LIST) {
		ADFWarningDispatcher::dispatch("bad extension block.");
	}

	if (block->sectype != ST_FILE) {
		ADFWarningDispatcher::dispatch("bad extension block.");
	}

	if (block->key != blockno) {
		ADFWarningDispatcher::dispatch("bad extension block.");
	}

	if (block->highseq < 0 || block->highseq > MAX_DATABLK) {
		ADFWarningDispatcher::dispatch("sequence out of range.");
	}

	if (block->extension != 0 && !isValidBlock(block->extension)) {
		ADFWarningDispatcher::dispatch("extension out of range.");
	}
}

/////////////////////////////////////////////////////////////////////////////
bool Volume::isBlockFree(uint32_t blockno)
{
	// total number of blocks in bitmap block
	uint32_t blocksmap = BM_MAPSIZE * BM_BLOCKS_ENTRY;

	uint32_t blockmapno = blockno - 2;	// first 2 blocks not in map
	uint32_t block = blockmapno / blocksmap;
	uint32_t index = (blockmapno / BM_BLOCKS_ENTRY) % BM_MAPSIZE;

	return (bmtbl[block]->map[index] & 
		bitmask[blockmapno % BM_BLOCKS_ENTRY]) != 0;
}

/////////////////////////////////////////////////////////////////////////////
EntryList Volume::readdir(uint32_t blockno, bool recurse)
{
	EntryList entries;
	Entry entry;

	// TODO: dircache

	entryblock_t parent, entryblk;
	readentry(blockno, &parent);

	uint32_t next;
	int32_t *hashtable = parent.tbl;
    for (uint32_t i = 0; i < HT_SIZE; i++) {
		if (hashtable[i] != 0) {
			readentry(hashtable[i], &entryblk);

			entry = entryblk;
			entry.blockno = hashtable[i];
			entries.push_back(entry);
			
			// TODO: if (recurs && entry->type==ST_DIR)

			next = entryblk.nextsamehash;
			while (next != 0) {
				readentry(next, &entryblk);
				entry = entryblk;
				entry.blockno = next;
				entries.push_back(entry);
				
				// TODO: if (recurs && entry->type==ST_DIR)

				next = entryblk.nextsamehash;
			}
		}
	}
	
	return entries;
}

/////////////////////////////////////////////////////////////////////////////
FilePtr Volume::openfile(const char *filename, const char *mode)
{
	bool write = strcmp(mode, "w") == 0;
	if (!write && strcmp(mode, "r") != 0)
		throw ADFException("unknown file mode.");

	if (!write) {	// file exists
		entryblock_t entry;
		uint32_t blockno = lookup(currdir, filename, &entry, NULL);
		if (blockno == -1)
			throw ADFException("file not found.");

		return Volume::openfile(entry);
	} 

	fileheader_t header;
	createFile(currdir, filename, &header);

	File *pFile = new File(this, &header);
	pFile->writemode = write;

	return FilePtr(pFile);
}

/////////////////////////////////////////////////////////////////////////////
FilePtr Volume::openfile(const Entry &e)
{
	// check access permissions
	if (hasR(e.access)) 
		throw ADFException("access denied.");

	return FilePtr(new File(this, e));
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Volume::lookup(uint32_t nblock, const char *name, 
	entryblock_t *pblock, uint32_t *pupblock)
{
	readentry(nblock, pblock);

	bool intl = isINTL(type) || isDIRCACHE(type);

	int32_t hash = adfhash(name, intl);
	string ename, uname = adfToUpper(name, intl);

	uint32_t blockno = pblock->tbl[hash];
	if (blockno == 0)
		return -1;	// not found

	uint32_t ublockno = 0;
	bool found = false;

	do {
		readentry(blockno, pblock);
		ename = string(pblock->name, pblock->namelen);
		ename = adfToUpper(ename.c_str(), intl);

		found = (uname == ename);
		if (!found) {
			ublockno = blockno;
			blockno = pblock->nextsamehash;
		}
	} while (!found && blockno != 0);

	if (blockno == 0 && !found)
		return -1;

	if (pupblock != NULL)
		*pupblock = ublockno;

	return blockno;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::changedir(const char *name)
{
	entryblock_t entry;
	
	uint32_t blockno;
	if ((blockno = lookup(currdir, name, &entry, NULL)) == -1)
		throw ADFException("can't find directory.");		

	if (entry.sectype != ST_DIR)
		throw ADFException("entry not directory.");

	currdir = entry.key;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::changedir(Entry *pEntry)
{
	if (pEntry->type != ST_DIR)
		throw ADFException("entry not directory.");

	currdir = pEntry->blockno;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Volume::freeblocks() 
{
	uint32_t nblocks = 0;

	for (uint32_t i = firstblock + 2; i <= (lastblock - firstblock); i++) {
		if (isBlockFree(i))
			nblocks++;
	}
	
	return nblocks;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::setCurrentDir(uint32_t blockno)
{
	if (!isValidBlock(blockno)) 
		throw ADFException("sector out of range.");

	currdir = blockno;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writebootblock(bootblock_t *boot)
{
	boot->type[0] = 'D';
    boot->type[1] = 'O';
    boot->type[2] = 'S';

#ifdef LITTLE_ENDIAN
	boot->checksum = swap_endian(boot->checksum);
	boot->rootblock = swap_endian(boot->rootblock);
#endif

	uint8_t buf[BOOTBLOCKSIZE];
	memcpy(buf, boot, BOOTBLOCKSIZE);

	// calculate boot block checksum
	if (boot->rootblock == 880 || boot->code[0] != 0) {
		uint32_t sum = bootsum(buf);
		*(uint32_t*)(buf+4) = swap_endian(sum);
	}

	writeblock(0, buf);
	writeblock(1, buf+BSIZE);

#ifdef LITTLE_ENDIAN
	boot->checksum = swap_endian(boot->checksum);
	boot->rootblock = swap_endian(boot->rootblock);
#endif
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writeblock(uint32_t blockno, void *block)
{
	if (!mounted) throw ADFException("volume not mounted.");
	
	if (readonly) throw ADFException("can't write block, read only volume.");

	// translate logical sector to physical sector
    blockno = blockno + firstblock;

	if (!isValidBlock(blockno))
		throw ADFException("sector out of range.");

	disk->writeblock(blockno, block);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::createbitmap()
{
	allocbitmap();

	uint32_t i;
	for (i = firstblock+2; i <= (lastblock-firstblock); i++) {
		setBlockFree(i);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::setBlockFree(uint32_t blockno)
{
	// total number of blocks in bitmap block
	uint32_t blocksmap = BM_MAPSIZE * BM_BLOCKS_ENTRY;

	uint32_t blockmapno = blockno - 2;	// first 2 blocks not in map
	uint32_t block = blockmapno / blocksmap;
	uint32_t index = (blockmapno / BM_BLOCKS_ENTRY) % BM_MAPSIZE;

	bmtbl[block]->map[index] |= bitmask[blockmapno % BM_BLOCKS_ENTRY];
}

/////////////////////////////////////////////////////////////////////////////
void Volume::setBlockUsed(uint32_t blockno)
{
	// total number of blocks in bitmap block
	uint32_t blocksmap = BM_MAPSIZE * BM_BLOCKS_ENTRY;

	uint32_t blockmapno = blockno - 2;	// first 2 blocks not in map
	uint32_t block = blockmapno / blocksmap;
	uint32_t index = (blockmapno / BM_BLOCKS_ENTRY) % BM_MAPSIZE;

	bmtbl[block]->map[index] &= ~bitmask[blockmapno % BM_BLOCKS_ENTRY];
}

/////////////////////////////////////////////////////////////////////////////
bool Volume::getFreeBlocks(uint32_t blockno, blocklist &blocks)
{
	blocks.resize(blockno);

	uint32_t block = rootblock;

	bool full = false;

	uint32_t i, j;
	for (i = 0; i < blockno && !full; ) {
		if (isBlockFree(block)) {
			blocks[i++] = block;
		}

		if (block == lastblock) {
			block = firstblock+2;
		}

		if (block+firstblock == lastblock) {
			block = 2;
		} else if (block == rootblock - 1) {
			full = true;
		} else {
			block++;
		}
	}

	if (!full) {
		for (j = 0; j < blockno; j++) {
			setBlockUsed(blocks[j]);
		}
	}

	return i == blockno;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::createEmptyCache(entryblock_t *parent, uint32_t blockno)
{
	uint32_t ncache;

	if (blockno == -1) {
		if ((ncache = getFreeBlock()) == -1) {
			throw ADFException("volume is full.");
		}
	} else {
		ncache = blockno;
	}

	if (parent->extension == 0)
		parent->extension = ncache;

	dircacheblock_t dirc;
	memset(&dirc, 0, sizeof(dircacheblock_t));

	if (parent->sectype == ST_ROOT) {
		dirc.parent = rootblock;
	} else if (parent->sectype == ST_DIR) {
		dirc.parent = parent->key;
	} else {
		ADFWarningDispatcher::dispatch("unknown sectype.");
	}

	writedircblock(ncache, &dirc);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writerootblock(uint32_t blockno, rootblock_t *root)
{
	root->type = T_HEADER;
    root->key = 0;
    root->highseq = 0L;
    root->tblsize = HT_SIZE;
    root->firstdata = 0;
    root->nextsamehash = 0;
    root->parent = 0;
    root->sectype = ST_ROOT;

#ifdef LITTLE_ENDIAN
	swaprootblock(root);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, root, BSIZE);

	root->checksum = adfchecksum(buf, 20, BSIZE);
	root->checksum = swap_endian(root->checksum);

	writeblock(blockno, root);

#ifdef LITTLE_ENDIAN
	swaprootblock(root);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writedircblock(uint32_t blockno, dircacheblock_t *dirc)
{
	dirc->type = T_DIRC;
	dirc->key = blockno;

#ifdef LITTLE_ENDIAN
	swapdircblock(dirc);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, dirc, BSIZE);

	dirc->checksum = adfchecksum(buf, 20, BSIZE);
	dirc->checksum = swap_endian(dirc->checksum);

	writeblock(blockno, dirc);

#ifdef LITTLE_ENDIAN
	swapdircblock(dirc);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Volume::getFreeBlock() 
{
	blocklist blocks;
	if (!getFreeBlocks(1, blocks))
		return -1;

	return blocks[0];
}

/////////////////////////////////////////////////////////////////////////////
bool Volume::writenewbitmap()
{
	blocklist blocks;
	if (!getFreeBlocks(bitmapsize, blocks)) {
		return false;
	}

	rootblock_t root;
	readrootblock(&root);

	uint32_t size = min(bitmapsize, BM_SIZE);
	uint32_t i, k;

	for (i = 0; i < size; i++) {
		root.bmpages[i] = bmblocks[i] = blocks[i];
	}

	uint32_t nblock, extblock;
	nblock = size;

	if (bitmapsize > BM_SIZE) {
		extblock = (bitmapsize - BM_SIZE) / BM_MAPSIZE;
		if ((bitmapsize - BM_SIZE) % BM_MAPSIZE)
			extblock++;
	
		blocklist eblocks;
		if (!getFreeBlocks(extblock, eblocks)) 
			return false;

		k = 0;
		root.bmext = eblocks[k];

		bitmapextblock_t bmeb;
		while (nblock < bitmapsize) {
			i = 0;
			while (i < BM_MAPSIZE && nblock < bitmapsize) {
				bmeb.pages[i] = bmblocks[nblock] = blocks[i];
				i++;
				nblock++;
			}

			if (k + 1 < extblock) {
                bmeb.next = eblocks[k+1];
			} else {
				bmeb.next = 0;
			}

			writebmextblock(eblocks[k++], &bmeb);
		}
	}

	writerootblock(rootblock, &root);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writebmextblock(uint32_t blockno, bitmapextblock_t *block)
{
#ifdef LITTLE_ENDIAN
	swapbmext(block);
#endif

	writeblock(blockno, block);

#ifdef LITTLE_ENDIAN
	swapbmext(block);
#endif
}

/////////////////////////////////////////////////////////////////////////////
void Volume::updatebitmap()
{
	rootblock_t root;
	readrootblock(&root);

	root.bmflag = BM_INVALID;
	writerootblock(rootblock, &root);

	uint32_t i;
	for (i = 0; i < bitmapsize; i++) {
		writebmblock(bmblocks[i], bmtbl[i]);
    }

	root.bmflag = BM_VALID;

	ADFDateTime tm = adfGetCurrentTime();
	adfTime2AmigaTime(tm, root.days, root.mins, root.ticks);

	writerootblock(rootblock, &root);
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writebmblock(uint32_t blockno, bitmapblock_t *block)
{
#ifdef LITTLE_ENDIAN
	swapbmblock(block);
#endif
	uint8_t buf[BSIZE];
	memcpy(buf, block, BSIZE);

	block->checksum = adfchecksum(buf, 0, BSIZE);
	block->checksum = swap_endian(block->checksum);

	writeblock(blockno, block); 

#ifdef LITTLE_ENDIAN
	swapbmblock(block);
#endif

}

/////////////////////////////////////////////////////////////////////////////
// Install a bootblock on a floppy disk. Won't work on any other device. 
// You must provide the 1024 bytes large bootblock. 
// Doesn't modify the initial 'DOS' header and type. 
// Recalculates the checksum. 
void Volume::installbootblock(uint8_t *code)
{
	if (disk->type != DISKTYPE_FLOPDD && disk->type != DISKTYPE_FLOPHD) {
        throw ADFException("disk not floppy.");
	}

	bootblock_t boot;
	readbootblock(&boot);

	boot.rootblock = 880;

	uint32_t i;
    for(i = 0; i < 1024-12; i++)	// bootcode
        boot.code[i] = code[i+12];

	writebootblock(&boot);
}

/////////////////////////////////////////////////////////////////////////////
bool Volume::deleteentry(uint32_t blockno, const char *name)
{
	entryblock_t parent, entry;

	readentry(blockno, &parent);

	uint32_t nblock, ublockno;
	if ((nblock = lookup(blockno, name, &entry, &ublockno)) == -1) {
		ADFWarningDispatcher::dispatch("entry not found.");
		return false;
	}

	// if it is a directory, is it empty ?
    if (entry.sectype == ST_DIR) {
		throw ADFException("directory delete not supported.");
    }

	if (ublockno == 0) {	// in parent hashtable
		bool intl = isINTL(type) || isDIRCACHE(type);
		uint32_t hash = adfhash(name, intl);
		parent.tbl[hash] = entry.nextsamehash;
		writeentry(blockno, &parent);
	} else {				// linked list
		entryblock_t previous;
		readentry(ublockno, &previous);
		previous.nextsamehash = entry.nextsamehash;
		writeentry(ublockno, &previous);
	}

	if (entry.sectype == ST_FILE) {
		freefileblocks((fileheader_t*)&entry);		
	} else if (entry.sectype == ST_DIR) {
		// TODO:
		/*
		adfSetBlockFree(vol, nSect);
        // free dir cache block : the directory must be empty, so there's only one cache block
        if (isDIRCACHE(vol->dosType))
            adfSetBlockFree(vol, entry.extension);
        if (adfEnv.useNotify)
            (*adfEnv.notifyFct)(pSect,ST_DIR);
			*/
	} else {
		throw ADFException("entry type not supported.");
	}

	if (isDIRCACHE(type)) {
		delFromCache(&parent, entry.key);
	}

    updatebitmap();

	return true;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writeentry(uint32_t blockno, entryblock_t *e)
{
#ifdef LITTLE_ENDIAN
	swapentry(e);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, e, BSIZE);

	e->checksum = adfchecksum(buf, 20, BSIZE);
	e->checksum = swap_endian(e->checksum);

	writeblock(blockno, e);

#ifdef LITTLE_ENDIAN
	swapentry(e);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
FileBlocks Volume::getFileBlocks(fileheader_t *entry)
{
	FileBlocks blocks;

	blocks.setHeader(entry->key);

	// in file header block
	int32_t i;
	for (i = 0; i < entry->nblocks; i++) {
		blocks.addData(entry->datablocks[MAX_DATABLK-1-i]);
	}

	// in file extension blocks 
	fileext_t extblock;
	uint32_t blockno = entry->extension;
	while (blockno != 0) {
		blocks.addExten(blockno);
		
		readextblock(blockno, &extblock);
		for (i = 0; i < extblock.highseq; i++) {
			blocks.addData(extblock.blocks[MAX_DATABLK-1-i]);
		}
		blockno = extblock.extension;
	}

	return blocks;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::freefileblocks(fileheader_t *entry)
{
	FileBlocks blocks = getFileBlocks(entry);

	block_iterator it = blocks.getDataBegin();
	block_iterator end = blocks.getDataEnd();

	for ( ; it != end; it++) {
		setBlockFree(*it);
	}

	it = blocks.getExtenBegin();
	end = blocks.getExtenEnd();

	for ( ; it != end; it++) {
		setBlockFree(*it);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::delFromCache(entryblock_t *parent, uint32_t key)
{
	uint32_t blockno = parent->extension;

	dircacheblock_t dirc;
	CacheEntry entry;

	bool found = false;
	int32_t offset, last, i;
	int32_t nLen, prevblock = -1;

	do {
		offset = 0;
		readdircblock(blockno, &dirc);
		for (int32_t n = 0; n < dirc.nrecs && !found; n++) {
			last = offset;
			entry = getCacheEntry(&dirc, &offset);
			found = (entry.header == key);
			if (found) {
				nLen = offset - last;
				if (dirc.nrecs > 1 || prevblock == -1) {
					if (n < dirc.nrecs - 1) { // not the last of the block
						for (i = last; i < (OFS_DBSIZE-nLen); i++) {
							dirc.records[i] = dirc.records[i+nLen];
						}
						for (i = OFS_DBSIZE-nLen; i < OFS_DBSIZE; i++) {
							dirc.records[i] = 0;
						}
					} else {	// the last record of this cache block
						for (i = last; i < offset; i++) {
                            dirc.records[i] = 0;
						}
					}
					dirc.nrecs--;
					writedircblock(dirc.key, &dirc);
				} else {
					// dirc.nrecs == 1 or 0, prevblock != -1 :
					// the only record in this dirc block and a previous
					// dirc block exists
					setBlockFree(dirc.key);
					readdircblock(prevblock, &dirc);
					dirc.next = 0;
					writedircblock(prevblock, &dirc);
					updatebitmap();
				}
			}
		}

		prevblock = blockno;
		blockno = dirc.next;
    } while (blockno != 0 && !found);

	if (!found) {
		ADFWarningDispatcher::dispatch("dirc entry not found.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::readdircblock(uint32_t blockno, dircacheblock_t *dirc)
{
	uint8_t buf[BSIZE];

	readblock(blockno, buf);
	memcpy(dirc, buf, BSIZE);

#ifdef LITTLE_ENDIAN
	swapdircblock(dirc);
#endif // LITTLE_ENDIAN

	if (dirc->checksum != adfchecksum(buf, 20, BSIZE)) {
		ADFWarningDispatcher::dispatch("invalid checksum.");
	}

	if (dirc->type != T_DIRC) {
		ADFWarningDispatcher::dispatch("bad dircache block.");
	}

	if (dirc->key != blockno) {
		ADFWarningDispatcher::dispatch("bad dircache block.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Volume::createFile(uint32_t nparent, const char *name, fileheader_t *
	header)
{
	entryblock_t parent;
	readentry(nparent, &parent);

	uint32_t blockno;
	if ((blockno = createEntry(&parent, name, -1)) == -1)
		throw ADFException("can't create entry.");

	memset(header, 0, BSIZE);
	header->namelen = min(MAXNAMELEN, strlen(name));
	memcpy(header->filename, name, header->namelen);
	header->key = blockno;

	if (parent.sectype == ST_ROOT) {
		header->parent = rootblock;
	} else if (parent.sectype == ST_DIR) {
		header->parent = parent.key;
	} else {
		ADFWarningDispatcher::dispatch("unknown sectype.");
	}

	adfTime2AmigaTime(adfGetCurrentTime(), header->days, header->mins,
		header->ticks);

	writefileblock(blockno, header);

	if (isDIRCACHE(type)) {
		// TODO: adfAddInCache(vol, &parent, (struct bEntryBlock *)fhdr);
	}

	updatebitmap();
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writedirblock(uint32_t blockno, dirblock_t* block)
{
	block->type = T_HEADER;
	block->key = 0;
	block->tblsize = 0;
	block->sectype = ST_DIR;

#ifdef LITTLE_ENDIAN
	swapdirblock(block);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, block, BSIZE);

	block->checksum = adfchecksum(buf, 20, sizeof(dirblock_t));
	block->checksum = swap_endian(block->checksum);

	writeblock(blockno, block);

#ifdef LITTLE_ENDIAN
	swapdirblock(block);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Volume::createEntry(entryblock_t *dir, const char *name,
	uint32_t blockno)
{
	bool intl = isINTL(type) || isDIRCACHE(type);
	string uname = adfToUpper(name, intl);
	uint32_t hash = adfhash(name, intl);

    uint32_t nblock = dir->tbl[hash];
	if (nblock == 0) {	// empty
		if (blockno == -1)	{	// allocate new block
			if ((blockno = getFreeBlock()) == -1) {
				throw ADFException("can't allocate block.");
			}
		}		

		dir->tbl[hash] = blockno;
        if (dir->sectype == ST_ROOT) {	// root block
			rootblock_t *root = (rootblock_t*)dir;
			adfTime2AmigaTime(adfGetCurrentTime(), root->cdays, root->cmins, 
				root->cticks);
			writerootblock(rootblock, root);
		} else {	// directory block
			adfTime2AmigaTime(adfGetCurrentTime(), dir->days, dir->mins, dir->ticks);
			writedirblock(dir->key, (dirblock_t*)dir);
        }
		return blockno;
	} 

	entryblock_t uentry;
	string ename;

	do {
		readentry(nblock, &uentry);
		ename = adfToUpper(uentry.name, intl);
		if (ename == uname) {
			throw ADFException("entry already exists.");
		}
		nblock = uentry.nextsamehash;
	} while (nblock != 0);

	if (blockno == -1) {
		if ((blockno = getFreeBlock()) == -1) {
			throw ADFException("can't allocate block.");
		}
	}

	uentry.nextsamehash = blockno;
	if (uentry.sectype == ST_DIR) {
		writedirblock(uentry.key, (dirblock_t*)&uentry);
	} else if (uentry.sectype == ST_FILE) {
		writefileblock(uentry.key, (fileheader_t*)&uentry);
	} else {
		throw ADFException("unknown entry type.");
	}

	return blockno;
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writefileblock(uint32_t blockno, fileheader_t *block)
{
	block->type = T_HEADER;
    block->datasize = 0;
    block->sectype = ST_FILE;

#ifdef LITTLE_ENDIAN
	swapfileblock(block);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, block, BSIZE);

	block->checksum = adfchecksum(buf, 20, sizeof(fileheader_t));
	block->checksum = swap_endian(block->checksum);

	writeblock(blockno, block);

#ifdef LITTLE_ENDIAN
	swapfileblock(block);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writefileextblock(uint32_t blockno, fileext_t *block)
{
	block->type = T_LIST;
    block->sectype = ST_FILE;
    block->datasize = 0;
    block->firstdata = 0;

#ifdef LITTLE_ENDIAN
	swapfileext(block);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, block, BSIZE);

	block->checksum = adfchecksum(buf, 20, sizeof(fileext_t));
	block->checksum = swap_endian(block->checksum);

	writeblock(blockno, block);

#ifdef LITTLE_ENDIAN
	swapfileext(block);
#endif // LITTLE_ENDIAN
}

/////////////////////////////////////////////////////////////////////////////
void Volume::writedatablock(uint32_t blockno, void *block)
{
	if (isOFS(type)) {
		ofsblock_t *data = (ofsblock_t*)block;
		data->type = T_DATA;

#ifdef LITTLE_ENDIAN
	swapofsblock(data);
#endif // LITTLE_ENDIAN

	uint8_t buf[BSIZE];
	memcpy(buf, data, BSIZE);

	data->checksum = adfchecksum(buf, 20, BSIZE);
	data->checksum = swap_endian(data->checksum);

	writeblock(blockno, data);

#ifdef LITTLE_ENDIAN
	swapofsblock(data);
#endif // LITTLE_ENDIAN

	} else {
		writeblock(blockno, block);
	}
}

// helper functions
namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
CacheEntry getCacheEntry(dircacheblock_t *dirc, int32_t *offset)
{
	CacheEntry entry;

	int ptr = *offset;

#ifdef LITTLE_ENDIAN
	entry.header = swap_long(dirc->records+ptr);
	entry.size = swap_long(dirc->records+ptr+4);
	entry.protect = swap_long(dirc->records+ptr+8);
	entry.days = swap_short(dirc->records+ptr+16);
	entry.mins = swap_short(dirc->records+ptr+18);
	entry.ticks = swap_short(dirc->records+ptr+20);
#else
	entry.header = toLong(dirc->records+ptr);
	entry.size = toLong(dirc->records+ptr+4);
	entry.protect = toLong(dirc->records+ptr+8);
	entry.days = toShort(dirc->records+ptr+16);
	entry.mins = toShort(dirc->records+ptr+18);
	entry.ticks = toShort(dirc->records+ptr+20);
#endif // LITTLE_ENDIAN

	entry.type = (signed char) dirc->records[ptr+22];

	uint8_t nLen = dirc->records[ptr+23];
	entry.name = toString(dirc->records+ptr+24, nLen);

	uint8_t cLen = dirc->records[ptr+24+nLen];
	entry.comment = toString(dirc->records+ptr+24+nLen+1, cLen);

	*offset = ptr+24+nLen+1+cLen;

	// the starting offset of each record must be even (68000 constraint)
    if ((*offset % 2) != 0)
        *offset = (*offset) + 1;

	return entry;
}

}	// anonymous

