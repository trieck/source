////////////////
// REGWIN.CPP //
////////////////

#include "winpente.h"

RECT cRect;				/* Large Rectangle */

//////////////////////////////
// RegisterWindow Function  //
//////////////////////////////
int RegisterWindow(HINSTANCE hInstance, const char* szAppName)
{
	WNDCLASS WindowClass;

	WindowClass.style = CS_BYTEALIGNCLIENT;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(hInstance, "MAINICON");
	WindowClass.hCursor = LoadCursor (0, IDC_ARROW);
	WindowClass.hbrBackground =0;
	WindowClass.lpszMenuName = "MAINMENU";
	WindowClass.lpszClassName = szAppName;

	if (!(RegisterClass(&WindowClass)))
		return(0);
	else
		return(1);
}
////////////////////////////
// DisplayWindow Function //
////////////////////////////
HWND DisplayWindow(HINSTANCE hInstance,
                   const char* szAppName,
                   const char* szTitle,
                   int nCmdShow)
{
	HWND hWnd;
	NONCLIENTMETRICS NonClientMetrics;
	RECT dw, rc;

	/* Adjust Rectangle based on Non Client Metrics */
	NonClientMetrics.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &NonClientMetrics, 0);

	rc.left = 0;
	rc.top = 0;
	rc.right = ((BoxSize * 19)+1) + (HOFFSET * 2) +
	           (GetSystemMetrics(SM_CXDLGFRAME)*2);
	rc.bottom = ((BoxSize * 19)+1) + (VOFFSET * 2) +
	            NonClientMetrics.iMenuHeight +
	            NonClientMetrics.iCaptionHeight +
	            20 + (GetSystemMetrics(SM_CYDLGFRAME)*2);

	AdjustWindowRectEx(&rc, WS_CAPTION |
	                   WS_BORDER |
	                   WS_MINIMIZEBOX |
	                   WS_SYSMENU, 1,
	                   WS_EX_OVERLAPPEDWINDOW);

	GetWindowRect(GetDesktopWindow(), &dw);

	hWnd = CreateWindowEx(
	           WS_EX_OVERLAPPEDWINDOW,
	           szAppName,
	           szTitle,
	           WS_MINIMIZEBOX|
	           WS_CAPTION |
	           WS_SYSMENU,
	           0,
	           0,
	           rc.right,
	           rc.bottom,
	           0,
	           0,
	           hInstance,
	           0);

	if (!hWnd)
		return (0);
	else {
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		return (hWnd);
	}
};
/////////////////////////
// BuildBoard Function //
/////////////////////////
void BuildBoard(HWND hWnd)
{
	int i,j,k,l;
	char szErrorMsg[50];

	/* Build Main Grid Rectangle */

	cRect.left = HOFFSET;
	cRect.top = VOFFSET;
	cRect.right = cRect.left + (BoxSize * 19)+1;
	cRect.bottom = cRect.top + (BoxSize * 19)+1;

	/* Build smaller rectangles */

	if (!(p_Board = (LPBOARD)calloc(19, sizeof(BOARD)))) {
		LoadString (hInstance, IDS_MEMERROR, szErrorMsg,50);
		MessageBox(hWnd, szErrorMsg, "Error", MB_OK);
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		return;
	}

	/* Initialize structure */
	p_Board->p1_captures = 0;
	p_Board->p2_captures = 0;
	p_Board->current_turn = 0;
	p_Board->game_option = PLAYER_VS_COMP;

	/* set 'p_Box' = RECT Array of p_Board */
	p_Box = &(p_Board->box);

	for (i=0, j=0, k=0, l=0; i<19; j++, k+=BoxSize) {
		p_Box[i][j]->piece = 0;
		p_Box[i][j]->bRect.left = cRect.left + k;
		p_Box[i][j]->bRect.top = cRect.top +l;
		p_Box[i][j]->bRect.right = (p_Box[i][j]->bRect.left) + BoxSize;
		p_Box[i][j]->bRect.bottom = (p_Box[i][j]->bRect.top) + BoxSize;
		if (j == 18) {
			i++;
			j=-1;
			k=-BoxSize;
			l+=BoxSize;
		}
	}
}

////////////////////////////
// DrawStatusBar Function //
////////////////////////////
void DrawStatusBar(HWND hWnd)
{
	HWND hWndStatus;
	RECT rc;
	int sb_piece;
	int aWidths[3];
	char sz_turnmsg[30];

	GetClientRect(hWnd, &rc);

	rc.right += GetSystemMetrics(SM_CXDLGFRAME);

	sb_piece = rc.right / 3;
	aWidths[0] = sb_piece;
	aWidths[1] = sb_piece * 2;
	aWidths[2] = sb_piece * 3;

	InitCommonControls();

	LoadString (hInstance, IDS_PLAYER1TURN,
	            sz_turnmsg, 30);

	hWndStatus = CreateStatusWindow (WS_CHILD |
	                                 WS_VISIBLE |
	                                 WS_CLIPSIBLINGS |
	                                 CCS_BOTTOM,
	                                 sz_turnmsg,
	                                 hWnd,
	                                 ID_STATUS);

	/* Split window into parts */
	SendDlgItemMessage(hWnd, ID_STATUS, SB_SETPARTS, 3, (LPARAM)&aWidths);
}
