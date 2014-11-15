//////////////
// COMP.CPP //
//////////////
#include "winpente.h"

///////////////////////
// MoveNext Function //
///////////////////////
POINT MoveNext(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            if (i >=1 && p_Box[i-1][j]->piece == 0) {
                bPoint.x = i-1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((i>=1 &&  j>=1) && p_Box[i-1][j-1]->piece ==0) {
                bPoint.x = i-1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((j>=1) && p_Box[i][j-1]->piece ==0) {
                bPoint.x = i;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((i<=17 &&  j>=1) && p_Box[i+1][j-1]->piece ==0) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((i<=17) && p_Box[i+1][j]->piece ==0) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((i<=17 &&  j<=17) && p_Box[i+1][j+1]->piece ==0) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if (( j<=17) && p_Box[i][j+1]->piece ==0) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            if ((i>=1 &&  j<=17) && p_Box[i-1][j+1]->piece ==0) {
                bPoint.x = i-1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

//////////////////////////////
// CheckFourInARow Function //
//////////////////////////////

/* This function checks for four  pieces in a row
	it returns a POINT structure representing next move either
	a win, a block or no move */

POINT CheckFourInARow(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for four in a row from far left */
            if ((j <= 15 ) &&
                    (p_Box[i][j+1]->piece == player &&
                     p_Box[i][j+2]->piece == player &&
                     p_Box[i][j+3]->piece == player)) {
                if (j > 0 && p_Box[i][j-1]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j-1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (j<14  && p_Box[i][j+4]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j+4;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for four in a row from upper left diagonal */
            if ((i <= 15 && j <= 15) &&
                    (p_Box[i+1][j+1]->piece == player &&
                     p_Box[i+2][j+2]->piece == player &&
                     p_Box[i+3][j+3]->piece == player)) {
                if ((j >0 && i>0) && p_Box[i-1][j-1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j-1;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j <=14 && i <=14) && p_Box[i+4][j+4]->piece ==0) {
                    bPoint.x = i+4;
                    bPoint.y = j+4;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for four in a row  from upper right diagonal */
            if ((i <= 15 && j >= 4) &&
                    (p_Box[i+1][j-1]->piece == player &&
                     p_Box[i+2][j-2]->piece == player &&
                     p_Box[i+3][j-3]->piece == player)) {
                if ((j >=4 && i <=14) && p_Box[i+4][j-4]->piece == 0) {
                    bPoint.x = i+4;
                    bPoint.y = j-4;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j<=17 && i >=1) && p_Box[i-1][j+1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j+1;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for four in a row from top most */
            if ((i <= 15 ) &&
                    (p_Box[i+1][j]->piece == player &&
                     p_Box[i+2][j]->piece == player &&
                     p_Box[i+3][j]->piece == player)) {
                if (i <=14 && p_Box[i+4][j]->piece ==0) {
                    bPoint.x = i+4;
                    bPoint.y = j;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (i >=1  && p_Box[i-1][j]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j;

                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

///////////////////////////////
// CheckThreeInARow Function //
///////////////////////////////

POINT CheckThreeInARow(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for three in a row from far left */
            if ((j <= 16 ) &&
                    (p_Box[i][j+1]->piece == player &&
                     p_Box[i][j+2]->piece == player)) {
                if (j > 0 && p_Box[i][j-1]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j-1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (j<=15  && p_Box[i][j+3]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j+3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row from upper left diagonal */
            if ((i <= 16 && j <= 16) &&
                    (p_Box[i+1][j+1]->piece == player &&
                     p_Box[i+2][j+2]->piece == player)) {
                if ((j >0 && i>0) && p_Box[i-1][j-1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j-1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j <=15 && i <=15) && p_Box[i+3][j+3]->piece ==0) {
                    bPoint.x = i+3;
                    bPoint.y = j+3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row  from upper right diagonal */
            if ((i <= 16 && j >= 2) &&
                    (p_Box[i+1][j-1]->piece == player &&
                     p_Box[i+2][j-2]->piece == player)) {
                if ((j >=3 && i <=15) && p_Box[i+3][j-3]->piece == 0) {
                    bPoint.x = i+3;
                    bPoint.y = j-3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j<=17 && i >=1) && p_Box[i-1][j+1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j+1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row from top most */
            if ((i <= 16 ) &&
                    (p_Box[i+1][j]->piece == player &&
                     p_Box[i+2][j]->piece == player)) {
                if (i <=15 && p_Box[i+3][j]->piece ==0) {
                    bPoint.x = i+3;
                    bPoint.y = j;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (i >=1  && p_Box[i-1][j]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

/////////////////////////////
// CheckOpenThree Function //
/////////////////////////////

POINT CheckOpenThree(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for three in a row from far left */
            if ((j <= 15 && j>=1 ) &&
                    (p_Box[i][j+1]->piece == player &&
                     p_Box[i][j+2]->piece == player &&
                     p_Box[i][j-1]->piece == 0 &&
                     p_Box[i][j+3]->piece == 0)) {
                if (j > 0 && p_Box[i][j-1]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j-1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (j<=15  && p_Box[i][j+3]->piece == 0) {
                    bPoint.x = i;
                    bPoint.y = j+3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row from upper left diagonal */
            if ((i <= 15 && i >=1 && j <= 15 && j >=1) &&
                    (p_Box[i+1][j+1]->piece == player &&
                     p_Box[i+2][j+2]->piece == player&&
                     p_Box[i-1][j-1]->piece == 0 &&
                     p_Box[i+3][j+3]->piece == 0)) {
                if ((j >0 && i>0) && p_Box[i-1][j-1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j-1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j <=15 && i <=15) && p_Box[i+3][j+3]->piece ==0) {
                    bPoint.x = i+3;
                    bPoint.y = j+3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row  from upper right diagonal */
            if ((i <= 15 && i>=1 && j >= 3 && j <=17) &&
                    (p_Box[i+1][j-1]->piece == player &&
                     p_Box[i+2][j-2]->piece == player &&
                     p_Box[i-1][j+1]->piece == 0 &&
                     p_Box[i+3][j-3]->piece == 0)) {
                if ((j >=3 && i <=15) && p_Box[i+3][j-3]->piece == 0) {
                    bPoint.x = i+3;
                    bPoint.y = j-3;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if ((j<=17 && i >=1) && p_Box[i-1][j+1]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j+1;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }

            /* Check for three in a row from top most */
            if ((i <= 15 && i >=1) &&
                    (p_Box[i+1][j]->piece == player &&
                     p_Box[i+2][j]->piece == player &&
                     p_Box[i-1][j]->piece == 0 &&
                     p_Box[i+3][j]->piece ==0)) {
                if (i <=15 && p_Box[i+3][j]->piece ==0) {
                    bPoint.x = i+3;
                    bPoint.y = j;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
                if (i >=1  && p_Box[i-1][j]->piece == 0) {
                    bPoint.x = i-1;
                    bPoint.y = j;
                    if (AddToList(&head, &current, &prev, bPoint) == -1)
                        return(bPoint);
                }
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

////////////////////////////////
// CheckThreePlusOne Function //
////////////////////////////////

/* This function checks for three in a row
	 plus another piece displaced by one square */

POINT CheckThreePlusOne(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for three + one from far left */
            if ((j <= 14  && p_Box[i][j+3]->piece == 0) &&
                    (p_Box[i][j+1]->piece == player &&
                     p_Box[i][j+2]->piece == player &&
                     p_Box[i][j+4]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+3;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for three + one from upper left diagonal */
            if ((i <= 14 && j <= 14 && p_Box[i+3][j+3]->piece == 0) &&
                    (p_Box[i+1][j+1]->piece == player &&
                     p_Box[i+2][j+2]->piece == player &&
                     p_Box[i+4][j+4]->piece == player)) {
                bPoint.x = i+3;
                bPoint.y = j+3;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for three + one from upper right diagonal */
            if ((i <= 14 && j >= 4 && p_Box[i+3][j-3]->piece == 0) &&
                    (p_Box[i+1][j-1]->piece == player &&
                     p_Box[i+2][j-2]->piece == player &&
                     p_Box[i+4][j-4]->piece == player)) {
                bPoint.x = i+3;
                bPoint.y = j-3;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for three + one from top most */
            if ((i <= 14 && p_Box[i+3][j]->piece == 0) &&
                    (p_Box[i+1][j]->piece == player &&
                     p_Box[i+2][j]->piece == player &&
                     p_Box[i+4][j]->piece == player)) {
                bPoint.x = i+3;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

////////////////////////////////
// CheckOnePlusThree Function //
////////////////////////////////

/* This function checks for one piece displaced
	 plus three in a row*/

POINT CheckOnePlusThree(int player)
{
    int i, j, opponent;
    POINT bPoint = {19, 0};
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for one + three from far left */
            if ((j <= 14  && p_Box[i][j+1]->piece == 0) &&
                    (p_Box[i][j+2]->piece == player &&
                     p_Box[i][j+3]->piece == player &&
                     p_Box[i][j+4]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + three from upper left diagonal */
            if ((i <= 14 && j <= 14 && p_Box[i+1][j+1]->piece == 0) &&
                    (p_Box[i+2][j+2]->piece == player &&
                     p_Box[i+3][j+3]->piece == player &&
                     p_Box[i+4][j+4]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + three from upper right diagonal */
            if ((i <= 14 && j >= 4 && p_Box[i+1][j-1]->piece == 0) &&
                    (p_Box[i+2][j-2]->piece == player &&
                     p_Box[i+3][j-3]->piece == player &&
                     p_Box[i+4][j-4]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + three from top most */
            if ((i <= 14 && p_Box[i+1][j]->piece == 0) &&
                    (p_Box[i+2][j]->piece == player &&
                     p_Box[i+3][j]->piece == player &&
                     p_Box[i+4][j]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

//////////////////////////////
// CheckTwoPlusTwo Function //
//////////////////////////////

/* This function checks for two pieces displaced
	 plus two other pieces */

POINT CheckTwoPlusTwo(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for two + two from far left */
            if ((j <= 14  && p_Box[i][j+1]->piece == player) &&
                    (p_Box[i][j+2]->piece == 0 &&
                     p_Box[i][j+3]->piece == player &&
                     p_Box[i][j+4]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + two from upper left diagonal */
            if ((i <= 14 && j <= 14 && p_Box[i+1][j+1]->piece == player) &&
                    (p_Box[i+2][j+2]->piece == 0 &&
                     p_Box[i+3][j+3]->piece == player &&
                     p_Box[i+4][j+4]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + two from upper right diagonal */
            if ((i <= 14 && j >= 4 && p_Box[i+1][j-1]->piece == player) &&
                    (p_Box[i+2][j-2]->piece == 0 &&
                     p_Box[i+3][j-3]->piece == player &&
                     p_Box[i+4][j-4]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j-2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + two from top most */
            if ((i <= 14 && p_Box[i+1][j]->piece == player) &&
                    (p_Box[i+2][j]->piece == 0 &&
                     p_Box[i+3][j]->piece == player &&
                     p_Box[i+4][j]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

//////////////////////////////
// CheckOnePlusTwo Function //
//////////////////////////////

/* This function checks for two pieces displaced
	 plus one piece */

POINT CheckOnePlusTwo(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for one + two from far left */
            if ((j <= 15  && p_Box[i][j+1]->piece == 0) &&
                    (p_Box[i][j+2]->piece == player &&
                     p_Box[i][j+3]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from upper left diagonal */
            if ((i <= 15 && j <= 15 && p_Box[i+1][j+1]->piece == 0) &&
                    (p_Box[i+2][j+2]->piece == player &&
                     p_Box[i+3][j+3]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from upper right diagonal */
            if ((i <= 15 && j >= 3 && p_Box[i+1][j-1]->piece == 0) &&
                    (p_Box[i+2][j-2]->piece == player &&
                     p_Box[i+3][j-3]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from top most */
            if ((i <= 15 && p_Box[i+1][j]->piece ==0) &&
                    (p_Box[i+2][j]->piece == player &&
                     p_Box[i+3][j]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

//////////////////////////////////
// CheckOpenOnePlusTwo Function //
//////////////////////////////////

POINT CheckOpenOnePlusTwo(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for one + two from far left */
            if ((j <= 14 && j>=1  && p_Box[i][j+1]->piece == 0) &&
                    (p_Box[i][j+2]->piece == player &&
                     p_Box[i][j+3]->piece == player &&
                     p_Box[i][j-1]->piece == 0 &&
                     p_Box[i][j+4]->piece == 0)) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from upper left diagonal */
            if ((i <= 14 &&  i>=1 && j <= 14 && j>=1 && p_Box[i+1][j+1]->piece == 0) &&
                    (p_Box[i+2][j+2]->piece == player &&
                     p_Box[i+3][j+3]->piece == player &&
                     p_Box[i-1][j-1]->piece == 0 &&
                     p_Box[i+4][j+4]->piece == 0)) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from upper right diagonal */
            if ((i <= 14 && i>= 4 && j >= 4 && j<=17 && p_Box[i+1][j-1]->piece == 0) &&
                    (p_Box[i+2][j-2]->piece == player &&
                     p_Box[i+3][j-3]->piece == player &&
                     p_Box[i-1][j+1]->piece == 0 &&
                     p_Box[i+4][j-4]->piece == 0)) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + two from top most */
            if ((i <= 14 && i>=1 && p_Box[i+1][j]->piece ==0) &&
                    (p_Box[i+2][j]->piece == player &&
                     p_Box[i+3][j]->piece == player &&
                     p_Box[i-1][j]->piece == 0 &&
                     p_Box[i+4][j]->piece == 0)) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

/////////////////////////////////
// CheckOpenTwoPlusOneFunction //
/////////////////////////////////
POINT CheckOpenTwoPlusOne(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for two + one from far left */
            if ((j <= 14 && j>=1  && p_Box[i][j+1]->piece == player) &&
                    (p_Box[i][j+2]->piece == 0 &&
                     p_Box[i][j+3]->piece == player &&
                     p_Box[i][j-1]->piece == 0 &&
                     p_Box[i][j+4]->piece == 0)) {
                bPoint.x = i;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from upper left diagonal */
            if ((i <= 14 && i >=1  && j <= 14 && j>=1 && p_Box[i+1][j+1]->piece == player) &&
                    (p_Box[i+2][j+2]->piece == 0 &&
                     p_Box[i+3][j+3]->piece == player &&
                     p_Box[i-1][j-1]->piece == 0 &&
                     p_Box[i+4][j+4]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from upper right diagonal */
            if ((i <= 14 && i>=1 && j >= 4 && j<=17 && p_Box[i+1][j-1]->piece == player) &&
                    (p_Box[i+2][j-2]->piece == 0 &&
                     p_Box[i+3][j-3]->piece == player &&
                     p_Box[i-1][j+1]->piece == 0 &&
                     p_Box[i+4][j-4]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j-2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from top most */
            if ((i <= 14 && i >=1 && p_Box[i+1][j]->piece == player) &&
                    (p_Box[i+2][j]->piece == 0 &&
                     p_Box[i+3][j]->piece == player &&
                     p_Box[i-1][j]->piece == 0 &&
                     p_Box[i+4][j]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

/////////////////////////////
// CheckTwoPlusOneFunction //
/////////////////////////////

POINT CheckTwoPlusOne(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for two + one from far left */
            if ((j <= 15  && p_Box[i][j+1]->piece == player) &&
                    (p_Box[i][j+2]->piece == 0 &&
                     p_Box[i][j+3]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from upper left diagonal */
            if ((i <= 15 && j <= 15 && p_Box[i+1][j+1]->piece == player) &&
                    (p_Box[i+2][j+2]->piece == 0 &&
                     p_Box[i+3][j+3]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from upper right diagonal */
            if ((i <= 15 && j >= 3 && p_Box[i+1][j-1]->piece == player) &&
                    (p_Box[i+2][j-2]->piece == 0 &&
                     p_Box[i+3][j-3]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j-2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two + one from top most */
            if ((i <= 15 && p_Box[i+1][j]->piece == player) &&
                    (p_Box[i+2][j]->piece == 0 &&
                     p_Box[i+3][j]->piece == player)) {
                bPoint.x = i+2;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

/////////////////////////////
// CheckTwoInARow Function //
/////////////////////////////

POINT CheckTwoInARow(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for two in a row from far left */
            if ((j <= 16  && p_Box[i][j+1]->piece == player) &&
                    (p_Box[i][j+2]->piece == 0)) {
                bPoint.x = i;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two in a row from upper left diagonal */
            if ((i <= 16 && j <= 16 && p_Box[i+1][j+1]->piece == player) &&
                    (p_Box[i+2][j+2]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j+2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two in a row from upper right diagonal */
            if ((i <= 16 && j >= 2 && p_Box[i+1][j-1]->piece == player) &&
                    (p_Box[i+2][j-2]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j-2;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for two in a row from top most */
            if ((i <= 16 && p_Box[i+1][j]->piece == player) &&
                    (p_Box[i+2][j]->piece == 0)) {
                bPoint.x = i+2;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

///////////////////////////////
// CheckMoveCapture Function //
///////////////////////////////
POINT CheckMoveCapture(void)
{
    int i, j;
    POINT bPoint = {19, 0};

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == P2PIECE) {
            /* Check to capture from above */
            if ((i>=3) &&
                    p_Box[i-1][j]->piece == P1PIECE &&
                    p_Box[i-2][j]->piece == P1PIECE &&
                    p_Box[i-3][j]->piece == 0) {
                bPoint.x = i-3;
                bPoint.y = j;
                break;
            }
            /* Check to capture from upper left */
            else if  ((i>=3 && j>=3) &&
                      p_Box[i-1][j-1]->piece == P1PIECE &&
                      p_Box[i-2][j-2]->piece == P1PIECE &&
                      p_Box[i-3][j-3]->piece == 0) {
                bPoint.x = i-3;
                bPoint.y = j-3;
                break;
            }
            /* Check to capture from left */
            else if ((j>=3) &&
                     p_Box[i][j-1]->piece == P1PIECE &&
                     p_Box[i][j-2]->piece == P1PIECE &&
                     p_Box[i][j-3]->piece == 0) {
                bPoint.x = i;
                bPoint.y = j-3;
                break;
            }
            /* Check to capture from lower left */
            else if ((j>=3 && i <=15) &&
                     p_Box[i+1][j-1]->piece == P1PIECE &&
                     p_Box[i+2][j-2]->piece == P1PIECE &&
                     p_Box[i+3][j-3]->piece == 0) {
                bPoint.x = i+3;
                bPoint.y = j-3;
                break;
            }

            /* Check to capture from below */
            else if ((i <=15) &&
                     p_Box[i+1][j]->piece == P1PIECE &&
                     p_Box[i+2][j]->piece == P1PIECE &&
                     p_Box[i+3][j]->piece == 0) {
                bPoint.x = i+3;
                bPoint.y = j;
                break;
            }

            /* Check to capture from lower right */
            else if ((j<=15 && i <=15) &&
                     p_Box[i+1][j+1]->piece == P1PIECE &&
                     p_Box[i+2][j+2]->piece == P1PIECE &&
                     p_Box[i+3][j+3]->piece == 0) {
                bPoint.x = i+3;
                bPoint.y = j+3;
                break;
            }

            /* Check to capture from right */
            else if ((j<=15) &&
                     p_Box[i][j+1]->piece == P1PIECE &&
                     p_Box[i][j+2]->piece == P1PIECE &&
                     p_Box[i][j+3]->piece == 0) {
                bPoint.x = i;
                bPoint.y = j+3;
                break;
            }

            /* Check to capture from upper right */
            else if ((j<=15 && i >=3) &&
                     p_Box[i-1][j+1]->piece == P1PIECE &&
                     p_Box[i-2][j+2]->piece == P1PIECE &&
                     p_Box[i-3][j+3]->piece == 0) {
                bPoint.x = i-3;
                bPoint.y = j+3;
                break;
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(bPoint);
}

//////////////////////////////
// CheckOnePlusOne Function //
//////////////////////////////
POINT CheckOnePlusOne(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for one + one from above */
            if ((i>=2) &&
                    p_Box[i-1][j]->piece == 0 &&
                    p_Box[i-2][j]->piece == player) {
                bPoint.x = i-1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            /* Check for one + one from upper left*/
            if  ((i>=2 && j>=2) &&
                    p_Box[i-1][j-1]->piece == 0 &&
                    p_Box[i-2][j-2]->piece == player) {
                bPoint.x = i-1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            /* Check one + one from left */
            if ((j>=2) &&
                    p_Box[i][j-1]->piece == 0 &&
                    p_Box[i][j-2]->piece == player) {
                bPoint.x = i;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
            /* Check for one + one  from lower left */
            if ((j>=2 && i <=16) &&
                    p_Box[i+1][j-1]->piece == 0 &&
                    p_Box[i+2][j-2]->piece == player) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + one from below */
            if ((i <=16) &&
                    p_Box[i+1][j]->piece == 0 &&
                    p_Box[i+2][j]->piece == player) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + one from lower right */
            if ((j<=16 && i <=16) &&
                    p_Box[i+1][j+1]->piece == 0 &&
                    p_Box[i+2][j+2]->piece == player) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check one + one  from right */
            if ((j<=16) &&
                    p_Box[i][j+1]->piece == 0 &&
                    p_Box[i][j+2]->piece == player) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one + one from upper right */
            if ((j<=16 && i >=2) &&
                    p_Box[i-1][j+1]->piece == 0 &&
                    p_Box[i-2][j+2]->piece == player) {
                bPoint.x = i-1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}

///////////////////////////////////
// CheckOneDisplacedTwo Function //
///////////////////////////////////

/* This function checks for two single pieces
	displaced by two empty boxes */
POINT CheckOneDisplacedTwo(int player)
{
    int i, j, opponent;
    struct MOVES *head = NULL;
    struct MOVES *prev, *current;
    POINT bPoint = {19, 0};

    if (player == P1PIECE)
        opponent = P2PIECE;
    else
        opponent = P1PIECE;

    for (i=0, j=0; i<19; j++) {
        if (p_Box[i][j]->piece == player) {
            /* Check for one displaced two from far left */
            if ((j <= 15  && p_Box[i][j+1]->piece == 0) &&
                    (p_Box[i][j+2]->piece == 0 &&
                     p_Box[i][j+3]->piece == player)) {
                bPoint.x = i;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one displaced two from upper left diagonal */
            if ((i <= 15 && j <= 15 && p_Box[i+1][j+1]->piece == 0) &&
                    (p_Box[i+2][j+2]->piece == 0 &&
                     p_Box[i+3][j+3]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j+1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one displaced  two from upper right diagonal */
            if ((i <= 15 && j >=3 && p_Box[i+1][j-1]->piece == 0) &&
                    (p_Box[i+2][j-2]->piece == 0 &&
                     p_Box[i+3][j-3]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j-1;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }

            /* Check for one displaced two from top most */
            if ((i <= 15 && p_Box[i+1][j]->piece == 0) &&
                    (p_Box[i+2][j]->piece == 0 &&
                     p_Box[i+3][j]->piece == player)) {
                bPoint.x = i+1;
                bPoint.y = j;
                if (AddToList(&head, &current, &prev, bPoint) == -1)
                    return(bPoint);
            }
        }
        if (j == 18) {
            i++;
            j=-1;
        }
    }
    return(GetBestPoint(&head, &current, &prev, opponent));
}


/////////////////////////////////
// GetNearestOpponent Function //
/////////////////////////////////
int GetNearestOpponent(POINT mPoint, int opponent)
{
    int top = 19;
    int left = 19;
    int bottom = 19;
    int right = 19;
    int i, j;

    /* Check distance from top */
    for (i = mPoint.x, j = mPoint.y; i >=0; i--) {
        if (p_Box[i][j]->piece == opponent) {
            top = i;
            break;
        }
    }
    /* Check distance from left */
    for (i = mPoint.x, j = mPoint.y; j>=0; j--) {
        if (p_Box[i][j]->piece == opponent) {
            left = j;
            break;
        }
    }
    /* Check distance from bottom */
    for (i = mPoint.x, j = mPoint.y; i<=18; i++) {
        if (p_Box[i][j]->piece == opponent) {
            bottom = i;
            break;
        }
    }
    /* Check distance from right */
    for (i = mPoint.x, j = mPoint.y; j<=18; j++) {
        if (p_Box[i][j]->piece == opponent) {
            right = j;
            break;
        }
    }
    return (min(min(top, bottom), min(left, right)));
}

////////////////////////
// AddToList Function //
////////////////////////
int  AddToList (MOVES ** head, MOVES** current, MOVES** prev, POINT bPoint)
{
    char szErrorMsg[50];

    if (!(*current = (MOVES*)malloc(sizeof(MOVES)))) {
        LoadString (hInstance, IDS_MEMERROR, szErrorMsg,50);
        MessageBox(NULL, szErrorMsg, NULL, MB_ICONEXCLAMATION);
        return(-1);
    }

    if (*head == NULL)
        *head = *current;
    else
        (*prev)->next = *current;

    (*current)->next  = NULL;
    (*current)->mPoint = bPoint;
    *prev = *current;

    return(0);
}

///////////////////////////
// GetBestPoint Function //
///////////////////////////
POINT GetBestPoint(MOVES** head, MOVES** current, MOVES** prev, int opponent)
{
    POINT mPoint = {19, 0};
    MOVES* nearest = NULL;

    *current = *head;
    *prev = NULL;

    while (*current != NULL) {
        if (*prev != NULL) {
            if (GetNearestOpponent((*prev)->mPoint, opponent) <
                    GetNearestOpponent((*current)->mPoint, opponent))
                nearest = *prev;
            else
                nearest = *current;
        } else
            nearest = *current;

        *prev = *current;
        *current = (*current)->next;
    }

    if (nearest != NULL)
        mPoint = (nearest)->mPoint;

    *current = *head;

    /* free allocated memory */
    while (*current != NULL) {
        *prev = *current;
        *current = (*current)->next;
        free(*prev);
    }
    return (mPoint);
}

