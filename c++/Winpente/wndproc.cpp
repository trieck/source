/////////////////
// WNDPROC.CPP //
/////////////////

#include "winpente.h"

static COLORREF grid_color, back_color;  
static int		gMove =	0;					/* Computer Move */
static char		szP1Color[20];				/* Player One Color */
static char		szP2Color[20];				/* Player Two Color */
LPBOARD			p_Board;					/* Board Pointer */
BOX				(*p_Box)[19][19];			/* Box Array Pointer */
LPGAME			p_Games = NULL;				/* Games Pointer */
int				Winner;						/* Winner Number */

long WINAPI WindowProc(HWND hWnd, UINT message,
					   WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PaintSt;
	RECT 		aRect;
	HDC 		hDC;
	HPEN 		hPen, hPenOld;
	HBRUSH 		hBrush, hBrushOld;
	POINT 		m_Point, c_position;
	static char sz_filename[_MAX_PATH];
	static char sz_titlename[_MAX_FNAME + _MAX_EXT];
	static int	CurrentGame = 0, FirstMove = 0;
	char 		szBuffer[100];
				
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ABOUT:
			DialogBox(hInstance, "ABOUT_BOX",
				hWnd, (DLGPROC)About);
            return (0);
		case ID_COLORS:
			if (DialogBox(hInstance, "COLOR_BOX",hWnd, (DLGPROC)Colors))
				InvalidateRect(hWnd, 0, 0);
			return(0);
		case ID_GAMEOPTIONS:
			DialogBox(hInstance, "GAME_BOX", 
				hWnd, (DLGPROC)Game);
			return (0);
		case ID_PIECES:
			DialogBox(hInstance, "PLAYERPIECES",
				hWnd, (DLGPROC)Pieces);
			return (0);
		case ID_HELPCONTENTS:
			WinHelp(hWnd, "winpente.hlp",HELP_CONTENTS, 0);
			return(0);
		case ID_NEWGAME:
			sz_filename[0] = '\0';
			sz_titlename[0] = '\0';
			CurrentGame = -1;
			FirstMove = 0;
			ClearBoard(hWnd);
			return (0);
		case ID_OPENGAME:
			if (FileOpenDlg(hWnd, sz_filename, sz_titlename))
			{
				if (!FileRead(sz_filename))
				{
					EnableMenuItem(GetMenu(hWnd), ID_SAVEGAME, MF_GRAYED);
					LoadString(hInstance, IDS_OPENERROR, szBuffer, 100);
					MessageBox(hWnd, szBuffer, "Error", MB_ICONINFORMATION);
				}
				else
				{
					InvalidateRect(hWnd, &cRect, 0);
					DoCaption(hWnd, sz_titlename);
					ShowStatus(hWnd);
					CurrentGame = -1;
					EnableMenuItem(GetMenu(hWnd), ID_GAMEOPTIONS, MF_GRAYED);
					EnableMenuItem(GetMenu(hWnd), ID_SAVEGAME, MF_ENABLED);
				}
			}
			return(0);
		case ID_SAVEGAME:
			if (FileSaveDlg(hWnd, sz_filename, sz_titlename))
			{
				if (!FileWrite(sz_filename))
				{
					LoadString(hInstance, IDS_SAVEERROR, szBuffer, 100);
					MessageBox(hWnd, szBuffer, "Error", MB_OK);
				}
				else
					DoCaption(hWnd, sz_titlename);
			}
			return(0);
		case ID_SCORES:
			DialogBox(hInstance, "SCORES",hWnd, (DLGPROC)Scores);
			
			if (p_Games != NULL)
				free(p_Games);

			p_Games = NULL;
			return(0);
		case ID_FILE_EXIT:
			SendMessage(hWnd, WM_CLOSE,0,0);
	   		return (0);
		}
		case WM_CREATE:
			back_color = GetSysColor(COLOR_BACKGROUND);
			grid_color = WHITE;
			strcpy(szP1Color, "BLUEBALL");
			strcpy(szP2Color, "PURPLEBALL");
			DrawStatusBar(hWnd);
			FileInitialize(hWnd);
			BuildBoard(hWnd);
			CenterDialog(hWnd);
			PlayWave(hWnd, "THEME", 
				SND_ASYNC | SND_MEMORY| SND_LOOP);
			return (0);
		case WM_LBUTTONDOWN:
			if (!CurrentGame)
				return(0);

			m_Point.x = LOWORD(lParam);
			m_Point.y = HIWORD(lParam);
			if (PtInRect(&cRect,m_Point))
			{
				/* Disable Game Option */
				if (FirstMove == 0)
				{
					EnableMenuItem(GetMenu(hWnd), ID_GAMEOPTIONS, MF_GRAYED);
					FirstMove = -1;
				}
				
				c_position = WhichRect(m_Point);

				/* check for inside main rect but not within a valid small rect */
				if (c_position.x == -1 && c_position.y  == -1)
					return(0);

				/* check to make sure there is not a piece in the current box. */
				if (p_Box[c_position.x][c_position.y]->piece)
					return (0);
			
				/* Draw Current Piece */
				if (p_Board->current_turn == 0)
					DrawPiece(hWnd, c_position, szP1Color);
				else
					DrawPiece(hWnd, c_position, szP2Color);
			
				/* Check for a capture or five in a row */
				if (CheckCapture (hWnd, c_position) || CheckFiveInARow (hWnd, c_position))
					NewGame(hWnd);
				else if (p_Board->game_option == PLAYER_VS_COMP)
					ComputerMove(hWnd);
			}
			return(0);
		case WM_PAINT:
			GetClientRect(hWnd, &aRect);
			hDC = BeginPaint(hWnd, &PaintSt);
			hPen = CreatePen(PS_SOLID, 0, grid_color);
			hPenOld = (HPEN)SelectObject(hDC, hPen);
			hBrush = (HBRUSH)CreateSolidBrush(back_color);
			hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
			FillRect(hDC, &aRect, hBrush);
			DrawGrid(hWnd, hDC);
			RepaintPieces(hWnd, hDC);
			SelectObject(hDC, hPenOld);
			DeleteObject(hPen);
			SelectObject(hDC, hBrushOld);
			DeleteObject(hBrush);
			EndPaint(hWnd, &PaintSt);
			return (0);
		case WM_DESTROY:
			free(p_Board);
			PostQuitMessage(0);
			return(0);
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
}
///////////////////////
// DrawGrid Function //
///////////////////////
void DrawGrid (HWND hWnd, HDC hDC)
{
	int i, j;
		
	Rectangle(hDC, cRect.left,
					cRect.top,
					cRect.right,
					cRect.bottom);

	for (i=0, j = cRect.top; i< 18; i++)
	{
		MoveToEx(hDC, cRect.left, j+=BoxSize, 0);
		LineTo(hDC, cRect.right, j);
	}

	for(i=0, j = cRect.left; i< 18; i++)
	{
		MoveToEx(hDC, j+=BoxSize, cRect.top, 0);
		LineTo(hDC, j, cRect.bottom);
	}
}
//////////////////////////////////
// About (Dialog Proc) Function //
//////////////////////////////////
BOOL About(HWND hDlg, unsigned message,
		WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {   
		case WM_INITDIALOG:
			CenterDialog(hDlg);
			return(TRUE);
        case WM_COMMAND:
            switch (wParam)
            {
				case IDCANCEL:
                case IDOK:
                    EndDialog (hDlg, TRUE);
                    break;
                default:
                    break;
            }; 
    } 
    return (0);
}

