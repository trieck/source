/*-------------------------------------------
	Module	: 	COMPMOV.C
	Purpose	:	Pente implementations
				for computer moves
	Author	: 	Thomas A. Rieck
	Date	:	09/09/1997
-------------------------------------------*/

#include "compmov.h"
#include "capture.h"
#include "resource.h"

/*--------------------------------
	ComputerMove Function
--------------------------------*/
BOOL DllExport ComputerMove(int aBoard[][19], LPPOINT pPoint, LPINT pCaptures, BOOL fEnableDebug)
{
    LPPIECELIST	pPieces	= NULL;
    BOOL		fRtn = FALSE;

    if (!pPoint || !pCaptures) {
        return fRtn;
    }

    // Initialize 'out' parameters
    pPoint->x	= -1;
    pPoint->y	= -1;
    *pCaptures	= 0;

    // Build a linked list of
    // computer pieces on the board.
    BuildPieces(aBoard, &pPieces);

    // Build paths for each piece
    // This also builds possible
    // trajectory for success'
    // for each path.
    BuildPaths(aBoard, pPieces);

#ifdef _DEBUG
    if (fEnableDebug) {
        ShowTrajectories(pPieces);
    }
#endif // _DEBUG

    // Move to capture
    *pCaptures = CheckMoveCapture(aBoard, pPieces, pPoint);
    if (*pCaptures) {
        fRtn = TRUE;
    }

    // Free list members
    EmptyPieces(&pPieces);

    return fRtn;
}

/*--------------------------------
	BuildPieces Function
--------------------------------*/

// This function builds a linked list
// of computer pieces on the board.
// aBoard[] is the address of the first
// entry into a 19 X 19 integer array holding
// values for marked spaces on the board.
// the list is later used in determing
// possible trajectories for success.

void BuildPieces(int aBoard[][19], PPPIECELIST ppHead)
{
    LPPIECELIST	pPrevious	= NULL;
    LPPIECELIST	pCurrent	= NULL;

    INT		i, j;
    POINT	bPoint;

    for (i = 0, j = 0; i < 19; j++) {
        if (aBoard[i][j] == PLAYER_TWO) {
            bPoint.x = i;
            bPoint.y = j;
            AddPiece(ppHead, &pPrevious, &pCurrent, &bPoint);
        }

        if (j == 18) {
            i++;
            j = -1;
        }
    }
}

/*-------------------------
	AddPiece Function
-------------------------*/

// This function adds a piece
// to the linked list of
// computer pieces on the board.

BOOL AddPiece(PPPIECELIST ppHead, PPPIECELIST ppPrev, PPPIECELIST ppCurrent, LPPOINT pPoint)
{
    if (*ppCurrent)
        *ppPrev = *ppCurrent;

    // Allocate memory for list member
    if (!(*ppCurrent = (LPPIECELIST)malloc(sizeof(PIECELIST))))
        return FALSE;

    (*ppCurrent)->pNextPiece = NULL;

    if (*ppHead == NULL)
        *ppHead = *ppCurrent;
    else
        (*ppPrev)->pNextPiece = *ppCurrent;

    (*ppCurrent)->bPoint = *pPoint;

    return TRUE;
}

/*-------------------------
	EmptyPieces Function
-------------------------*/

// This function removes the linked list
// of computer pieces on the board.
VOID EmptyPieces(PPPIECELIST ppHead)
{
    LPPIECELIST	pPrevious, pCurrent;

    pCurrent = *ppHead;

    // Free allocated memory for
    // each list member
    while (pCurrent) {
        pPrevious	= pCurrent;
        pCurrent	= pCurrent->pNextPiece;

        // Free allocated memory for paths
        // including linked lists for trajectories.
        EmptyPaths(pPrevious);

        FREELISTMEMBER(pPrevious);
    }

    // Destroy the head pointer
    *ppHead = NULL;
}

/*-------------------------
	EmptyPaths Function
-------------------------*/

// This function frees the memory allocated
// for each path
VOID EmptyPaths(LPPIECELIST pPiece)
{
    UINT i;

    for (i = 0; i < 4; i++) {
        if (pPiece->paths[i].pTrajectories != NULL) {
            EmptyTrajectories(&pPiece->paths[i].pTrajectories);
        }
    }
}

