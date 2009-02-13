/////////////////////////////////////////////////////////////////////////////
//
// ADFUTIL.CPP : ADF utility functions
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#include "common.h"
#include "adf.h"
#include "adfutil.h"
#include "adfexcept.h"
#include <limits.h>
#include <time.h>

#define MAKEWORD(p) (((uint8_t*)p)[0]<<8 | ((uint8_t*)p)[1])
#define MAKELONG(p) (MAKEWORD(p)<<16 | MAKEWORD(((uint8_t*)p)+2))

#define SWAPWORD(p) (((uint8_t*)p)[0]<<8 | ((uint8_t*)p)[1])
#define SWAPLONG(p) (SWAPWORD(p)<<16 | SWAPWORD(((uint8_t*)p)+2))

/////////////////////////////////////////////////////////////////////////////
int swap_endian(int d)
{
	unsigned char buffer[sizeof (int)];
	buffer [0] = (char) (d >> 24) & 0xff;
	buffer [1] = (char) (d >> 16) & 0xff;
	buffer [2] = (char) (d >> 8) & 0xff;
	buffer [3] = (char) d;
	return *(int*)buffer;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t swap_long(void *p)
{
	return MAKELONG(p);
}

/////////////////////////////////////////////////////////////////////////////
uint16_t swap_short(void *p)
{
	return MAKEWORD(p);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t toLong(void *p)
{
	return MAKELONG(p);
}

/////////////////////////////////////////////////////////////////////////////
uint16_t toWord(void *p)
{
	return MAKEWORD(p);
}

/////////////////////////////////////////////////////////////////////////////
string toString(void *p, uint32_t len)
{
	return string((const char *)p, len);
}

/////////////////////////////////////////////////////////////////////////////
uint32_t bootsum(uint8_t *block)
{
    uint32_t d, sum = 0;
    
    for (int i = 0; i < BOOTBLOCKSIZE/4; i++) {
		if (i == 1) continue;
		d = MAKELONG(block+i*4);
		if ((ULONG_MAX - sum) < d)
			sum++;
		sum += d;
    }
    
    return ~sum;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t adfchecksum(uint8_t *block, uint32_t offset, uint32_t len)
{
	int32_t sum = 0;

	for (uint32_t i = 0; i < len/4; i++) {
		if (i != (offset/4))	/* old chksum */
            sum += MAKELONG(block+i*4);
	}
    
    return -sum;
}

/////////////////////////////////////////////////////////////////////////////
void * xmalloc(uint32_t size)
{
	void *p; 
	
	if ((p = malloc(size)) == NULL) 
		throw ADFException();

	return p;
}

/////////////////////////////////////////////////////////////////////////////
bool adfIsLeap(int32_t y)
{
    return (!(y % 100) ? ! (y % 400) : !(y % 4));
}

/////////////////////////////////////////////////////////////////////////////
ADFDate adfDays2Date(int32_t days)
{
	ADFDate date;

	int jm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int32_t nd = 365;
	int32_t year = 1978;

	if (adfIsLeap(year))
		nd++;

	// year
	while (days >= nd) {
		days -= nd;
		year++;
		nd = adfIsLeap(year) ? 366 : 365;
	}

	// month 
    int32_t month = 1;
    if (adfIsLeap(year))
        jm[2-1] = 29;

    while (days >= jm[month-1] ) {
        days -= jm[month-1];
        month++;
    }

	date.year = year;
	date.month = month;
	date.days = days + 1;

	return date;
}

/////////////////////////////////////////////////////////////////////////////
char adfIntlToUpper(char c)
{
	return (c >= 'a' && c <= 'z') 
		|| (c >= 224 && c <= 254 && c != 247) 
		? c - ('a' - 'A') : c ;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t adfhash(const char *k, bool intl)
{
	uint32_t hash, len;
    uint32_t i;
    char upper;

    len = hash = strlen(k);

    for (i = 0; i < len; i++) {
        if (intl)
            upper = adfIntlToUpper(k[i]);
        else
            upper = toupper(k[i]);

        hash = (hash * 13 + upper) & 0x7ff;
    }

	hash = hash % HT_SIZE;

    return hash;
}

/////////////////////////////////////////////////////////////////////////////
string adfToUpper(const char *str, bool intl)
{
	string output;

    uint32_t i, nlen = strlen(str);

	if (intl) {
		for (i = 0; i < nlen; i++) {
            output += adfIntlToUpper(str[i]);
		}
	} else {
		for (i = 0; i < nlen; i++) {
            output += toupper(str[i]);
		}
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string adfaccess(int32_t acc)
{
    char ret[8+1];

    strcpy(ret,"----rwed");
    if (hasD(acc)) ret[7]='-';
    if (hasE(acc)) ret[6]='-';
    if (hasW(acc)) ret[5]='-';
    if (hasR(acc)) ret[4]='-';
    if (hasA(acc)) ret[3]='a';
    if (hasP(acc)) ret[2]='p';
    if (hasS(acc)) ret[1]='s';
    if (hasH(acc)) ret[0]='h';

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
ADFDateTime adfGetCurrentTime()
{
	ADFDateTime dt;

    time_t cal;
	time(&cal);
        
    struct tm *local = localtime(&cal);

	dt.year = local->tm_year;         // since 1900 
    dt.month = local->tm_mon+1;
    dt.day = local->tm_mday;
    dt.hour = local->tm_hour;
    dt.min = local->tm_min;
    dt.sec = local->tm_sec;

	return dt;
}

/////////////////////////////////////////////////////////////////////////////
void adfTime2AmigaTime(ADFDateTime dt, int32_t &day, int32_t &min, 
	int32_t &ticks)
{
    int jm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    min = dt.hour * 60 + dt.min;	//mins
    ticks = dt.sec*50;				// ticks

	// days

    day = dt.day - 1;	// current month days

    // previous months days down to january
    if (dt.month > 1) {	// if previous month exists
        dt.month--;
        if (dt.month > 2 && adfIsLeap(dt.year))	// months after a leap february
            jm[2-1] = 29;
        while (dt.month > 0) {
            day = day + jm[dt.month-1];
            dt.month--;
        }
    }

    // years days before current year down to 1978 
    if (dt.year > 78) {
        dt.year--;
        while (dt.year >= 78) {
            if (adfIsLeap(dt.year))
                day = day+366;
            else
                day = day+365;
            dt.year--;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void swapfileblock(fileheader_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->nblocks = swap_endian(block->nblocks);
	block->firstblock = swap_endian(block->firstblock);
	block->checksum = swap_endian(block->checksum);

	for (uint32_t i = 0; i < MAX_DATABLK; i++)
		block->datablocks[i] = swap_endian(block->datablocks[i]);

	block->access = swap_endian(block->access);
	block->bytesize = swap_endian(block->bytesize);
	block->days = swap_endian(block->days);
	block->mins = swap_endian(block->mins);
	block->ticks = swap_endian(block->ticks);
	block->nextlink = swap_endian(block->nextlink);
	block->nexthash = swap_endian(block->nexthash);
	block->parent = swap_endian(block->parent);
	block->extension = swap_endian(block->extension);
	block->sectype = swap_endian(block->sectype);
}

/////////////////////////////////////////////////////////////////////////////
void swapofsblock(ofsblock_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->seqnum = swap_endian(block->seqnum);
	block->size = swap_endian(block->size);
	block->next = swap_endian(block->next);
	block->checksum = swap_endian(block->checksum);
}

/////////////////////////////////////////////////////////////////////////////
void swaprootblock(rootblock_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->highseq = swap_endian(block->highseq);
	block->tblsize = swap_endian(block->tblsize);
	block->firstdata = swap_endian(block->firstdata);
	block->checksum = swap_endian(block->checksum);

	uint32_t i;
	for (i = 0; i < HT_SIZE; i++)
		block->tbl[i] = swap_endian(block->tbl[i]);

	block->bmflag = swap_endian(block->bmflag);
	for (i = 0; i < BM_SIZE; i++)
		block->bmpages[i] = swap_endian(block->bmpages[i]);

	block->bmext = swap_endian(block->bmext);
	block->cdays = swap_endian(block->cdays);
	block->cmins = swap_endian(block->cmins);
	block->cticks = swap_endian(block->cticks);
	block->days = swap_endian(block->days);
	block->mins = swap_endian(block->mins);
	block->ticks = swap_endian(block->ticks);
	block->codays = swap_endian(block->codays);
	block->comins = swap_endian(block->comins);
	block->coticks = swap_endian(block->coticks);
	block->nextsamehash = swap_endian(block->nextsamehash);
	block->parent = swap_endian(block->parent);
	block->extension = swap_endian(block->extension);
	block->sectype = swap_endian(block->sectype);
}

/////////////////////////////////////////////////////////////////////////////
void swapbmblock(bitmapblock_t *block)
{
	block->checksum = swap_endian(block->checksum);
	uint32_t i;
	for (i = 0; i < BM_MAPSIZE; i++)
		block->map[i] = swap_endian(block->map[i]);
}

/////////////////////////////////////////////////////////////////////////////
void swapentry(entryblock_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	
	uint32_t i;
	for (i = 0; i < 2; i++) {
		block->r1[i] = swap_endian(block->r1[i]);
	}
	
	block->firstblock = swap_endian(block->firstblock);
	block->checksum = swap_endian(block->checksum);
	for (i = 0; i < HT_SIZE; i++) {
		block->tbl[i] = swap_endian(block->tbl[i]);
	}
	
	for (i = 0; i < 2; i++) {
		block->r2[i] = swap_endian(block->r2[i]);
	}

	block->access = swap_endian(block->access);
	block->bytesize = swap_endian(block->bytesize);
	block->days = swap_endian(block->days);
	block->mins = swap_endian(block->mins);
	block->ticks = swap_endian(block->ticks);
	block->r4 = swap_endian(block->r4);
	block->realentry = swap_endian(block->realentry);
	block->nextlink = swap_endian(block->nextlink);

	for (i = 0; i < 5; i++) {
		block->r5[i] = swap_endian(block->r5[i]);
	}

	block->nextsamehash = swap_endian(block->nextsamehash);
	block->parent = swap_endian(block->parent);
	block->extension = swap_endian(block->extension);
	block->sectype = swap_endian(block->sectype);
}

/////////////////////////////////////////////////////////////////////////////
void swapfileext(fileext_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->highseq = swap_endian(block->highseq);
	block->checksum = swap_endian(block->checksum);

	for (uint32_t i = 0; i < MAX_DATABLK; i++) 
		block->blocks[i] = swap_endian(block->blocks[i]);

	block->parent = swap_endian(block->parent);
	block->extension = swap_endian(block->extension);
	block->sectype = swap_endian(block->sectype);
}

/////////////////////////////////////////////////////////////////////////////
void swapdircblock(dircacheblock_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->parent = swap_endian(block->parent);
	block->nrecs = swap_endian(block->nrecs);
	block->next = swap_endian(block->next);
	block->checksum = swap_endian(block->checksum);
}

/////////////////////////////////////////////////////////////////////////////
void swapbmext(bitmapextblock_t *block)
{
	for (uint32_t i = 0; i < BM_MAPSIZE; i++) {
		block->pages[i] = swap_endian(block->pages[i]);
	}
	block->next = swap_endian(block->next);
}

/////////////////////////////////////////////////////////////////////////////
void swapdirblock(dirblock_t *block)
{
	block->type = swap_endian(block->type);
	block->key = swap_endian(block->key);
	block->highseq = swap_endian(block->highseq);
	block->tblsize = swap_endian(block->tblsize);
	block->r1 = swap_endian(block->r1);
	block->checksum = swap_endian(block->checksum);

	uint32_t i;
	for (i = 0; i < HT_SIZE; i++) {
		block->tbl[i] = swap_endian(block->tbl[i]);
	}

	for (i = 0; i < 2; i++) {
		block->r2[i] = swap_endian(block->r2[i]);
	}

	block->access = swap_endian(block->access);

	for (i = 0; i < 2; i++) {
		block->r2[i] = swap_endian(block->r2[i]);
	}

	for (i = 0; i < 11; i++) {
		block->r5[i] = swap_endian(block->r5[i]);
	}

	block->days = swap_endian(block->days);
	block->mins = swap_endian(block->mins);
	block->ticks = swap_endian(block->ticks);
	
	block->r6 = swap_endian(block->r6);
	block->real = swap_endian(block->real);
	block->nextlink = swap_endian(block->nextlink);

	for (i = 0; i < 5; i++) {
		block->r7[i] = swap_endian(block->r7[i]);
	}

	block->nextsamehash = swap_endian(block->nextsamehash);
	block->parent = swap_endian(block->parent);
	block->extension = swap_endian(block->extension);
	block->sectype = swap_endian(block->sectype);
}
