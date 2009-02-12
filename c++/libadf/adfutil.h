/////////////////////////////////////////////////////////////////////////////
//
// ADFUTIL.H : ADF utility functions
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __ADFUTIL_H_INCLUDED
#define __ADFUTIL_H_INCLUDED

#ifndef min
#define min(a,b)    (((a)<(b))?(a):(b))
#define max(a,b)    (((a)>(b))?(a):(b))
#endif // min

/////////////////////////////////////////////////////////////////////////////
struct ADFDate {
	int32_t year;
	int32_t month;
	int32_t days;
};

/////////////////////////////////////////////////////////////////////////////
struct ADFDateTime {
	int32_t year;
	int32_t month;
	int32_t day;
	int32_t hour;
	int32_t min;
	int32_t sec;
};

ADFDate adfDays2Date(int32_t days);
ADFDateTime adfGetCurrentTime();
void adfTime2AmigaTime(ADFDateTime dt, int32_t &day, int32_t &min, 
	int32_t &ticks);
int swap_endian(int d);
uint32_t bootsum(uint8_t *block);
uint32_t adfchecksum(uint8_t *block, uint32_t offset, uint32_t len);
void * xmalloc(uint32_t size);
uint32_t adfhash(const char *k, bool intl);
string adfToUpper(const char *str, bool intl);
string adfaccess(int32_t access);

#endif // __ADFUTIL_H_INCLUDED