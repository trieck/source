/*-----------------------------------
	Module	: 	CAPTURE.H
	Purpose	:	Pente capture
				module declarations
	Author	: 	Thomas A. Rieck
	Date	:	08/24/1997
-----------------------------------*/

#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include "wpthk.h"

// Local functions
void			SetPointPair(POINT pt[], int x1, int y1, int x2, int y2);
void			ClearPair(int aBoard[][19], POINT pt[]); 
			
// Exported functions
EXTERNC	int	DllExport CheckCapture(int aBoard[][19], LPPOINT ppt, int nCurrentPlayer);

#endif // _CAPTURE_H_