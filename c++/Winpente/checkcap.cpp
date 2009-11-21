//////////////////
// CHECKCAP.CPP //
//////////////////

#include "winpente.h"

///////////////////////////
// CheckCapture Function //
///////////////////////////
int CheckCapture(HWND hWnd, POINT c_point)
{
	int opponent, player;
	int i, j;
	POINT d_pieces[2];
	char sz_p1captures[30];
	char sz_p2captures[30];
	char sz_winnermsg[30];
	char sz_buffer[25];

	i = c_point.x;
	j = c_point.y;

	if (p_Box[i][j]->piece == P1PIECE) {
		opponent	= P2PIECE;
		player		= P1PIECE;
	} else {
		opponent	= P1PIECE;
		player		= P2PIECE;
	}

	/* Check for capture from below */
	if (i >= 3) {
		if (p_Box[i-1][j]->piece == opponent &&
		        p_Box[i-2][j]->piece == opponent &&
		        p_Box[i-3][j]->piece == player) {
			d_pieces[0].x = j;
			d_pieces[0].y = i-1;
			d_pieces[1].x = j;
			d_pieces[1].y = i-2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}
	/* Check for capture from above */
	if (i <=15) {
		if (p_Box[i+1][j]->piece == opponent &&
		        p_Box[i+2][j]->piece == opponent &&
		        p_Box[i+3][j]->piece == player) {
			d_pieces[0].x = j;
			d_pieces[0].y = i+1;
			d_pieces[1].x = j;
			d_pieces[1].y = i+2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for Capture from right*/
	if (j >=3) {
		if (p_Box[i][j-1]->piece == opponent &&
		        p_Box[i][j-2]->piece == opponent &&
		        p_Box[i][j-3]->piece == player) {
			d_pieces[0].x = j-1;
			d_pieces[0].y = i;
			d_pieces[1].x = j-2;
			d_pieces[1].y = i;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for Capture from left*/
	if (j <=15) {
		if (p_Box[i][j+1]->piece == opponent &&
		        p_Box[i][j+2]->piece == opponent &&
		        p_Box[i][j+3]->piece == player) {
			d_pieces[0].x = j+1;
			d_pieces[0].y = i;
			d_pieces[1].x = j+2;
			d_pieces[1].y = i;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for diagonal capture from bottom left */
	if (i >= 3 && j <= 15) {
		if (p_Box[i-1][j+1]->piece == opponent &&
		        p_Box[i-2][j+2]->piece == opponent &&
		        p_Box[i-3][j+3]->piece == player) {
			d_pieces[0].x = j+1;
			d_pieces[0].y = i-1;
			d_pieces[1].x = j+2;
			d_pieces[1].y = i-2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for diagonal capture from bottom right */
	if (i >= 3 && j >= 3) {
		if (p_Box[i-1][j-1]->piece == opponent &&
		        p_Box[i-2][j-2]->piece == opponent &&
		        p_Box[i-3][j-3]->piece == player) {
			d_pieces[0].x = j-1;
			d_pieces[0].y = i-1;
			d_pieces[1].x = j-2;
			d_pieces[1].y = i-2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for diagonal capture from top left */
	if (i <=15 && j <= 15) {
		if (p_Box[i+1][j+1]->piece == opponent &&
		        p_Box[i+2][j+2]->piece == opponent &&
		        p_Box[i+3][j+3]->piece == player) {
			d_pieces[0].x = j+1;
			d_pieces[0].y = i+1;
			d_pieces[1].x = j+2;
			d_pieces[1].y = i+2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}

	/* Check for diagonal capture from top right */
	if (i <= 15 && j >= 3) {
		if (p_Box[i+1][j-1]->piece == opponent &&
		        p_Box[i+2][j-2]->piece == opponent &&
		        p_Box[i+3][j-3]->piece == player) {
			d_pieces[0].x = j-1;
			d_pieces[0].y = i+1;
			d_pieces[1].x = j-2;
			d_pieces[1].y = i+2;

			if (player == P1PIECE)
				p_Board->p1_captures++;
			else
				p_Board->p2_captures++;

			ErasePieces(hWnd, d_pieces);
		}
	}
	LoadString(hInstance, IDS_P1CAPTURES, sz_buffer, 25);
	sprintf(sz_p1captures, "%s%d", sz_buffer, p_Board->p1_captures);

	LoadString(hInstance, IDS_P2CAPTURES, sz_buffer, 25);
	sprintf(sz_p2captures, "%s%d", sz_buffer, p_Board->p2_captures);
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 1, (LPARAM)sz_p1captures);
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 2, (LPARAM)sz_p2captures);

	if (p_Board->p1_captures > 4) {
		LoadString(hInstance,
		           IDS_PLAYER1WINNER, sz_winnermsg,
		           30);
		Winner = 1;
		PlayWave(hWnd, "WINNER", SND_ASYNC | SND_MEMORY);
		MessageBox(hWnd, sz_winnermsg, "Winner", MB_ICONINFORMATION);
		return (1);
	} else if (p_Board->p2_captures >4) {
		LoadString(hInstance, IDS_PLAYER2WINNER, sz_winnermsg, 30);
		Winner = 2;
		PlayWave(hWnd,"WINNER", SND_ASYNC | SND_MEMORY);
		MessageBox(hWnd, sz_winnermsg, "Winner", MB_ICONINFORMATION);
		return (1);
	} else
		return (0);
}