/*-------------------------------
	EmptyTrajectories Function
-------------------------------*/

// This function removes the linked list
// of trajectories for a given path.
VOID EmptyTrajectories(PPTRAJECTORYLIST ppHead)
{
    LPTRAJECTORYLIST pPrevious, pCurrent;

    pCurrent = *ppHead;

    // Free allocated memory for
    // each list member
    while (pCurrent) {
        pPrevious	= pCurrent;
        pCurrent	= pCurrent->pNextTrajectory;
        FREELISTMEMBER(pPrevious);
    }

    // Destroy the head pointer
    *ppHead = NULL;
}

/*-----------------------------
	BuildPaths() Function
-----------------------------*/
// This function builds the 4 paths
// for each computer piece found on the board

/*------------------------------------------------------------------

	paths[0]	:	Represents path from upper left diagonal.
	paths[1]	:	Represents vertical path from above.
	paths[2]	:	Represents path from lower left diagonal.
	paths[3]	:	Represents horizontal path from far left.

------------------------------------------------------------------*/

VOID BuildPaths(int aBoard[][19], LPPIECELIST pPieces)
{
    LPPIECELIST pCurrentPiece = pPieces;
    POINT		pt, ptExtent;
    PATH		paths[4];
    UINT		i;

    while (pCurrentPiece) {
        pt.x = pCurrentPiece->bPoint.x;
        pt.y = pCurrentPiece->bPoint.y;

        ZeroMemory(paths, sizeof(paths));

        paths[0].ptStart.x	= min(pt.x - 4, pt.y - 4) >= 0  ? - 4 : - min(pt.x, pt.y);
        paths[0].ptStart.y	= paths[0].ptStart.x;
        paths[0].ptEnd.x	= max(pt.x + 4, pt.y + 4) <= 18 ? + 4 : min(18 - pt.x, 18 - pt.y);
        paths[0].ptEnd.y	= paths[0].ptEnd.x;
        paths[1].ptStart.x	= 0;
        paths[1].ptStart.y	= pt.y - 4 >= 0 ? - 4 : - pt.y;
        paths[1].ptEnd.x	= 0;
        paths[1].ptEnd.y	= pt.y + 4 <= 18 ? + 4 : 18 - pt.y;
        paths[2].ptStart.x	= max(pt.x - 4 >= 0 ? - 4 : - pt.x, 18 - pt.y >= 4 ? - 4 : -(18 - pt.y));
        paths[2].ptStart.y	= paths[2].ptStart.x;
        paths[2].ptEnd.x	= min(pt.x + 4 <= 18 ? 4 : 18 - pt.x, pt.y - 4 >= 0 ? 4 : pt.y);
        paths[2].ptEnd.y	= paths[2].ptEnd.x;
        paths[3].ptStart.x	= pt.x - 4 >= 0 ? - 4 : - pt.x;
        paths[3].ptStart.y	= 0;
        paths[3].ptEnd.x	= pt.x + 4 <= 18 ? + 4 : 18 - pt.x;
        paths[3].ptEnd.y	= 0;

        memcpy(pCurrentPiece->paths, paths, sizeof(paths));

        // Loop through all paths and
        // build a list of trajectories for success
        for (i = 0; i < 4; i++) {
            FindPathExtent(&pCurrentPiece->paths[i], &ptExtent);

            if (ptExtent.x >=4 || ptExtent.y >=4) {
                // We have possible trajectories
                BuildTrajectories(aBoard, pCurrentPiece, i);
            }
        }
        pCurrentPiece = pCurrentPiece->pNextPiece;
    }
}

/*-----------------------------
	FindPathExtent() Function
-----------------------------*/
// This function finds the difference
// between the starting and ending points of a path
BOOL FindPathExtent(LPPATH pPath, LPPOINT ptExtent)
{
    if (!pPath || !ptExtent)
        return FALSE;

    ptExtent->x = abs(pPath->ptStart.x - pPath->ptEnd.x);
    ptExtent->y = abs(pPath->ptStart.y - pPath->ptEnd.y);

    return TRUE;
}

