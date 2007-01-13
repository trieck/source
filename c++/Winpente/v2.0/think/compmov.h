/*-------------------------------------------
	Module	: 	COMPMOV.H
	Purpose	:	Pente declarations
				for computer moves
	Author	: 	Thomas A. Rieck
	Date	:	09/09/1997
--------------------------------------------*/

#ifndef _COMPMOV_H_
#define _COMPMOV_H_

#include "wpthk.h"
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <commctrl.h>

typedef struct tagPIECELIST			PIECELIST;
typedef struct tagPIECELIST*		LPPIECELIST;
typedef struct tagPIECELIST**		PPPIECELIST;

typedef struct tagTRAJECTORYLIST	TRAJECTORYLIST;
typedef struct tagTRAJECTORYLIST*	LPTRAJECTORYLIST;
typedef struct tagTRAJECTORYLIST**	PPTRAJECTORYLIST;

struct tagTRAJECTORYLIST					// Linked list structure for
{											// Trajectories for Success
	INT					nOffset;			// Offset from beginning of path 
	LPTRAJECTORYLIST	pNextTrajectory;
};

typedef struct	// Path structure for pieces
{
	POINT				ptStart;		// Starting point of the path (Relative to a piece)
	POINT				ptEnd;			// Ending point of the path (Relative to a piece)
	LPTRAJECTORYLIST	pTrajectories;
} PATH, *LPPATH, **PPPATH;

struct tagPIECELIST				// Linked list structure for
{								// building list of computer pieces
	POINT		bPoint;
	PATH		paths[4];		// The four paths for any given piece
	LPPIECELIST	pNextPiece;		// Pointer to the next piece in the list
};

// Macros
#define FREELISTMEMBER(p)				\
						if (p)			\
						{				\
							free(p);	\
							p = NULL;	\
						}				\
// Local functions
BOOL 	AddPiece(PPPIECELIST ppHead, PPPIECELIST ppPrev, PPPIECELIST ppCurrent, LPPOINT pPoint);
BOOL	AddTrajectory(PPTRAJECTORYLIST ppHead, PPTRAJECTORYLIST ppPrev, PPTRAJECTORYLIST ppCurrent, UINT nOffset);
VOID 	EmptyPieces(PPPIECELIST ppHead);
VOID	EmptyPaths(LPPIECELIST pPiece);
VOID	EmptyTrajectories(PPTRAJECTORYLIST ppHead);
VOID	BuildPieces(int aBoard[][19], PPPIECELIST ppHead);
VOID	BuildPaths(int aBoard[][19], LPPIECELIST pPieces);
VOID	BuildTrajectories(int aBoard[][19], LPPIECELIST pPiece, UINT nPath);
BOOL	FindPathExtent(LPPATH pPath, LPPOINT ptExtent);
BOOL	RelativePointsToAbsolute(LPPIECELIST pPieces, POINT ptExtents[2], UINT nPath, UINT nOffset);	
UINT	CheckMoveCapture(INT aBoard[][19], LPPIECELIST pPieces, LPPOINT pPoint);

// Local Debug Functions
#ifdef _DEBUG
VOID	ShowTrajectories(LPPIECELIST pPieces);
BOOL	CALLBACK TrajectoryProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // _DEBUG

// Exported functions
EXTERNC	BOOL DllExport ComputerMove(int aBoard[][19], LPPOINT pPoint, LPINT pCaptures, BOOL fEnableDebug);

#endif // _COMPMOV_H_