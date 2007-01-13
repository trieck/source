/*-------------------------------------------
	Module	:	OurTypes.h
	Purpose	:	Global Data Types
	Date	:	09/01/1997
-------------------------------------------*/

#ifndef _OURTYPES_H_
#define _OURTYPES_H_

#include "afxwin.h"

typedef void ** PPVOID;
typedef BYTE ** PPBYTE;

typedef struct
{
	BYTE	bPiece;			// Current piece
	CRect	rcDims;			// Dimensions
} SQUARE, *LPSQUARE;

typedef struct
{
	CWnd*	pWnd;
	INT		nResource;
}PLAYERPIECE, *LPPLAYERPIECE;

#endif // _OURTYPES_H_