/*---------------------------------
	BuildTrajectories() Function
---------------------------------*/
// This function builds all trajectories
// for a given path
VOID BuildTrajectories(int aBoard[][19], LPPIECELIST pPiece, UINT nPath)
{
    LPTRAJECTORYLIST pCurrent 	= NULL;
    LPTRAJECTORYLIST pPrevious 	= NULL;
    POINT	ptStart, ptEnd;
    POINT	ptTStart, ptTEnd;
    POINT	pt;
    UINT	i, nPossibleT;
    BOOL	fIsTrajectory;

    // Ensure trajectories have not been built
    if (pPiece->paths[nPath].pTrajectories != NULL)
        return;

    switch (nPath) {
    case 0:		// Upper Left Diagonal
        // Convert relative points to absolute.
        ptStart.x	= pPiece->bPoint.x + pPiece->paths[0].ptStart.x;
        ptStart.y	= pPiece->bPoint.y + pPiece->paths[0].ptStart.y;
        ptEnd.x		= pPiece->bPoint.x + pPiece->paths[0].ptEnd.x;
        ptEnd.y		= pPiece->bPoint.y + pPiece->paths[0].ptEnd.y;

        // Number of possible trajectories
        // for this path
        nPossibleT = ((ptEnd.x - ptStart.x) - 4) + 1;

        // Ensure all pieces are computer pieces or free for all.
        for (i = 0; i < nPossibleT; i++) {
            ptTStart.x	= ptStart.x + i;
            ptTStart.y	= ptStart.y + i;
            ptTEnd.x	= ptTStart.x + 4;
            ptTEnd.y	= ptTStart.y + 4;

            fIsTrajectory = TRUE;

            for (pt.x = ptTStart.x, pt.y = ptTStart.y; pt.x <= ptTEnd.x && pt.y <= ptTEnd.y; pt.x++, pt.y++) {
                if (aBoard[pt.x][pt.y] != PLAYER_TWO &&
                        aBoard[pt.x][pt.y] != FREE_FOR_ALL) {
                    fIsTrajectory = FALSE;
                    break;		// Not a possible trajectory
                }
            }

            if (fIsTrajectory) {
                AddTrajectory(&pPiece->paths[0].pTrajectories, &pPrevious, &pCurrent, i);
            }
        }
        break;
    case 1:		// Upper Vertical
        // Convert relative points to absolute.
        ptStart.x	= pPiece->bPoint.x;
        ptStart.y	= pPiece->bPoint.y + pPiece->paths[1].ptStart.y;
        ptEnd.x		= pPiece->bPoint.x;
        ptEnd.y		= pPiece->bPoint.y + pPiece->paths[1].ptEnd.y;

        // Number of possible trajectories
        // for this path
        nPossibleT = ((ptEnd.y - ptStart.y) - 4) + 1;

        // Ensure all pieces are computer pieces or free for all.
        for (i = 0; i < nPossibleT; i++) {
            ptTStart.x	= ptStart.x;
            ptTStart.y	= ptStart.y + i;
            ptTEnd.x	= ptTStart.x;
            ptTEnd.y	= ptTStart.y + 4;

            fIsTrajectory = TRUE;

            for (pt.x = ptTStart.x, pt.y = ptTStart.y; pt.y <= ptTEnd.y; pt.y++) {
                if (aBoard[pt.x][pt.y] != PLAYER_TWO &&
                        aBoard[pt.x][pt.y] != FREE_FOR_ALL) {
                    fIsTrajectory = FALSE;
                    break;		// Not a possible trajectory
                }
            }

            if (fIsTrajectory) {
                AddTrajectory(&pPiece->paths[1].pTrajectories, &pPrevious, &pCurrent, i);
            }
        }
        break;
    case 2:		// Lower Left Diagonal
        // Convert relative points to absolute.
        ptStart.x	= pPiece->bPoint.x + pPiece->paths[2].ptStart.x;
        ptStart.y	= pPiece->bPoint.y - pPiece->paths[2].ptStart.y;
        ptEnd.x		= pPiece->bPoint.x + pPiece->paths[2].ptEnd.x;
        ptEnd.y		= pPiece->bPoint.y - pPiece->paths[2].ptEnd.y;

        // Number of possible trajectories
        // for this path
        nPossibleT = ((ptStart.y - ptEnd.y) - 4) + 1;

        // Ensure all pieces are computer pieces or free for all.
        for (i = 0; i < nPossibleT; i++) {
            ptTStart.x	= ptStart.x + i;
            ptTStart.y	= ptStart.y - i;
            ptTEnd.x	= ptTStart.x + 4;
            ptTEnd.y	= ptTStart.y - 4;

            fIsTrajectory = TRUE;

            for (pt.x = ptTStart.x, pt.y = ptTStart.y; pt.x <= ptTEnd.x && pt.y >= ptTEnd.y; pt.x++, pt.y--) {
                if (aBoard[pt.x][pt.y] != PLAYER_TWO &&
                        aBoard[pt.x][pt.y] != FREE_FOR_ALL) {
                    fIsTrajectory = FALSE;
                    break;		// Not a possible trajectory
                }
            }

            if (fIsTrajectory) {
                AddTrajectory(&pPiece->paths[2].pTrajectories, &pPrevious, &pCurrent, i);
            }
        }
        break;
    case 3:		// Left Horizontal
        // Convert relative points to absolute.
        ptStart.x	= pPiece->bPoint.x + pPiece->paths[3].ptStart.x;
        ptStart.y	= pPiece->bPoint.y;
        ptEnd.x		= pPiece->bPoint.x + pPiece->paths[3].ptEnd.x;
        ptEnd.y		= pPiece->bPoint.y;

        // Number of possible trajectories
        // for this path
        nPossibleT = ((ptEnd.x - ptStart.x) - 4) + 1;

        // Ensure all pieces are computer pieces or free for all.
        for (i = 0; i < nPossibleT; i++) {
            ptTStart.x	= ptStart.x + i;
            ptTStart.y	= ptStart.y;
            ptTEnd.x	= ptTStart.x + 4;
            ptTEnd.y	= ptTStart.y;

            fIsTrajectory = TRUE;

            for (pt.x = ptTStart.x, pt.y = ptTStart.y; pt.x <= ptTEnd.x; pt.x++) {
                if (aBoard[pt.x][pt.y] != PLAYER_TWO &&
                        aBoard[pt.x][pt.y] != FREE_FOR_ALL) {
                    fIsTrajectory = FALSE;
                    break;		// Not a possible trajectory
                }
            }

            if (fIsTrajectory) {
                AddTrajectory(&pPiece->paths[3].pTrajectories, &pPrevious, &pCurrent, i);
            }
        }
        break;
    }
}