/////////////////////////////////
// Game (Dialog Proc) Function //
/////////////////////////////////
BOOL Game(HWND hDlg, unsigned message,
		WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {   
		case WM_INITDIALOG:
			if (p_Board->game_option == PLAYER_VS_PLAYER)
				CheckRadioButton(hDlg, ID_PLAYERVSPLAYER, ID_PLAYERVSCOMP, ID_PLAYERVSPLAYER);
			else
				CheckRadioButton(hDlg, ID_PLAYERVSPLAYER, ID_PLAYERVSCOMP, ID_PLAYERVSCOMP);
			CenterDialog(hDlg);
			return(TRUE);
        case WM_COMMAND:
            switch (wParam)
            {
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					break;
                case IDOK:
					if (IsDlgButtonChecked(hDlg, ID_PLAYERVSPLAYER))
						p_Board->game_option = PLAYER_VS_PLAYER;
					else
						p_Board->game_option = PLAYER_VS_COMP;
                    EndDialog (hDlg, TRUE);
                    break;
                default:
                    break;
            }; 
    } 
    return (0);
}

///////////////////////////////////
// Colors (Dialog Proc) Function //
///////////////////////////////////
BOOL Colors(HWND hDlg, unsigned message,
		WPARAM wParam, LPARAM lParam)
{
	CHOOSECOLOR CColor;
	static DWORD CustColors[16];
	static COLORREF gColor, bColor;

	switch (message)
    {   
		case WM_INITDIALOG:
			gColor = grid_color;
			bColor = back_color;
								
			switch(grid_color)
			{
			case WHITE:
				CheckRadioButton(hDlg, IDC_GRIDWHITE, IDC_GRIDBLACK, IDC_GRIDWHITE);
				break;
			case BLACK:
				CheckRadioButton(hDlg, IDC_GRIDWHITE, IDC_GRIDBLACK, IDC_GRIDBLACK);
				break;
			};
		
			CenterDialog(hDlg);
			
			return(1);
        case WM_COMMAND:
            switch (wParam)
            {
				case IDC_GRIDWHITE:
					gColor = WHITE;
					break;
				case IDC_GRIDBLACK:
					gColor = BLACK;
					break;
				case ID_BACKCOLOR:
					CColor.lStructSize = sizeof(CHOOSECOLOR);
					CColor.hwndOwner = hDlg;
					CColor.hInstance = (HWND)hInstance;
					CColor.rgbResult = bColor;
					CColor.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
					CColor.lpCustColors = CustColors;
															
					if (ChooseColor(&CColor))
						bColor = CColor.rgbResult;
						
					break;
                case IDOK:
					grid_color = gColor;
					back_color = bColor;
					EndDialog(hDlg, TRUE);
					break;
                case IDCANCEL:
					EndDialog (hDlg, FALSE);
                    break;
                default:
                    break;
            }; 
    } 
    return (FALSE);
}
////////////////////////
// WhichRect Function //
////////////////////////

