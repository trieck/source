/*-----------------------------------
	Module	: 	FIVEROW.H
	Purpose	:	Pente five-in-a-row
				module declarations
	Author	: 	Thomas A. Rieck
	Date	:	08/28/1997
-----------------------------------*/

#ifndef _FIVEROW_H_
#define _FIVEROW_H_

#include "wpthk.h"
			
// Exported functions

EXTERNC	int	DllExport CheckFiveInARow(int aBoard[][19], POINT pt, int nCurrentPlayer);

#endif // _FIVEROW_H_