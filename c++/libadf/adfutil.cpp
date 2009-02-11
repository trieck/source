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
uint32_t bootsum(void *block)
{
    uint32_t d, sum = 0;
    
    for (int i = 0; i < BOOTBLOCKSIZE/4; i++) {
		if (i == 1) continue;
		d = MAKELONG(((uint8_t*)block)+i*4);
		if ((ULONG_MAX - sum) < d)
			sum++;
		sum += d;
    }
    
    return ~sum;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t adfchecksum(void *block, uint32_t offset, uint32_t len)
{
	int32_t sum = 0;

	for (uint32_t i = 0; i < len/4; i++) {
		if (i != (offset/4))	/* old chksum */
            sum += MAKELONG(((uint8_t*)block)+i*4);
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
