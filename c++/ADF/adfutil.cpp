/////////////////////////////////////////////////////////////////////////////
//
// ADFUTIL.CPP : ADF utility functions
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "adfutil.h"
#include <limits.h>

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
uint32_t bootsum(uint8_t *block)
{
    uint32_t d, sum = 0;
    
    for (int i = 0; i < BOOTBLOCKSIZE/4; i++) {
		if (i != 1) {
			d = MAKELONG(block+i*4);
			if ((ULONG_MAX - sum) < d)
                sum++;
            sum += d;
		}
    }
    
    return ~sum;
}