POINT WhichRect(POINT m_Point)
{
	int i, j;
	POINT c_position = {-1,-1};
	
	for (i=0, j=0; i<19; j++)
	{
		if (PtInRect(&(p_Box[i][j]->bRect), m_Point))
		{
			c_position.x = i;
			c_position.y = j;
			break;
		}
		if (j == 18)
		{
			i++;
			j=-1;
		}
	}
	return (c_position);
}
////////////////////////
// DrawPiece Function //
////////////////////////
void DrawPiece (HWND hWnd, POINT c_point, char* szResName)
{
	HICON hIcon;
	HDC hDC;
	int l_pos, t_pos;
	int iIconSize = BoxSize-3;
	char sz_turnmsg[30];
	
	hDC = GetDC(hWnd);
	
	l_pos = p_Box[c_point.x][c_point.y]->bRect.left+2;
	t_pos = p_Box[c_point.x][c_point.y]->bRect.top+2;

	if (p_Board->current_turn == 0)
	{
		p_Box[c_point.x][c_point.y]->piece = P1PIECE;
		
		LoadString (hInstance, 
						IDS_PLAYER2TURN,
						sz_turnmsg,30);
		p_Board->current_turn = 1;
	}
	else
	{
		p_Box[c_point.x][c_point.y]->piece = P2PIECE;
		LoadString (hInstance, 
						IDS_PLAYER1TURN,
						sz_turnmsg, 30);
		p_Board->current_turn = 0;
	}
	hIcon = (HICON)LoadImage(hInstance, szResName, 
								IMAGE_ICON,
								iIconSize, iIconSize,
								LR_LOADMAP3DCOLORS);

	DrawIconEx(hDC, l_pos, t_pos, hIcon, iIconSize, iIconSize, 0, 0, DI_NORMAL);
	
	ReleaseDC(hWnd, hDC);

	PlayWave(hWnd, "PIECE", SND_ASYNC | SND_MEMORY);
	
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 0, (LPARAM)sz_turnmsg);
}
////////////////////////////
// RepaintPieces Function //
////////////////////////////
void RepaintPieces(HWND hWnd, HDC hDC)
{
	int i, j, l_pos, t_pos;
	int iIconSize = BoxSize-3;
	HICON hIcon, hP1Icon, hP2Icon;

	hP1Icon = (HICON)LoadImage(hInstance,
									szP1Color, 
									IMAGE_ICON,
									iIconSize, iIconSize,
									LR_LOADMAP3DCOLORS);

	hP2Icon = (HICON)LoadImage(hInstance,
									szP2Color, 
									IMAGE_ICON,
									iIconSize, iIconSize,
									LR_LOADMAP3DCOLORS);

	for (i=0, j=0; i<19; j++)
	{
		if (p_Box[i][j]->piece)
		{
			l_pos = p_Box[i][j]->bRect.left+2;
			t_pos = p_Box[i][j]->bRect.top+2;
			switch (p_Box[i][j]->piece)
			{
			case P1PIECE:
				hIcon = hP1Icon;
				break;
			case P2PIECE:
				hIcon = hP2Icon;
				break;
			};
			DrawIconEx(hDC, l_pos, t_pos, hIcon, iIconSize, iIconSize, 0, 0, DI_NORMAL);
		}
		if (j == 18)
		{
			i++;
			j=-1;
		}
	}
}
//////////////////////////
// ErasePieces Function //
//////////////////////////
void ErasePieces(HWND hWnd, POINT d_pieces[])
{
	POINT i,j;
	
	i = d_pieces[0];
	j = d_pieces[1];

	p_Box[i.y][i.x]->piece = 0;
	p_Box[j.y][j.x]->piece = 0;

	PlayWave(hWnd, "CAPTURE", SND_ASYNC | SND_MEMORY);

	InvalidateRect(hWnd, &p_Box[i.y][i.x]->bRect, 0);
	InvalidateRect(hWnd, &p_Box[j.y][j.x]->bRect, 0);
	UpdateWindow(hWnd);
}
/////////////////////////
// ClearBoard Function //
/////////////////////////
void ClearBoard(HWND hWnd)
{
	int i,j;
	char sz_turnmsg[30];

	/* Initialize variables */
	p_Board->current_turn = 0;
	p_Board->p1_captures = 0;
	p_Board->p2_captures = 0;
	Winner = 0;
	gMove = 0;
	
	LoadString (hInstance, IDS_PLAYER1TURN,
						sz_turnmsg, 30);

	for (i=0, j=0; i<19; j++)
	{
		p_Box[i][j]->piece = 0;

		if (j == 18)
		{
			i++;
			j=-1;
		}
	}
	InvalidateRect(hWnd, &cRect, 0);

	/* Clear StatusBar */
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 0, (LPARAM)sz_turnmsg);
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 1, NULL);
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 2, NULL);

	/* Clear Title Bar */
	SetWindowText(hWnd, szTitle);

	/* Enable Option Menu and Save Game */
	EnableMenuItem(GetMenu(hWnd), ID_GAMEOPTIONS, MF_ENABLED);
	EnableMenuItem(GetMenu(hWnd), ID_SAVEGAME, MF_ENABLED);
}

