/////////////////////////////////////////////////////////////////////////////
//
// ENTRY.H : ADF entry definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ENTRY_H__
#define __ENTRY_H__

/////////////////////////////////////////////////////////////////////////////
class Entry 
{
// Construction / Destruction
public:
	Entry();
	Entry(const Entry &e);
	Entry(const entryblock_t &block);
	~Entry();

// Interface
	Entry& operator = (const Entry &e);
	Entry& operator = (const entryblock_t &block);

// Implementation
public:
	int32_t type;			// entry type, ST_DIR or ST_FILE
	string name;			// entry name
	uint32_t blockno;		// block where entry is located
	uint32_t real;			// real size of the entry
	uint32_t parent;		// location of parent directory
	uint32_t firstblock;	// first data block location
	string comment;			// optional comment
	uint32_t size;			// file size, 0 for directory
	int32_t access;			// RWEDAPSH access flags
	int32_t year;			// date
	int32_t month;		
	int32_t days;
	int32_t hour;			// time
	int32_t mins;		
	int32_t secs;
};

typedef vector<Entry> EntryList;

#endif // __ENTRY_H__
