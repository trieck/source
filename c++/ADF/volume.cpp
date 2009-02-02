/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.CPP : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "adfutil.h"
#include "adfexcept.h"
#include "disk.h"
#include "volume.h"
#include "adfwarn.h"

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

/////////////////////////////////////////////////////////////////////////////
Volume::Volume()
: blocksize(0), bitmapsize(0), dblocksize(0), firstblock(0), lastblock(0), 
 rootblock(0), type(0), mounted(false), bmtbl(0), bmblocks(0), disk(0)
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
	root->type = swap_endian(root->type);
	root->hkey = swap_endian(root->hkey);
	root->highseq = swap_endian(root->highseq);
	root->tblsize = swap_endian(root->tblsize);
	root->firstdata = swap_endian(root->firstdata);
	root->checksum = swap_endian(root->checksum);

	uint32_t i;
	for (i = 0; i < HT_SIZE; i++)
		root->tbl[i] = swap_endian(root->tbl[i]);

	root->bmflag = swap_endian(root->bmflag);
	for (i = 0; i < BM_SIZE; i++)
		root->bmpages[i] = swap_endian(root->bmpages[i]);

	root->bmext = swap_endian(root->bmext);
	root->cdays = swap_endian(root->cdays);
	root->cmins = swap_endian(root->cmins);
	root->cticks = swap_endian(root->cticks);
	root->days = swap_endian(root->days);
	root->mins = swap_endian(root->mins);
	root->ticks = swap_endian(root->ticks);
	root->codays = swap_endian(root->codays);
	root->comins = swap_endian(root->comins);
	root->coticks = swap_endian(root->coticks);
	root->nextsamehash = swap_endian(root->nextsamehash);
	root->parent = swap_endian(root->parent);
	root->extension = swap_endian(root->extension);
	root->sectype = swap_endian(root->sectype);
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
void Volume::readbitmap(rootblock_t *root)
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
	bm->checksum = swap_endian(bm->checksum);
	uint32_t i;
	for (i = 0; i < BM_MAPSIZE; i++)
		bm->map[i] = swap_endian(bm->map[i]);
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
	e->type = swap_endian(e->type);
	e->key = swap_endian(e->key);
	e->checksum = swap_endian(e->checksum);
	
	uint32_t i;
	for (i = 0; i < HT_SIZE; i++) {
		e->tbl[i] = swap_endian(e->tbl[i]);
	}
	
	e->access = swap_endian(e->access);
	e->bytesize = swap_endian(e->bytesize);
	e->days = swap_endian(e->days);
	e->mins = swap_endian(e->mins);
	e->ticks = swap_endian(e->ticks);
	e->realentry = swap_endian(e->realentry);
	e->nextlink = swap_endian(e->nextlink);
	e->nextsamehash = swap_endian(e->nextsamehash);
	e->parent = swap_endian(e->parent);
	e->extension = swap_endian(e->extension);
	e->sectype = swap_endian(e->sectype);
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

	// TODO: dircache

	entryblock_t parent, entryblk;
	readentry(blockno, &parent);

	int32_t *hashtable = parent.tbl;
    for (uint32_t i = 0; i < HT_SIZE; i++) {
		if (hashtable[i] != 0) {
			readentry(hashtable[i], &entryblk);

			// if (adfEntBlock2Entry(&entryBlk, entry)!=RC_OK) {
			// entry->sector = hashTable[i];

			// if (recurs && entry->type==ST_DIR)

				/* same hashcode linked list */
			/*
             nextSector = entryBlk.nextSameHash;
             while( nextSector!=0 ) {
                 entry = (struct Entry *)malloc(sizeof(struct Entry));
                 if (!entry) {
                     adfFreeDirList(head);
					 (*adfEnv.eFct)("adfGetDirEnt : malloc");
                     return NULL;
                 }
                 if (adfReadEntryBlock(vol, nextSector, &entryBlk)!=RC_OK) {
					 adfFreeDirList(head); return NULL;
                 }

                 if (adfEntBlock2Entry(&entryBlk, entry)!=RC_OK) {
					 adfFreeDirList(head);
                     return NULL;
                 }
                 entry->sector = nextSector;
	
                 cell = newCell(cell, (void*)entry);
                 if (cell==NULL) {
                     adfFreeDirList(head); return NULL;
                 }
				 
                 if (recurs && entry->type==ST_DIR)
                     cell->subdir = adfGetRDirEnt(vol,entry->sector,recurs);
				 
                 nextSector = entryBlk.nextSameHash;
             }*/
		}


	}
	
	return entries;
}