////////////////////////
// DoCaption Function //
////////////////////////
void DoCaption(HWND hWnd, char* sz_titlename)
{
	const int MAXCOUNT = 64 + _MAX_FNAME + _MAX_EXT; 
	char sz_caption[MAXCOUNT];
		
	sprintf(sz_caption, "%s - %s", szTitle, sz_titlename);

	SetWindowText(hWnd, sz_caption);
}

/////////////////////////
// ShowStatus Function //
/////////////////////////
void ShowStatus(HWND hWnd)
{
	char sz_turnmsg[30];
	char sz_p1captures[30];
	char sz_p2captures[30];
	char sz_buffer[25];

	if (p_Board->current_turn == 0)
		LoadString (hInstance, 
			IDS_PLAYER1TURN,
			sz_turnmsg, 30);
	else
		LoadString (hInstance, 
			IDS_PLAYER2TURN,
			sz_turnmsg, 30);
	
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 0, (LPARAM)sz_turnmsg);

	LoadString(hInstance, IDS_P1CAPTURES, sz_buffer, 25);
	sprintf(sz_p1captures, "%s%d", sz_buffer, p_Board->p1_captures);
	
	LoadString(hInstance, IDS_P2CAPTURES, sz_buffer, 25);
	sprintf(sz_p2captures, "%s%d", sz_buffer, p_Board->p2_captures);
	
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 1, (LPARAM)sz_p1captures);
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETTEXT, 2, (LPARAM)sz_p2captures);
}

///////////////////////////
// CenterDialog Function //
///////////////////////////
void CenterDialog(HWND hDlg)
{
	RECT rcDlg, rc, rcOwner;
	HWND hwndOwner;

	// Get the owner window and dialog box rectangles. 
	if ((hwndOwner = GetParent(hDlg)) == NULL) 
		hwndOwner = GetDesktopWindow(); 
        GetWindowRect(hwndOwner, &rcOwner); 
        GetWindowRect(hDlg, &rcDlg); 
        CopyRect(&rc, &rcOwner); 
 
	// Offset the owner and dialog box rectangles so that 
    // right and bottom values represent the width and 
    // height, and then offset the owner again to discard 
    // space taken up by the dialog box. 
 
    OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); 
    OffsetRect(&rc, -rc.left, -rc.top); 
    OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom); 
 
    // The new position is the sum of half the remaining 
    // space and the owner's original position. 
 
    SetWindowPos(hDlg, 
		HWND_TOP, 
        rcOwner.left + (rc.right / 2), 
        rcOwner.top + (rc.bottom / 2), 
        0, 0,          // ignores size arguments 
        SWP_NOSIZE); 
}

