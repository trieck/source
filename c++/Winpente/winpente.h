/*------------------------------
		WINPENTE.H
-------------------------------*/

#ifndef _WINPENTE_H
#define _WINPENTE_H_

#include <time.h>
#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include "resource.h"

#define WHITE					0x00FFFFFF
#define BLACK					0x00000000
#define P1PIECE					1
#define P2PIECE					2
#define HOFFSET					15
#define VOFFSET					15
#define PLAYER_VS_PLAYER		0
#define PLAYER_VS_COMP			1
#define ID_STATUS				101

typedef struct {
    char szPlayerOne[16];
    char szPlayerTwo[16];
    char szWinner[16];
    char szTime[25];
} GAME, *LPGAME;

typedef struct {
    int piece;							/* Current Piece */
    RECT bRect;						    /* Rectangle coordinates */
} BOX, *LPBOX;

typedef struct {
    int p1_captures;					/* # of Green Captures */
    int p2_captures;					/* # of Red Captures */
    int current_turn;					/* Current Turn */
    int game_option;					/* Game Option */
    BOX box[19][19];					/* Array of Rectangles */
} BOARD, *LPBOARD;

typedef struct {
    int piece[19][19];					/* Which Piece */
    int info[4];						/* Current turn, captures, option*/
} GAMEFILE, *LPGAMEFILE;

struct MOVES {						/* linked list structure of possible MOVES */
    POINT mPoint;
    struct MOVES *next;
};

typedef struct MOVES ** PPMOVES;

extern HINSTANCE	hInstance;
extern RECT			cRect;							/* Grid Rectangle */
extern LPBOARD		p_Board;						/* Board Structure Pointer*/
extern BOX			(*p_Box)[19][19];				/* Box Structure Pointer */
extern int			BoxSize;						/* Box Size */
extern LPGAME		p_Games;						/* Games Structure Pointer */
extern const char	szTitle[];						/* Application Title */
extern char			szWorkingDirectory[_MAX_PATH];	/* Current Working Directory */
extern int			Winner;							/* Winner Number */

//////////////////////////////////////////////
// RegisterWindow Prototype //
/////////////////////////////////////////////
extern int RegisterWindow(HINSTANCE hInstance, LPCSTR szAppName);

////////////////////////////////////////////
// DisplayWindow Prototype //
////////////////////////////////////////////
extern HWND DisplayWindow(HINSTANCE hInstance,
                          LPCSTR szAppName,
                          LPCSTR szTitle,
                          int nCmdShow);

///////////////////////////////////
// DrawGrid Prototype //
///////////////////////////////////
extern void DrawGrid(HWND hWnd, HDC hDC);

///////////////////////////////////////////
// DrawStatusBar Prototype //
///////////////////////////////////////////
extern void DrawStatusBar(HWND hWnd);

/////////////////////////////////////
// DrawPiece Prototype //
/////////////////////////////////////
extern void DrawPiece (HWND hWnd, POINT c_point, LPSTR szResName);

////////////////////////////////////////
// WindowProc Prototype //
///////////////////////////////////////
extern long WINAPI WindowProc(HWND hWnd, UINT message,
                              WPARAM wParam, LPARAM lParam);

//////////////////////////////
// About Prototype //
//////////////////////////////
extern BOOL About(HWND hDlg, unsigned message, WPARAM wParam, LPARAM lParam);

//////////////////////////////
// Game Prototype //
//////////////////////////////
extern BOOL Game(HWND hDlg, unsigned message, WPARAM wParam, LPARAM lParam);

///////////////////////////////
// Colors Prototype //
//////////////////////////////
extern BOOL Colors(HWND hDlg, unsigned message, WPARAM wParam, LPARAM lParam);

/////////////////////////////////////
// WhichRect Prototype //
////////////////////////////////////
extern POINT WhichRect(POINT m_Point);

//////////////////////////////////////
// BuildBoard Prototype //
/////////////////////////////////////
extern void BuildBoard(HWND hWnd);

///////////////////////////////////////////
// RepaintPieces Prototype //
///////////////////////////////////////////
extern void RepaintPieces(HWND hWnd, HDC hDC);

/////////////////////////////////////////
// ErasePieces Prototype //
////////////////////////////////////////
extern void ErasePieces(HWND hWnd, POINT d_pieces[]);

//////////////////////////////////////////
// CheckCapture Prototype //
//////////////////////////////////////////
extern int CheckCapture(HWND hWnd, POINT c_point);

/////////////////////////////////////////////////
// CheckFiveInARow Prototype //
////////////////////////////////////////////////
extern int CheckFiveInARow(HWND hWnd, POINT c_point);

//////////////////////////////////////
// ClearBoard Prototype //
//////////////////////////////////////
extern void ClearBoard(HWND hWnd);

//////////////////////////////////////
// FileInitialize Prototype //
//////////////////////////////////////
extern void FileInitialize(HWND hWnd);

////////////////////////////////////////
// FileOpenDlg Prototype //
///////////////////////////////////////
extern BOOL FileOpenDlg (HWND hWnd, PSTR pstrFileName, PSTR pstrTitleName);