/*---------------------------------
	AddTrajectory() Function
---------------------------------*/
// This function adds a trajectory
// to a given path for a given piece
BOOL AddTrajectory(PPTRAJECTORYLIST ppHead, PPTRAJECTORYLIST ppPrev, PPTRAJECTORYLIST ppCurrent, UINT nOffset)
{
    if (*ppCurrent)
        *ppPrev = *ppCurrent;

    // Allocate memory for list member
    if (!(*ppCurrent = (LPTRAJECTORYLIST)malloc(sizeof(TRAJECTORYLIST))))
        return FALSE;

    (*ppCurrent)->pNextTrajectory = NULL;

    if (*ppHead == NULL)
        *ppHead = *ppCurrent;
    else
        (*ppPrev)->pNextTrajectory = *ppCurrent;

    (*ppCurrent)->nOffset = nOffset;

    return TRUE;
}

/*------------------------------------------
	RelativePointsToAbsolute() Function
------------------------------------------*/
BOOL RelativePointsToAbsolute(LPPIECELIST pPieces, POINT ptExtents[2], UINT nPath, UINT nOffset)
{
    assert(pPieces);

    if (pPieces->bPoint.x > 18 || pPieces->bPoint.y > 18)
        return FALSE;

    if (nPath > 4 || nOffset > 4)
        return FALSE;

    // Set Trajectory Beginning Points
    ptExtents[0].x = pPieces->bPoint.x + pPieces->paths[nPath].ptStart.x;

    if (nPath != 2) {
        ptExtents[0].y = pPieces->bPoint.y + pPieces->paths[nPath].ptStart.y;
    } else {
        ptExtents[0].y = pPieces->bPoint.y - pPieces->paths[nPath].ptStart.y;
    }

    if (nPath == 0) {
        ptExtents[0].x += nOffset;
        ptExtents[0].y += nOffset;
    } else if (nPath == 1) {
        ptExtents[0].y += nOffset;
    } else if (nPath == 2) {
        ptExtents[0].x += nOffset;
        ptExtents[0].y -= nOffset;
    } else if (nPath == 3) {
        ptExtents[0].x += nOffset;
    }

    // Set Trajectory Ending Points
    if (nPath == 0) {
        ptExtents[1].x	= ptExtents[0].x + 4;
        ptExtents[1].y	= ptExtents[0].y + 4;
    } else if (nPath == 1) {
        ptExtents[1].x 	= ptExtents[0].x;
        ptExtents[1].y	= ptExtents[0].y + 4;
    } else if (nPath == 2) {
        ptExtents[1].x	= ptExtents[0].x + 4;
        ptExtents[1].y 	= ptExtents[0].y - 4;
    } else if (nPath == 3) {
        ptExtents[1].x	= ptExtents[0].x + 4;
        ptExtents[1].y	= ptExtents[0].y;
    }

    return TRUE;
}