///////////////////////////////////
// Scores (Dialog Proc) Function //
///////////////////////////////////
BOOL Scores(HWND hDlg, unsigned message,
		WPARAM wParam, LPARAM lParam)
{
	FILE* fp;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, hBrushOld;
	HRGN hRgn;
	HFONT hOldFont;
	static RECT fRect, cRect;
	static HFONT hFont;
	static HWND hFrame;
	static int cxChar, cxCaps, cyChar;
	static int numgames,  vScrollPos, maxpos;
	char szScoresFile[_MAX_PATH + _MAX_FNAME + _MAX_EXT];
	long fs;
	int i, y;
	char szBuffer[100];
	
	switch (message)
	{
		case WM_INITDIALOG:
			hFrame = GetDlgItem(hDlg, ID_FRAME);
			hDC = GetDC (hFrame);
			
			/* Find Client area relative to Dialog Box
			/* Offset cRect relative to Dialog Box */
			GetClientRect(hFrame, &fRect);
			cRect = fRect;
			MapWindowPoints(hFrame, hDlg, (LPPOINT)&cRect, 2);
			
			/* Create Font*/
			hFont =  CreateFont(
				-MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72),
				0,
				0,
				0,
				400,
				FALSE,
				FALSE,
				FALSE,
				DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH,
				"MS Sans Serif");

			hOldFont = (HFONT)SelectObject (hDC, hFont);

			/* Get Text Metric information based on new font */
			GetTextMetrics(hDC, &tm);
			cxChar = tm.tmAveCharWidth;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 :2) * cxChar /2;
			cyChar = tm.tmHeight + tm.tmExternalLeading;

			SelectObject(hDC, hOldFont);
						
			ReleaseDC (hFrame, hDC);
			
			/* Read data to file */
			sprintf(szScoresFile, "%s%s", szWorkingDirectory, "\\scores.dat");
			if (NULL==(fp=fopen(szScoresFile, "rb")))
			{
				p_Games = NULL;
				return(FALSE);
			}
					
			/* Move to end of file to find number of games */
			fseek(fp, 0L, SEEK_END);
			fs = ftell(fp);
			if (fs==0)
			{
				p_Games = NULL;
				return (FALSE);
			}
			if (NULL == (p_Games = (GAME*)malloc(fs)))
			{
				LoadString(hInstance, IDS_MEMERROR, szBuffer, 100);
				MessageBox(hDlg, szBuffer, "Error", MB_ICONEXCLAMATION);
				fclose(fp);
				DestroyWindow(hDlg);
				return (FALSE);
			}
												
			/* Move to beginning of file and read data */
		    rewind(fp);
			if (fread(p_Games, fs, 1, fp)==0)
			{
				LoadString(hInstance, IDS_OPENERROR, szBuffer, 100);
				MessageBox(hDlg, szBuffer, "Error", MB_ICONEXCLAMATION);
				fclose(fp);
				DestroyWindow(hDlg);
				return (FALSE);
			}
			fclose(fp);

			/* Find Total number of games */
			numgames = fs / sizeof(GAME);

			/* Find maximum position of scroll bar control */
			maxpos = (numgames - (fRect.bottom - fRect.top)/cyChar);

			/* Set scroll range */
			 SetScrollRange(GetDlgItem(hDlg, ID_SCROLL),  SB_CTL, 0, maxpos, FALSE);

			CenterDialog(hDlg);
			return (TRUE);
		case WM_COMMAND:
            switch (wParam)
            {
				case IDCANCEL:
				case IDOK:
					DeleteObject(hFont);
					vScrollPos = 0;
					EndDialog (hDlg, TRUE);
                    break;
				default:
                    break;
            };
			return(0);
		case WM_VSCROLL:
			switch(LOWORD(wParam))
			{
				case SB_LINEDOWN:
					vScrollPos+=1;
					break;
				case SB_LINEUP:
					vScrollPos-=1;
					break;
				default:
					break;
			};
						
			/* Set the scroll bar control position */
			vScrollPos = max(0, min(vScrollPos, maxpos));

			if (vScrollPos != GetScrollPos(GetDlgItem(hDlg, ID_SCROLL), SB_CTL))
			{
				SetScrollPos(GetDlgItem(hDlg, ID_SCROLL), SB_CTL, vScrollPos, FALSE);
				InvalidateRect(hDlg,&cRect, FALSE);
			}
			
			return(0);
		case WM_PAINT:
			hDC = BeginPaint(hFrame, &ps);

			/* Set Background Mode, Text Color, and Font */
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(0, 255, 0));
			hOldFont = (HFONT)SelectObject (hDC, hFont);

			/* Set Clipping Region */
			hRgn = CreateRectRgn(fRect.left, fRect.top, fRect.right, fRect.bottom);
			SelectClipRgn(hDC, hRgn);

			/* Fill Window Black */
			hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
			FillRect(hDC, &fRect, hBrush);
			SelectObject(hDC, hBrushOld);
			DeleteObject(hBrush);
					
			/* Draw the Scores */
			if (p_Games != NULL)
			{
				for (i =0; i<numgames; i++)
				{
					y = cyChar *( i-vScrollPos);

					TextOut(hDC, 0, y,
					(p_Games+i)->szPlayerOne, strlen((p_Games+i)->szPlayerOne));

					TextOut(hDC, cxCaps * 13, y, 
					(p_Games+i)->szPlayerTwo, strlen((p_Games+i)->szPlayerTwo));

					TextOut(hDC, cxCaps * 26, y, 
					(p_Games+i)->szWinner, strlen((p_Games+i)->szWinner));

					TextOut(hDC, cxCaps * 39, y,
					(p_Games+i)->szTime, strlen((p_Games+i)->szTime));
				}
			}
			SelectObject(hDC, hOldFont);
			DeleteObject(hRgn); 
			EndPaint (hFrame, &ps);
			break;
		default:
			break;
	}
	return (FALSE);
}