////////////////////////////////////////
// FileSaveDlg Prototype //
///////////////////////////////////////
extern BOOL FileSaveDlg (HWND hWnd, PSTR pstrFileName, PSTR pstrTitleName);

//////////////////////////////////
// FileWrite Prototype //
//////////////////////////////////
extern BOOL FileWrite(PSTR pstrFileName);

///////////////////////////////////
// FileRead Prototype //
//////////////////////////////////
extern BOOL FileRead(PSTR pstrFileName);

/////////////////////////////////////
// DoCaption Prototype //
/////////////////////////////////////
extern void DoCaption(HWND hWnd, LPSTR sz_titlename);

//////////////////////////////////////
// ShowStatus Prototype //
//////////////////////////////////////
extern void ShowStatus(HWND hWnd);

/////////////////////////////////////////
// CenterDialog Prototype //
////////////////////////////////////////
extern void CenterDialog(HWND hDlg);

////////////////////////////////
// Scores Prototype //
///////////////////////////////
extern BOOL Scores(HWND hDlg, unsigned message,
                   WPARAM wParam, LPARAM lParam);

////////////////////////////////
// Players Prototype //
////////////////////////////////
extern BOOL Players(HWND hDlg, unsigned message,
                    WPARAM wParam, LPARAM lParam);

////////////////////////////////////
// PlayWave Prototype //
////////////////////////////////////
extern void PlayWave(HWND hWnd, PSTR szWaveName, int iFlags);

////////////////////////////////////////////
// ComputerMove Prototype //
///////////////////////////////////////////
extern void ComputerMove(HWND hWnd);

/////////////////////////////////////
// NewGame Prototype //
/////////////////////////////////////
extern void NewGame(HWND hWnd);

////////////////////////////////////
// MoveNext Prototype //
////////////////////////////////////
extern POINT MoveNext(int player);

/////////////////////////////////////////////////
// CheckFourInARow Prototype //
/////////////////////////////////////////////////
extern POINT CheckFourInARow(int Player);

///////////////////////////////////////////////////
// CheckThreeInARow Prototype //
///////////////////////////////////////////////////
extern POINT CheckThreeInARow(int Player);

////////////////////////////////////////////////
// CheckOpenThree  Prototype //
////////////////////////////////////////////////
extern POINT CheckOpenThree(int Player);

////////////////////////////////////////////////////
// CheckThreePlusOne Prototype //
////////////////////////////////////////////////////
extern POINT CheckThreePlusOne(int Player);

////////////////////////////////////////////////////
// CheckOnePlusThree Prototype //
////////////////////////////////////////////////////
extern POINT CheckOnePlusThree(int Player);

//////////////////////////////////////////////////////////
// CheckOpenTwoPlusOne Prototype //
/////////////////////////////////////////////////////////
extern POINT CheckOpenTwoPlusOne(int player);

//////////////////////////////////////////////////
// CheckOnePlusTwo Prototype //
/////////////////////////////////////////////////
extern POINT CheckOnePlusTwo(int Player);

//////////////////////////////////////////////////////////
// CheckOpenOnePlusTwo Prototype //
//////////////////////////////////////////////////////////
extern POINT CheckOpenOnePlusTwo(int Player);

//////////////////////////////////////////////////
// CheckTwoPlusOne Prototype //
/////////////////////////////////////////////////
extern POINT CheckTwoPlusOne(int Player);

//////////////////////////////////////////////////
// CheckTwoPlusTwo Prototype //
//////////////////////////////////////////////////
extern POINT CheckTwoPlusTwo(int Player);

/////////////////////////////////////////////////
// CheckTwoInARow Prototype //
////////////////////////////////////////////////
extern POINT CheckTwoInARow(int Player);

///////////////////////////////////////////////////////////
// CheckOneDisplacedTwo Prototype //
//////////////////////////////////////////////////////////
extern POINT CheckOneDisplacedTwo(int Player);

///////////////////////////////////////////////////
// CheckMoveCapture Prototype //
//////////////////////////////////////////////////
extern POINT CheckMoveCapture(void);

/////////////////////////////////////////////////
// CheckOnePlusOne Prototype //
/////////////////////////////////////////////////
extern POINT CheckOnePlusOne(int player);

/////////////////////////////////////////////////////
// GetNearestOpponent Prototype //
////////////////////////////////////////////////////
extern int GetNearestOpponent(POINT mPoint, int opponent);

////////////////////////////////////
// AddToList Prototype //
////////////////////////////////////
extern int  AddToList (PPMOVES head, PPMOVES current, PPMOVES prev, POINT bPoint);

//////////////////////////////////////////
// GetBestPoint Prototype  //
/////////////////////////////////////////
extern POINT GetBestPoint(PPMOVES head, PPMOVES current, PPMOVES prev, int opponent);

//////////////////////////////////
// Pieces (DialogProc) Function //
//////////////////////////////////
extern BOOL Pieces(HWND hDlg, unsigned message,
                   WPARAM wParam, LPARAM lParam);

////////////////////////
// DrawFrame Function //
////////////////////////
void DrawFrame (HWND hDlg, UINT cPiece, COLORREF lColor);

#endif // _WINPENTE_H_