/*----------------------------------
	CheckMoveCapture Function
----------------------------------*/
UINT CheckMoveCapture(INT aBoard[][19], LPPIECELIST pPieces, LPPOINT pPoint)
{
    INT		i, j;
    BOOL	nRtn = 0;

    if (!pPieces || !pPoint) {
        return nRtn;
    }

    // Intialize 'out' parameter
    pPoint->x = -1;
    pPoint->y = -1;

    while (pPieces != NULL) {
        i = pPieces->bPoint.x;
        j = pPieces->bPoint.y;

        /* Check to capture from above */
        if ((i >= 3) &&
                aBoard[i - 1][j] == PLAYER_ONE &&
                aBoard[i - 2][j] == PLAYER_ONE &&
                aBoard[i - 3][j] == FREE_FOR_ALL) {
            pPoint->x = i - 3;
            pPoint->y = j;
            break;
        }
        /* Check to capture from upper left */
        else if  ((i >= 3 && j >= 3) &&
                  aBoard[i - 1][j - 1] == PLAYER_ONE &&
                  aBoard[i - 2][j - 2] == PLAYER_ONE &&
                  aBoard[i - 3][j - 3] == FREE_FOR_ALL) {
            pPoint->x = i - 3;
            pPoint->y = j - 3;
            break;
        }
        /* Check to capture from left */
        else if ((j >= 3) &&
                 aBoard[i][j - 1] == PLAYER_ONE &&
                 aBoard[i][j - 2] == PLAYER_ONE &&
                 aBoard[i][j - 3] == FREE_FOR_ALL) {
            pPoint->x = i;
            pPoint->y = j - 3;
            break;
        }
        /* Check to capture from lower left */
        else if ((j >= 3 && i <= 15) &&
                 aBoard[i + 1][j - 1] == PLAYER_ONE &&
                 aBoard[i + 2][j - 2] == PLAYER_ONE &&
                 aBoard[i + 3][j - 3] == FREE_FOR_ALL) {
            pPoint->x = i + 3;
            pPoint->y = j - 3;
            break;
        }

        /* Check to capture from below */
        else if ((i <= 15) &&
                 aBoard[i + 1][j] == PLAYER_ONE &&
                 aBoard[i + 2][j] == PLAYER_ONE &&
                 aBoard[i + 3][j] == FREE_FOR_ALL) {
            pPoint->x = i + 3;
            pPoint->y = j;
            break;
        }

        /* Check to capture from lower right */
        else if ((j <= 15 && i <= 15) &&
                 aBoard[i + 1][j + 1] == PLAYER_ONE &&
                 aBoard[i + 2][j + 2] == PLAYER_ONE &&
                 aBoard[i + 3][j + 3] == FREE_FOR_ALL) {
            pPoint->x = i + 3;
            pPoint->y = j + 3;
            break;
        }

        /* Check to capture from right */
        else if ((j <= 15) &&
                 aBoard[i][j + 1] == PLAYER_ONE &&
                 aBoard[i][j + 2] == PLAYER_ONE &&
                 aBoard[i][j + 3] == FREE_FOR_ALL) {
            pPoint->x = i;
            pPoint->y = j + 3;
            break;
        }

        /* Check to capture from upper right */
        else if ((j <= 15 && i >= 3) &&
                 aBoard[i - 1][j + 1] == PLAYER_ONE &&
                 aBoard[i - 2][j + 2] == PLAYER_ONE &&
                 aBoard[i - 3][j + 3] == FREE_FOR_ALL) {
            pPoint->x = i - 3;
            pPoint->y = j + 3;
            break;
        }
        pPieces = pPieces->pNextPiece;
    }

    if (pPoint->x != -1 && pPoint->y != -1) {
        nRtn = CheckCapture(aBoard, pPoint, PLAYER_TWO);
        if (nRtn != 0) {
            aBoard[pPoint->x][pPoint->y] = PLAYER_TWO;
        }
    }

    return nRtn;
}