////////////////////////////////////
// Players (Dialog Proc) Function //
////////////////////////////////////
BOOL Players(HWND hDlg, unsigned message,
		WPARAM wParam, LPARAM lParam)
{
	FILE *fg, *fp;
	GAME players;
    tm *newtime;
 	time_t a_clock;
	static char szPlayersFile[_MAX_PATH + _MAX_FNAME + _MAX_EXT];
	char szScoresFile[_MAX_PATH + _MAX_FNAME + _MAX_EXT];
	char szComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	char szPlayerName[16];
	char szBuffer[100];
	DWORD lCompLength = MAX_COMPUTERNAME_LENGTH + 1;
	
    int i;
	
	switch (message)
	{
		case WM_INITDIALOG:
			/* Read list of players */
			sprintf(szPlayersFile, "%s%s", szWorkingDirectory, "\\players.dat");
			if (NULL==(fp=fopen(szPlayersFile, "a+b")))
			{
				LoadString(hInstance, IDS_OPENERROR, szBuffer, 100);
				MessageBox(hDlg, szBuffer, "WinPente", MB_ICONEXCLAMATION);
				DestroyWindow(hDlg);
				return (FALSE);
			}
			while (fgets(szPlayerName, 16, fp) != NULL)
			{
				for (i = 0; i<16; i++)
				{
					if (szPlayerName[i] == '\n' ||  szPlayerName[i] == '\r')
						szPlayerName[i] = '\0';
				}
				if (szPlayerName[0] != '\0')
				{
					SendDlgItemMessage(hDlg, ID_PLAYERONE, CB_ADDSTRING, 0, (LPARAM)szPlayerName);
					SendDlgItemMessage(hDlg, ID_PLAYERTWO, CB_ADDSTRING, 0, (LPARAM)szPlayerName);
				}
			}
			fclose(fp);
		

			/* Limit text  entry length */
			SendDlgItemMessage(hDlg, ID_PLAYERONE, CB_LIMITTEXT, (WPARAM)15, 0);
			SendDlgItemMessage(hDlg, ID_PLAYERTWO, CB_LIMITTEXT, (WPARAM)15, 0);
			
			/* Put Computer Name in Player 2 Box 
				if playing against computer */
			if (p_Board->game_option == PLAYER_VS_COMP)
			{
				GetComputerName(szComputerName, &lCompLength);
				if (strlen(szComputerName) != 0)
				{
					SendDlgItemMessage(hDlg, ID_PLAYERTWO, WM_SETTEXT, 0, (LPARAM)szComputerName);
					EnableWindow(GetDlgItem(hDlg, ID_PLAYERTWO), FALSE);
				}
			}
			SetFocus(GetDlgItem(hDlg, ID_PLAYERONE));

			CenterDialog(hDlg);
			return (FALSE);
		case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:
					GetDlgItemText(hDlg, ID_PLAYERONE, players.szPlayerOne, 16);
					GetDlgItemText(hDlg, ID_PLAYERTWO, players.szPlayerTwo, 16);
					
					if ((!(strlen(players.szPlayerOne))) || (!(strlen(players.szPlayerTwo))))
						return (FALSE); 

					/* Check whether players names exist in database;
					     if they do not then we will add them to the file */
					if (NULL==(fp=fopen(szPlayersFile, "a+b")))
					{
						LoadString(hInstance, IDS_OPENERROR, szBuffer, 100);
						MessageBox(hDlg, szBuffer, "WinPente", MB_ICONEXCLAMATION);
						DestroyWindow(hDlg);
						return (FALSE);
					}
										
					if (SendDlgItemMessage(hDlg, ID_PLAYERONE, CB_FINDSTRINGEXACT, 0, (LPARAM)players.szPlayerOne) == CB_ERR)
					{
						fputs(players.szPlayerOne, fp);
						fputs("\r\n", fp);
					}
					if (SendDlgItemMessage(hDlg, ID_PLAYERONE, CB_FINDSTRINGEXACT, 0, (LPARAM)players.szPlayerTwo) == CB_ERR)
					{
						fputs(players.szPlayerTwo, fp);
						fputs("\r\n", fp);
					}
					fclose(fp);

					/* Set Winner */
					if (Winner == 1)
						strcpy(players.szWinner, players.szPlayerOne);
					else
						strcpy(players.szWinner, players.szPlayerTwo);
						
					/* Get current time */
					time(&a_clock);
					newtime = localtime(&a_clock);
					strcpy(players.szTime, asctime(newtime));
					/* Replace newline character with null */
					players.szTime[strlen(players.szTime)-1]= '\0';
				
					/* Write data to file */
					sprintf(szScoresFile, "%s%s", szWorkingDirectory, "\\scores.dat");
					if (NULL==(fg=fopen(szScoresFile, "a+b")))
					{
						LoadString(hInstance, IDS_OPENERROR, szBuffer, 100);
						MessageBox(hDlg, szBuffer, "WinPente", MB_ICONEXCLAMATION);
						EndDialog (hDlg, FALSE);
						break;
					}
					if (fwrite(&players, sizeof(GAME), 1, fg)==0)
					{
						LoadString(hInstance, IDS_SAVEERROR, szBuffer, 100);
						MessageBox(hDlg, szBuffer, "WinPente", MB_ICONEXCLAMATION);
					}
						
					fclose(fg);
					EndDialog (hDlg, TRUE);
                    break;
                default:
                    break;
            };
		default:
			break;
	}
	return (FALSE);
}

