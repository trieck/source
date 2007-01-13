/*---------------------------------------
	Module	: 	CAPTURE.C
	Purpose	:	Pente capture
				module implementation
	Author	: 	Thomas A. Rieck
	Date	:	08/24/1997
---------------------------------------*/

#include "capture.h"

/*--------------------------------
	CheckCapture Function 
--------------------------------*/

// This function checks if the board index
// passed in (pt) is capable of capturing a pair(s)
// of pieces on the board.  If so, the pair(s)
// are set to a value of FREE_FOR_ALL, and the 
// return value is set to the number of pairs 
// captured. Otherwise, the return value is zero.  
// NOTE ** aBoard[] is the address of the first
// entry into a 19 X 19 integer array holding 
// values for marked spaces on the board. 0 representing
// empty space, 1 representing player one, and 2 representing
// player two.  nCurrentPlayer is one of these values.

int DllExport CheckCapture(int aBoard[][19], LPPOINT ppt, int nCurrentPlayer)
{
	int 	i, j;
	int 	opponent;
	int 	nRtn = 0;

	POINT	dPoints[2];

	i = ppt->x;
	j = ppt->y;
	
	switch (nCurrentPlayer)
	{
	case PLAYER_ONE:
		opponent = PLAYER_TWO;
		break;
	case PLAYER_TWO:
		opponent = PLAYER_ONE;
		break;
	case FREE_FOR_ALL:
	default:
		return nRtn;
	};

	// Check for capturing from below
	if (i >= 3)
	{
		if (aBoard[i-1][j] == opponent &&
			aBoard[i-2][j] == opponent &&
			aBoard[i-3][j] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j, i-1, j, i-2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for capture from above 
	if (i <= 15)
	{
		if (aBoard[i+1][j] == opponent &&
			aBoard[i+2][j] == opponent &&
			aBoard[i+3][j] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j, i+1, j, i+2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for capture from right
	if (j >= 3)
	{
		if (aBoard[i][j-1] == opponent &&
			aBoard[i][j-2] == opponent &&
			aBoard[i][j-3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j-1, i, j-2, i);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for Capture from left
	if (j <= 15)
	{
		if (aBoard[i][j+1] == opponent &&
			aBoard[i][j+2] == opponent &&
			aBoard[i][j+3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j+1, i, j+2, i);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for diagonal capture from bottom left 
	if (i >= 3 && j <= 15)
	{
		if (aBoard[i-1][j+1] == opponent &&
			aBoard[i-2][j+2] == opponent &&
			aBoard[i-3][j+3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j+1, i-1, j+2, i-2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for diagonal capture from bottom right 
	if (i >= 3 && j >= 3)
	{
		if (aBoard[i-1][j-1] == opponent &&
			aBoard[i-2][j-2] == opponent &&
			aBoard[i-3][j-3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j-1, i-1, j-2, i-2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for diagonal capture from top left 
	if (i <=15 && j <= 15)
	{
		if (aBoard[i+1][j+1] == opponent &&
			aBoard[i+2][j+2] == opponent &&
			aBoard[i+3][j+3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j+1, i+1,j+2,i+2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	// Check for diagonal capture from top right 
	if (i <= 15 && j >= 3)
	{
		if (aBoard[i+1][j-1] == opponent &&
			aBoard[i+2][j-2] == opponent &&
			aBoard[i+3][j-3] == nCurrentPlayer)
		{
			SetPointPair(dPoints, j-1, i+1, j-2, i+2);
			ClearPair(aBoard, dPoints);
			nRtn++;
		}
	}

	return nRtn;
}

/*-----------------------------------------
	Function	:	SetPointPair()
	Purpose		:	Set integers into 
					POINT structure
------------------------------------------*/
void SetPointPair(POINT pt[], int x1, int y1, int x2, int y2)
{
	pt[0].x	= x1;
	pt[0].y	= y1;
	pt[1].x	= x2;
	pt[1].y	= y2;
}

/*-----------------------------------------
	Function	:	ClearPair()
	Purpose		:	Clears a pair of 
					pieces from the board
------------------------------------------*/
void ClearPair(int aBoard[][19], POINT pt[])
{
	int i;

	for (i = 0; i < 2; i++)
		aBoard[pt[i].y][pt[i].x] = FREE_FOR_ALL;
}