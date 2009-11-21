/*---------------------------------------
	Module	: 	FIVEROW.C
	Purpose	:	Pente five-in-a-row
				module implementation
	Author	: 	Thomas A. Rieck
	Date	:	08/28/1997
---------------------------------------*/

#include "fiverow.h"

/*--------------------------------
	CheckFiveInARow Function
--------------------------------*/

// This function checks if the board index
// passed in (pt) is capable of winning a game.
// If so, the return value is non-zero.
// Otherwise, the return value is zero.
// NOTE ** aBoard[] is the address of the first
// entry into a 19 X 19 integer array holding
// values for marked spaces on the board. 0 representing
// empty space, 1 representing player one, and 2 representing
// player two.  nCurrentPlayer is one of these values.

int DllExport CheckFiveInARow(int aBoard[][19], POINT pt, int nCurrentPlayer)
{
	int 	i, j;
	int 	opponent;
	int 	nRtn = 0;

	i = pt.x;
	j = pt.y;

	switch (nCurrentPlayer) {
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

	// Check for win from far right
	if ((j >= 4) &&
	        (aBoard[i][j-1] == nCurrentPlayer &&
	         aBoard[i][j-2] == nCurrentPlayer &&
	         aBoard[i][j-3] == nCurrentPlayer &&
	         aBoard[i][j-4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from far left
	if ((j <= 14) &&
	        (aBoard[i][j+1] == nCurrentPlayer &&
	         aBoard[i][j+2] == nCurrentPlayer &&
	         aBoard[i][j+3] == nCurrentPlayer &&
	         aBoard[i][j+4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from top most
	if ((i <= 14) &&
	        (aBoard[i+1][j] == nCurrentPlayer &&
	         aBoard[i+2][j] == nCurrentPlayer &&
	         aBoard[i+3][j] == nCurrentPlayer &&
	         aBoard[i+4][j] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from bottom most
	if ((i >= 4) &&
	        (aBoard[i-1][j] == nCurrentPlayer &&
	         aBoard[i-2][j] == nCurrentPlayer &&
	         aBoard[i-3][j] == nCurrentPlayer &&
	         aBoard[i-4][j] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 4th position h
	if ((j >= 3 && j <=17) &&
	        (aBoard[i][j-1] == nCurrentPlayer &&
	         aBoard[i][j-2] == nCurrentPlayer &&
	         aBoard[i][j-3] == nCurrentPlayer &&
	         aBoard[i][j+1] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 3rd position h
	if ((j >= 2 && j <=16) &&
	        (aBoard[i][j-1] == nCurrentPlayer &&
	         aBoard[i][j-2] == nCurrentPlayer &&
	         aBoard[i][j+1] == nCurrentPlayer &&
	         aBoard[i][j+2] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 2nd position h
	if ((j >= 1 && j <=15) &&
	        (aBoard[i][j-1] == nCurrentPlayer &&
	         aBoard[i][j+1] == nCurrentPlayer &&
	         aBoard[i][j+2] == nCurrentPlayer &&
	         aBoard[i][j+3] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 4th position v
	if ((i >= 3 && i <=17) &&
	        (aBoard[i-1][j] == nCurrentPlayer &&
	         aBoard[i-2][j] == nCurrentPlayer &&
	         aBoard[i-3][j] == nCurrentPlayer &&
	         aBoard[i+1][j] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 3rd position v
	if ((i >= 2 && i <=16) &&
	        (aBoard[i-1][j] == nCurrentPlayer &&
	         aBoard[i-2][j] == nCurrentPlayer &&
	         aBoard[i+1][j] == nCurrentPlayer &&
	         aBoard[i+2][j] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 2nd position v
	if ((i >= 1 && i <=15) &&
	        (aBoard[i-1][j] == nCurrentPlayer &&
	         aBoard[i+1][j] == nCurrentPlayer &&
	         aBoard[i+2][j] == nCurrentPlayer &&
	         aBoard[i+3][j] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from far lower right diagonal
	if ((i >= 4 && j >= 4) &&
	        (aBoard[i-1][j-1] == nCurrentPlayer &&
	         aBoard[i-2][j-2] == nCurrentPlayer &&
	         aBoard[i-3][j-3] == nCurrentPlayer &&
	         aBoard[i-4][j-4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from far lower left diagonal
	if ((i >= 4 && j <= 14) &&
	        (aBoard[i-1][j+1] == nCurrentPlayer &&
	         aBoard[i-2][j+2] == nCurrentPlayer &&
	         aBoard[i-3][j+3] == nCurrentPlayer &&
	         aBoard[i-4][j+4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from far upper right diagonal
	if ((i <= 14 && j >= 4) &&
	        (aBoard[i+1][j-1] == nCurrentPlayer &&
	         aBoard[i+2][j-2] == nCurrentPlayer &&
	         aBoard[i+3][j-3] == nCurrentPlayer &&
	         aBoard[i+4][j-4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from far upper left diagonal
	if ((i <= 14 && j <= 14) &&
	        (aBoard[i+1][j+1] == nCurrentPlayer &&
	         aBoard[i+2][j+2] == nCurrentPlayer &&
	         aBoard[i+3][j+3] == nCurrentPlayer &&
	         aBoard[i+4][j+4] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 4th position left diagonal
	if (((i <= 17 && i >=3) && (j <= 15 && j >=1)) &&
	        (aBoard[i-1][j+1] == nCurrentPlayer &&
	         aBoard[i-2][j+2] == nCurrentPlayer &&
	         aBoard[i-3][j+3] == nCurrentPlayer &&
	         aBoard[i+1][j-1] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 3rd position left diagonal
	if (((i <= 16 && i >=2) && (j <= 16 && j >=2)) &&
	        (aBoard[i-1][j+1] == nCurrentPlayer &&
	         aBoard[i-2][j+2] == nCurrentPlayer &&
	         aBoard[i+1][j-1] == nCurrentPlayer &&
	         aBoard[i+2][j-2] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 2nd position left diagonal */
	if (((i <= 15 && i >=1) && (j <= 17 && j >=3)) &&
	        (aBoard[i-1][j+1] == nCurrentPlayer &&
	         aBoard[i+1][j-1] == nCurrentPlayer &&
	         aBoard[i+2][j-2] == nCurrentPlayer &&
	         aBoard[i+3][j-3] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 4th position right diagonal
	if (((i >= 3 && i <=17) && (j <= 17 && j >=3)) &&
	        (aBoard[i-1][j-1] == nCurrentPlayer &&
	         aBoard[i-2][j-2] == nCurrentPlayer &&
	         aBoard[i-3][j-3] == nCurrentPlayer &&
	         aBoard[i+1][j+1] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 3rd position right diagonal
	if (((i <= 16 && i >=2) && (j <= 16 && j >=2)) &&
	        (aBoard[i-1][j-1] == nCurrentPlayer &&
	         aBoard[i-2][j-2] == nCurrentPlayer &&
	         aBoard[i+1][j+1] == nCurrentPlayer &&
	         aBoard[i+2][j+2] == nCurrentPlayer)) {
		nRtn++;
	}

	// Check for win from 2nd position right diagonal
	if (((i <= 15 && i >=1) && (j <= 15 && j >=1)) &&
	        (aBoard[i-1][j-1] == nCurrentPlayer &&
	         aBoard[i+1][j+1] == nCurrentPlayer &&
	         aBoard[i+2][j+2] == nCurrentPlayer &&
	         aBoard[i+3][j+3] == nCurrentPlayer)) {
		nRtn++;
	}

	return nRtn;
}