//////////////////////////////////
// Pieces (DialogProc) Function //
//////////////////////////////////
extern BOOL Pieces(HWND hDlg, unsigned message, 
				   WPARAM wParam, LPARAM lParam)
{
	LPCSTR szColors[5]			= {"BLUEBALL", "GREENBALL", "LTBLUEBALL",
									"PURPLEBALL", "REDBALL"};
	UINT PONEPIECE[5]			= {IDC_PLAYERONEPIECE, IDC_PLAYERONEPIECE2,
									IDC_PLAYERONEPIECE3, IDC_PLAYERONEPIECE4,
									IDC_PLAYERONEPIECE5};
	UINT PTWOPIECE[5]			= {IDC_PLAYERTWOPIECE, IDC_PLAYERTWOPIECE2,
									IDC_PLAYERTWOPIECE3, IDC_PLAYERTWOPIECE4,
									IDC_PLAYERTWOPIECE5};

	UINT i = 0;
	HDC hDC;
	PAINTSTRUCT ps;
	static UINT cPiece1 = 0;
	static UINT cPiece2 = 0;
	char szMsg[100];
	const COLORREF fColor = RGB(255,255,0);

	switch (message)
	{
		case WM_INITDIALOG:
			// set colors
			for (i=0; i <5; i++)
			{
				if (strcmp (szP1Color, szColors[i]) == 0)
					cPiece1 = PONEPIECE[i];

				if (strcmp(szP2Color, szColors[i]) == 0)
					cPiece2 = PTWOPIECE[i];
			}

			CenterDialog(hDlg);
			return (TRUE);
			break;
		case WM_COMMAND:
			switch (wParam)
			{
				case IDOK:
					if (cPiece1 != 0 && cPiece2 != 0)
					{
						for (i = 0; i < 5; i++)
						{
							if (cPiece1 == PONEPIECE[i])
								strcpy(szP1Color, szColors[i]);

							if (cPiece2 == PTWOPIECE[i])
								strcpy(szP2Color, szColors[i]);
						}
					}
					if (strcmp(szP1Color, szP2Color) == 0)
					{
						LoadString(hInstance, IDS_PIECEEQUAL, szMsg, 100);
						MessageBox(hDlg, szMsg, "Error", MB_ICONINFORMATION);
						break;
					}
					InvalidateRect(GetParent(hDlg), 0, TRUE);
					EndDialog(hDlg, TRUE);
					break;
				case IDCANCEL:
					cPiece1 = 0;
					cPiece2 = 0;
					EndDialog(hDlg, FALSE);
					break;
				default:
					for (i = 0; i < 5; i ++)
					{
						if (PONEPIECE[i] == LOWORD(wParam))
							cPiece1 = LOWORD(wParam);

						if (PTWOPIECE[i] == LOWORD(wParam))
							cPiece2 = LOWORD(wParam);
					}
					break;
			}
		case WM_PAINT:
			hDC = BeginPaint(hDlg, &ps);
			
			for (i = 0; i < 5; i++)
			{
				if (cPiece1 == PONEPIECE[i])
					DrawFrame(hDlg, cPiece1, fColor);
				else
					DrawFrame(hDlg, PONEPIECE[i], GetSysColor(COLOR_BTNFACE));

				if (cPiece2 == PTWOPIECE[i])
					DrawFrame(hDlg, cPiece2, fColor);
				else
					DrawFrame(hDlg, PTWOPIECE[i], GetSysColor(COLOR_BTNFACE));
			}
			EndPaint(hDlg, &ps);
			break;
	}
	return (FALSE);
}

////////////////////////
// DrawFrame Function //
////////////////////////
void DrawFrame (HWND hDlg, UINT cPiece, COLORREF lColor)
{
	HWND hWndPct;
	HDC hDC;
	RECT rc;
	HBRUSH hBrush, hBrushOld;

	hWndPct = GetDlgItem(hDlg, cPiece);

	hDC = GetDC(hWndPct);
	
	GetClientRect(hWndPct, &rc);
	
	hBrush = (HBRUSH)CreateSolidBrush(lColor);
	hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
	
	FrameRect(hDC, &rc, hBrush);
	SelectObject(hDC, hBrushOld);
	
	// clean up
	DeleteObject(hBrush);
	ReleaseDC(hWndPct, hDC);
}

