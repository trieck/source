/////////////////
// FIVEROW.CPP //
/////////////////

#include "winpente.h"

//////////////////////////////
// CheckFiveInARow Function //
//////////////////////////////
int CheckFiveInARow(HWND hWnd, POINT c_point)
{
	int opponent, player;
	int i, j;
	char sz_winnermsg[30];

	i = c_point.x;
	j = c_point.y;

	if (p_Box[i][j]->piece == P1PIECE) {
		opponent	= P2PIECE;
		player		= P1PIECE;
		LoadString(hInstance, IDS_PLAYER1WINNER, sz_winnermsg, 30);
	} else {
		opponent	= P1PIECE;
		player		= P2PIECE;
		LoadString(hInstance, IDS_PLAYER2WINNER, sz_winnermsg, 30);
	}

	/* Check for win from far right */

	if ((j >= 4) &&
	        (p_Box[i][j-1]->piece == player &&
	         p_Box[i][j-2]->piece == player &&
	         p_Box[i][j-3]->piece == player &&
	         p_Box[i][j-4]->piece == player)

	        ||
	        /* Check for win from far left */
	        ((j <= 14) &&
	         (p_Box[i][j+1]->piece == player &&
	          p_Box[i][j+2]->piece == player &&
	          p_Box[i][j+3]->piece == player &&
	          p_Box[i][j+4]->piece == player))

	        ||
	        /* Check for win from top most */
	        ((i <= 14) &&
	         (p_Box[i+1][j]->piece == player &&
	          p_Box[i+2][j]->piece == player &&
	          p_Box[i+3][j]->piece == player &&
	          p_Box[i+4][j]->piece == player))

	        ||
	        /* Check for win from bottom most */
	        ((i >= 4) &&
	         (p_Box[i-1][j]->piece == player &&
	          p_Box[i-2][j]->piece == player &&
	          p_Box[i-3][j]->piece == player &&
	          p_Box[i-4][j]->piece == player))

	        ||
	        /* Check for win from 4th position h */
	        ((j >= 3 && j <=17) &&
	         (p_Box[i][j-1]->piece == player &&
	          p_Box[i][j-2]->piece == player &&
	          p_Box[i][j-3]->piece == player &&
	          p_Box[i][j+1]->piece == player))

	        ||
	        /* Check for win from 3rd position h */

	        ((j >= 2 && j <=16) &&
	         (p_Box[i][j-1]->piece == player &&
	          p_Box[i][j-2]->piece == player &&
	          p_Box[i][j+1]->piece == player &&
	          p_Box[i][j+2]->piece == player))

	        ||
	        /* Check for win from 2nd position h */
	        ((j >= 1 && j <=15) &&
	         (p_Box[i][j-1]->piece == player &&
	          p_Box[i][j+1]->piece == player &&
	          p_Box[i][j+2]->piece == player &&
	          p_Box[i][j+3]->piece == player))

	        ||
	        /* Check for win from 4th position v */
	        ((i >= 3 && i <=17) &&
	         (p_Box[i-1][j]->piece == player &&
	          p_Box[i-2][j]->piece == player &&
	          p_Box[i-3][j]->piece == player &&
	          p_Box[i+1][j]->piece == player))

	        ||
	        /* Check for win from 3rd position v */
	        ((i >= 2 && i <=16) &&
	         (p_Box[i-1][j]->piece == player &&
	          p_Box[i-2][j]->piece == player &&
	          p_Box[i+1][j]->piece == player &&
	          p_Box[i+2][j]->piece == player))

	        ||
	        /* Check for win from 2nd position v */
	        ((i >= 1 && i <=15) &&
	         (p_Box[i-1][j]->piece == player &&
	          p_Box[i+1][j]->piece == player &&
	          p_Box[i+2][j]->piece == player &&
	          p_Box[i+3][j]->piece == player))

	        ||
	        /* Check for win from far lower right diagonal */
	        ((i >= 4 && j >= 4) &&
	         (p_Box[i-1][j-1]->piece == player &&
	          p_Box[i-2][j-2]->piece == player &&
	          p_Box[i-3][j-3]->piece == player &&
	          p_Box[i-4][j-4]->piece == player))

	        ||
	        /* Check for win from far lower left diagonal */
	        ((i >= 4 && j <= 14) &&
	         (p_Box[i-1][j+1]->piece == player &&
	          p_Box[i-2][j+2]->piece == player &&
	          p_Box[i-3][j+3]->piece == player &&
	          p_Box[i-4][j+4]->piece == player))

	        ||
	        /* Check for win from far upper right diagonal */
	        ((i <= 14 && j >= 4) &&
	         (p_Box[i+1][j-1]->piece == player &&
	          p_Box[i+2][j-2]->piece == player &&
	          p_Box[i+3][j-3]->piece == player &&
	          p_Box[i+4][j-4]->piece == player))

	        ||
	        /* Check for win from far upper left diagonal */
	        ((i <= 14 && j <= 14) &&
	         ((p_Box[i+1][j+1]->piece == player &&
	           p_Box[i+2][j+2]->piece == player &&
	           p_Box[i+3][j+3]->piece == player &&
	           p_Box[i+4][j+4]->piece == player))

	         ||
	         /* Check for win from 4th position left diagonal */
	         (((i <= 17 && i >=3) && (j <= 15 && j >=1)) &&
	          (p_Box[i-1][j+1]->piece == player &&
	           p_Box[i-2][j+2]->piece == player &&
	           p_Box[i-3][j+3]->piece == player &&
	           p_Box[i+1][j-1]->piece == player))

	         ||
	         /* Check for win from 3rd position left diagonal */
	         (((i <= 16 && i >=2) && (j <= 16 && j >=2)) &&
	          (p_Box[i-1][j+1]->piece == player &&
	           p_Box[i-2][j+2]->piece == player &&
	           p_Box[i+1][j-1]->piece == player &&
	           p_Box[i+2][j-2]->piece == player))

	         ||
	         /* Check for win from 2nd position left diagonal */
	         (((i <= 15 && i >=1) && (j <= 17 && j >=3)) &&
	          (p_Box[i-1][j+1]->piece == player &&
	           p_Box[i+1][j-1]->piece == player &&
	           p_Box[i+2][j-2]->piece == player &&
	           p_Box[i+3][j-3]->piece == player))

	         ||
	         /* Check for win from 4th position right diagonal */
	         (((i >= 3 && i <=17) && (j <= 17 && j >=3)) &&
	          (p_Box[i-1][j-1]->piece == player &&
	           p_Box[i-2][j-2]->piece == player &&
	           p_Box[i-3][j-3]->piece == player &&
	           p_Box[i+1][j+1]->piece == player))

	         ||
	         /* Check for win from 3rd position right diagonal */
	         (((i <= 16 && i >=2) && (j <= 16 && j >=2)) &&
	          (p_Box[i-1][j-1]->piece == player &&
	           p_Box[i-2][j-2]->piece == player &&
	           p_Box[i+1][j+1]->piece == player &&
	           p_Box[i+2][j+2]->piece == player))

	         ||
	         /* Check for win from 2nd position right diagonal */
	         (((i <= 15 && i >=1) && (j <= 15 && j >=1)) &&
	          (p_Box[i-1][j-1]->piece == player &&
	           p_Box[i+1][j+1]->piece == player &&
	           p_Box[i+2][j+2]->piece == player &&
	           p_Box[i+3][j+3]->piece == player)))) {
		Winner = player;
		PlayWave(hWnd, "WINNER", SND_ASYNC | SND_MEMORY);
		MessageBox(hWnd, sz_winnermsg, "Winner", MB_ICONINFORMATION);
		return (1);
	} else
		return (0);
}
