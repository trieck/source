/////////////////////////////////////////////////////////////////////////////
//
// ADFUTIL.H : ADF utility functions
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#ifndef __ADFUTIL_H_INCLUDED
#define __ADFUTIL_H_INCLUDED

#define MAKEWORD(p) (((uint8_t*)p)[0]<<8 | ((uint8_t*)p)[1])
#define MAKELONG(p) (MAKEWORD(p)<<16 | MAKEWORD(((uint8_t*)p)+2))

/////////////////////////////////////////////////////////////////////////////
int swap_endian(int d);
uint32_t bootsum(uint8_t *block);
uint32_t adfchecksum(uint8_t *block, uint32_t offset, uint32_t len);

#endif // __ADFUTIL_H_INCLUDED