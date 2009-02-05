/////////////////////////////////////////////////////////////////////////////
//
// ENTRY.CPP : ADF entry definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "entry.h"
#include "adfwarn.h"
#include "adfutil.h"

/////////////////////////////////////////////////////////////////////////////
Entry::Entry() : access(0), blockno(0), days(0), hour(0), mins(0), month(0),
 parent(0), real(0), secs(0), size(0), type(0), year(0), firstblock(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Entry::~Entry()
{
}

/////////////////////////////////////////////////////////////////////////////
Entry::Entry(const Entry &e)
{ 
	*this = e;
}

/////////////////////////////////////////////////////////////////////////////
Entry::Entry(const entryblock_t &block)
{ 
	*this = block;
}

/////////////////////////////////////////////////////////////////////////////
Entry& Entry::operator = (const Entry &e)
{
	if (this != &e) {
		type = e.type;
		name = e.name;
		blockno = e.blockno;
		real = e.real;
		parent = e.parent;
		firstblock = e.firstblock;
		comment = e.comment;
		size = e.size;
		access = e.access;
		year = e.year;
		month = e.month;		
		days = e.days;
		hour = e.hour;
		mins = e.mins;		
		secs = e.secs;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
Entry& Entry::operator = (const entryblock_t &block)
{
	type = block.sectype;
	parent = block.parent;
	firstblock = block.firstblock;
	name = string(block.name, block.namelen);

	ADFDate date = adfDays2Date(block.days);

	year = date.year;
	month = date.month;
	days = date.days;
	hour = block.mins / 60;
	mins = block.mins % 60;
	secs = block.ticks / 50;
	access = -1;
	size = 0;
	comment.clear();
	real = 0;

	switch(block.sectype) {
    case ST_ROOT:
        break;
    case ST_DIR:
        access = block.access;
		comment = string(block.comment, block.commlen);
        break;
    case ST_FILE:
		access = block.access;
		size = block.bytesize;
		comment = string(block.comment, block.commlen);
        break;
    case ST_LFILE:
    case ST_LDIR:
		real = block.realentry;
    case ST_LSOFT:
        break;
    default:
		ADFWarningDispatcher::dispatch("unknown entry type.");
    }

	return *this;
}
