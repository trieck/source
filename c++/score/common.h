/////////////////////////////////////////////////////////////////////////////
//
//	COMMON.H
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __COMMON_H__
#define __COMMON_H__

/////////////////////////////////////////////////////////////////////////////
// Duration enumeration
typedef enum {
    EmptyNote = 0,
    WholeNote = 1,
    HalfNote = 2,
    QuarterNote = 4,
    EigthNote = 8,
    SixteenthNote = 16,
    ThirtySecondNote = 32
} Duration;

#define COLOR_WHITE     RGB(255, 255, 255)
#define DEFAULT_TEMPO   120

/////////////////////////////////////////////////////////////////////////////


#endif // __COMMON_H__