///////////////////////
// PlayWave function //
///////////////////////
void PlayWave(HWND hWnd, PSTR szWaveName, int iFlags)
{
	HRSRC hWaveRes;
	HGLOBAL hGlobMem;

	hWaveRes = FindResource(hInstance, szWaveName, "WAVE");
 
    hGlobMem = LoadResource(hInstance, hWaveRes);
      
	PlaySound((LPSTR)LockResource(hGlobMem), hInstance, iFlags);
 
    FreeResource(hGlobMem);  
}

///////////////////////////
// ComputerMove Function //
///////////////////////////
void ComputerMove(HWND hWnd)
{
	POINT bPoint = {19,0};
	POINT fPoint[3][3] = {
		{{8,8}, {8,9}, {8,10}},
		{{9,8}, {9,9}, {9,10}},
		{{10,8}, {10,9}, {10,10}}
	};
	int i,j;
			
	/* make sure first move is around center */
	if (gMove == 0)
	{
		srand( (unsigned)time( NULL ) );
		do 
		{
			bPoint.x = (rand() % 3) + 8;
			bPoint.y = (rand() % 3) +8;
		}
		while (p_Box[bPoint.x][bPoint.y]->piece != 0);
		gMove = 1;
	}

	if (bPoint.x>18)
		bPoint = CheckFourInARow(P2PIECE);
	
	if  (bPoint.x>18)
		bPoint = CheckThreePlusOne(P2PIECE);
	
	if (bPoint.x>18)
		bPoint = CheckOnePlusThree(P2PIECE);

	if(bPoint.x>18)
		bPoint = CheckTwoPlusTwo(P2PIECE);

	if (bPoint.x>18)
		bPoint =  CheckFourInARow (P1PIECE);
	
	if  (bPoint.x>18)
		bPoint = CheckThreePlusOne(P1PIECE);
		
	if (bPoint.x>18)
		bPoint = CheckOnePlusThree(P1PIECE);

	if(bPoint.x>18)
		bPoint = CheckTwoPlusTwo(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckOpenThree(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckOpenTwoPlusOne(P1PIECE);
	
	if (bPoint.x>18)
		bPoint = CheckOpenOnePlusTwo(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckOpenThree(P2PIECE);
  
	if (bPoint.x>18)
		bPoint = CheckOpenTwoPlusOne(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckOpenOnePlusTwo(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckOnePlusTwo(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckTwoPlusOne(P2PIECE);
		
	if (bPoint.x>18)
		bPoint = CheckThreeInARow(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckMoveCapture();

	if (bPoint.x>18)
		bPoint = CheckTwoInARow(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckOneDisplacedTwo(P2PIECE);
		
	if (bPoint.x>18)
		bPoint = CheckOnePlusTwo(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckTwoPlusOne(P1PIECE);
		
	if (bPoint.x>18)
		bPoint = CheckThreeInARow(P1PIECE);
	
	if (bPoint.x>18)
		bPoint = CheckOnePlusOne(P2PIECE);

	if (bPoint.x>18)
		bPoint = CheckTwoInARow(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckOneDisplacedTwo(P1PIECE);

	if (bPoint.x>18)
		bPoint = CheckOnePlusOne(P1PIECE);
		
	if (bPoint.x>18)
		bPoint = MoveNext(P2PIECE);
	
	/* try to move to center */ 
	if (bPoint.x>18)
	{
		for (i=0, j=0; i<3; j++)
		{
			if (p_Box[fPoint[i][j].x][fPoint[i][j].y]->piece == 0)
			{
				bPoint.x = fPoint[i][j].x;
				bPoint.y = fPoint[i][j].y;
				break;
			}
			if (j == 2)
			{
				i++;
				j =-1;
			}
		}
	}
	
	/* Choose random position if no other choice */
	if (bPoint.x>18)
	{
		/* seed random number generator w/time */
		srand( (unsigned)time( NULL ) );
		do 
		{
			bPoint.x = rand() % 19;
			bPoint.y = rand() % 19;
		}
		while (p_Box[bPoint.x][bPoint.y]->piece != 0);
	}

	DrawPiece(hWnd, bPoint, szP2Color);
	
	if (CheckCapture (hWnd, bPoint) || CheckFiveInARow (hWnd, bPoint))
			NewGame(hWnd);
}

///////////////////////
// NewGame  Function //
///////////////////////
void NewGame(HWND hWnd)
{
	int rtn;
	
	DialogBox(hInstance,"PLAYERS", hWnd, (DLGPROC)Players);
									
	rtn = MessageBox(hWnd, "Do you wish to play another game?",
						"WinPente",
						MB_ICONQUESTION |
						MB_YESNO |
						MB_DEFBUTTON1);
	
	if (rtn != IDYES)
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	else
		SendMessage(hWnd, WM_COMMAND,  ID_NEWGAME, 0);
}