// Local Debug Functions

#ifdef _DEBUG

/*-------------------------------------
	ShowTrajectories() Function
-------------------------------------*/
VOID ShowTrajectories(LPPIECELIST pPieces)
{
    assert(g_hModule);

    DialogBoxParam(g_hModule,
                   MAKEINTRESOURCE(IDD_TRAJECTORIES),
                   GetActiveWindow(),
                   TrajectoryProc,
                   (LPARAM)pPieces);
}

BOOL CALLBACK TrajectoryProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static				HWND hWndListView;
    static				LPPIECELIST pPieces;
    LV_COLUMN			lvc;
    LV_ITEM				lvi;
    LPCTSTR				lpszHeaders[] = {_T("Piece"),
                                         _T("Path"),
                                         _T("Coordinates")
                               };
    LPTRAJECTORYLIST	pTrajectories;
    TCHAR				szBuffer[256];
    RECT				rc;
    UINT				nCount, nOffset, i, j;
    BOOL				fRtn;
    POINT				ptExtents[2];

    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            fRtn = TRUE;
            break;
        case IDCANCEL:
            fRtn = FALSE;
            break;
        }

        EndDialog(hDlg, fRtn);
        return FALSE;

        break;
    case WM_INITDIALOG:
        pPieces = (LPPIECELIST)lParam;

        // Initiate Common Controls
        InitCommonControls();

        hWndListView = GetDlgItem(hDlg, IDC_TRAJECTORYLIST);
        assert(hWndListView);

        ListView_SetTextColor(hWndListView, RGB(0, 0, 255));

        GetClientRect(hWndListView, &rc);

        nCount = sizeof(lpszHeaders) / sizeof(LPCTSTR);

        for (i = 0; i < nCount; i++) {
            lvc.mask		= LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
            lvc.iSubItem	= i;
            lvc.cx			= (rc.right - rc.left) / nCount;
            lvc.pszText		= (LPTSTR)lpszHeaders[i];
            lvc.cchTextMax	= lstrlen(lpszHeaders[i]);

            ListView_InsertColumn(hWndListView, i, &lvc);
        }

        for (i = 0; pPieces != NULL; pPieces = pPieces->pNextPiece) {
            for (j = 0; j < 4; j++) {
                pTrajectories = pPieces->paths[j].pTrajectories;

                while (pTrajectories) {
                    sprintf(szBuffer, _T("%d, %d"), pPieces->bPoint.x, pPieces->bPoint.y);

                    lvi.mask		= LVIF_TEXT;
                    lvi.iItem		= i;
                    lvi.iSubItem	= 0;
                    lvi.pszText		= szBuffer;
                    lvi.cchTextMax	= lstrlen(szBuffer);

                    ListView_InsertItem(hWndListView, &lvi);

                    // Set Path Text
                    sprintf(szBuffer, _T("%d"), j);
                    ListView_SetItemText(hWndListView, i, 1, szBuffer);

                    nOffset = pTrajectories->nOffset;

                    // Convert Relative Points to Absolute
                    if (RelativePointsToAbsolute(pPieces, ptExtents, j, nOffset)) {
                        // Set Coordinates Text
                        sprintf(szBuffer, _T("%d, %d : %d, %d"),
                                ptExtents[0].x, ptExtents[0].y, ptExtents[1].x, ptExtents[1].y);

                        ListView_SetItemText(hWndListView, i, 2, szBuffer);

                        pTrajectories = pTrajectories->pNextTrajectory;
                        i++;
                    }
                }
            }
        }

        break;
    default:
        break;
    }
    return FALSE;
}

#endif // _DEBUG