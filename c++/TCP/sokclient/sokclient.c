////////////////////////////////
//	Module:	SOKCLIENT.C		  //
//	Author:	Thomas A. Rieck	  //
//	Date:	05/25/97		  //
////////////////////////////////

#include	"..\MERLIN.H"
#include	"SOKCLIENT.H"
#include	"resource.h"

HINSTANCE	hInst;
SOCKET		sock;
LPCSTR		lpszClassName	= "SocketClient";
CONST INT	WINDOW_STYLE	=	WS_SYSMENU |
                                WS_MINIMIZEBOX |
                                WS_BORDER |
                                WS_CAPTION;

////////////////////////
// WinMain Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!hPrevInstance)
		if (!InitApplication(hInstance))
			return (0);

	if (!InitInstance(hInstance, nCmdShow))
		return (0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

/////////////////////////////
// InitApplication Function
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;

	wc.style			= 0;
	wc.lpfnWndProc		= (WNDPROC)MainWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wc.hInstance		= hInstance;
	wc.hCursor			= NULL;
	wc.hbrBackground	= GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName	= lpszClassName;

	return (RegisterClass(&wc));
}

//////////////////////////
// InitInstance Function
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd;

	hInst = hInstance;

	// disallow multiple instances
	if (FindWindow(lpszClassName, NULL))
		return (FALSE);

	hWnd = CreateWindowEx(
	           WS_EX_DLGMODALFRAME,			// Extended Window style
	           lpszClassName,					// Window Class Name
	           "Socket Client",				// Window Caption
	           WINDOW_STYLE,					// Window style.
	           CW_USEDEFAULT,                  // Default horizontal position.
	           CW_USEDEFAULT,                  // Default vertical position.
	           CW_USEDEFAULT,					// Default width
	           CW_USEDEFAULT,					// Default height
	           NULL,                           // Overlapped windows have no parent.
	           NULL,                           // Use the window class menu.
	           hInstance,                      // This instance owns this window.
	           NULL							// Pointer not needed.
	       );

	if (!hWnd)
		return (FALSE);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return (TRUE);
}

////////////////////////////
// MainWndProc Function
LONG APIENTRY MainWndProc(HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
	static HWND			hMainDlg, hWndToolBar, hWndStatus;
	static CHAR			szHostName[25];
	static CHAR			szHostBuffer[MAXGETHOSTSTRUCT];
	static HCURSOR		hCursor;
	static HANDLE		hHostID;
	static SOCKADDR_IN	dest_sin;
	CHAR				szSendString[80];
	CHAR				szStrBuffer[80];
	RECT				DlgRect;
	BOOL				status;
	WSADATA				WSAData;
	WSABUF				WSABuffer;
	LPNMHDR				pnmh;
	LPHOSTENT			lphp;
	DWORD				dwBytesSent;

	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT),
			          hWnd, AboutProc);
			break;
		case IDM_CONNECT:
		case IDT_CONNECT:

			SetCapture(hWnd);
			hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

			GetDlgItemText(hMainDlg, IDC_HOSTNAME, szHostName, 80);
			if (!strlen(szHostName)) {
				LoadString(hInst, IDS_HOSTNAMEERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL,
				           MB_OK | MB_ICONINFORMATION);
				SetCursor(hCursor);
				ReleaseCapture();
				break;
			}

			// create socket
			sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

			if (sock == INVALID_SOCKET) {
				LoadString(hInst, IDS_CREATESOCKERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
				SetCursor(hCursor);
				ReleaseCapture();
				break;
			}

			// retrieve IP address and TCP port number
			// from host name, will call WM_WSGETHOST when
			// returning data
			if (!(hHostID = WSAAsyncGetHostByName(hWnd, WM_WSGETHOST,
			                                      szHostName, szHostBuffer, MAXGETHOSTSTRUCT))) {
				closesocket(sock);
				LoadString(hInst, WSAGetLastError(), szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
				SetCursor(hCursor);
				ReleaseCapture();
				break;
			}

			// select asynchronous messages
			if (WSAAsyncSelect(sock, hWnd, WSA_ASYNC, FD_CONNECT | FD_CLOSE) > 0) {
				closesocket(sock);
				LoadString(hInst, IDS_ASYNCERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
				SetCursor(hCursor);
				ReleaseCapture();
				break;
			}
			break;
		case IDT_SEND:
		case IDM_SENDMESSAGE:
			break;

			status = GetDlgItemText(hMainDlg, IDC_MESSAGE, szSendString, 80);

			if (!status || !strlen(szSendString))
				break;

			// send the string
			WSABuffer.len = sizeof(REQUEST);
			WSABuffer.buf = szSendString;
			if (WSASend(sock, &WSABuffer, 1, &dwBytesSent, NO_FLAGS_SET, NULL, NULL) == SOCKET_ERROR) {
				LoadString(hInst, IDS_SENDERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
				break;
			}
			// set status window
			LoadString(hInst, IDS_STATUSBYTES, szStrBuffer, 80);
			sprintf(szStrBuffer, szStrBuffer, status);
			SendMessage(hWndStatus, SB_SETTEXT, 1, (LPARAM)szStrBuffer);
			break;
		case IDM_EXIT:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case IDM_DISCONNECT:
		case IDT_DISCONNECT:
			shutdown(sock, SD_SEND);
			closesocket(sock);

			// enable menus and toolbar buttons
			SetConnectMenus(hWnd, hWndToolBar, FALSE);
			SetConnectState(hWndStatus, FALSE);

			break;
		case IDM_DISKINFO:
		case IDT_DISKINFO:
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DISKINFO),
			               hWnd, DiskInfoProc, (LPARAM)&dest_sin);
			break;
		default:
			break;
		}
		break;
	case WSA_ASYNC:
		switch (WSAGETSELECTEVENT(lParam)) {
		case FD_CLOSE:
			LoadString(hInst, IDS_CONNECTDROP, szStrBuffer, 80);
			MessageBox(hWnd, szStrBuffer, NULL,
			           MB_OK | MB_ICONEXCLAMATION);

			// close the socket
			shutdown(sock, SD_SEND);
			closesocket(sock);

			// enable menus and toolbar buttons
			SetConnectMenus(hWnd, hWndToolBar, FALSE);
			SetConnectState(hWndStatus, FALSE);

			break;
		case FD_CONNECT:
			SetCursor(hCursor);
			ReleaseCapture();
			// connection completed. check for errors
			if (WSAGETSELECTERROR(lParam) == 0) {
				// connected
				// enable menus and toolbar buttons
				SetConnectMenus(hWnd, hWndToolBar, TRUE);
				SetConnectState(hWndStatus, TRUE);
			} else {
				// not connected
				LoadString(hInst, IDS_CONNECTERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);

				// enable menus and toolbar buttons
				SetConnectMenus(hWnd, hWndToolBar, FALSE);
				SetConnectState(hWndStatus, FALSE);
			}
			break;
		}
		break;
	case WM_WSGETHOST:
		if (wParam != (WPARAM)hHostID)	// ignore message
			break;

		if (WSAGETASYNCERROR(lParam) != 0) {
			closesocket(sock);
			LoadString(hInst, IDS_HOSTBYNAMEERR, szStrBuffer, 80);
			MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
			SetCursor(hCursor);
			ReleaseCapture();
			break;
		}

		// set address information
		dest_sin.sin_family			= PF_INET;
		dest_sin.sin_port			= ResolveServicePort();
		lphp						= (LPHOSTENT)szHostBuffer;
		dest_sin.sin_addr.s_addr	= ((LPIN_ADDR)(lphp->h_addr))->s_addr;

		// connect
		if (WSAConnect(sock, (PSOCKADDR)&dest_sin, sizeof(dest_sin), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
			// error occured on connect call.  however expecting
			// to get WSAEWOULDBLOCK error indicating that
			// connection is in progress
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				closesocket(sock);
				LoadString(hInst, IDS_CONNECTERR, szStrBuffer, 80);
				MessageBox(hWnd, szStrBuffer, NULL, MB_OK | MB_ICONINFORMATION);
				SetCursor(hCursor);
				ReleaseCapture();
			}
		}
		break;
	case WM_CREATE:
		// start winsock services
		if ((status = WSAStartup(MAKEWORD(2,0),  &WSAData)) != 0) {
			MessageBox(hWnd, WSAData.szDescription,
			           WSAData.szSystemStatus, MB_OK | MB_ICONINFORMATION);
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}

		// show main dialog
		hMainDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN),
		                        hWnd, MainDlgProc);

		GetWindowRect(hMainDlg, &DlgRect);
		AdjustWindowRectEx(&DlgRect, WINDOW_STYLE, TRUE, WS_EX_DLGMODALFRAME);

		// move the dialog box past the toolbar
		SetWindowPos(hMainDlg, HWND_TOP, 0, 28, 0, 0, SWP_NOSIZE);

		// resize the window to accomodate the dialog box
		SetWindowPos(hWnd, HWND_TOP, 0, 0, (DlgRect.right - DlgRect.left),
		             (DlgRect.bottom - DlgRect.top), SWP_NOMOVE);

		// show toolbar
		hWndToolBar = CreateToolBar(hWnd);

		// show status bar
		hWndStatus = CreateStatusBar(hWnd);

		// show connect state
		SetConnectState(hWndStatus, FALSE);
		break;
	case WM_NOTIFY:
		pnmh = (LPNMHDR)lParam;

		// check whether the tooltip needs text
		if (pnmh->code == TTN_NEEDTEXT) {
			LPTOOLTIPTEXT lpttt;

			lpttt = (LPTOOLTIPTEXT) lParam;
			lpttt->hinst = hInst;

			// specify the resource identifier of the descriptive
			// text for the given button.
			switch (lpttt->hdr.idFrom) {
			case IDT_CONNECT:
				lpttt->lpszText = MAKEINTRESOURCE(IDS_TIPS_CONNECT);
				break;
			case IDT_SEND:
				lpttt->lpszText = MAKEINTRESOURCE(IDS_TIPS_SENDMESSAGE);
				break;
			case IDT_DISCONNECT:
				lpttt->lpszText = MAKEINTRESOURCE(IDS_TIPS_EXIT);
				break;
			case IDT_DISKINFO:
				lpttt->lpszText = MAKEINTRESOURCE(IDS_TIPS_DISKINFO);
				break;
			}
		}
		break;
	case WM_SIZE:
		// resize the toolbar
		SendMessage(hWndToolBar, TB_AUTOSIZE, 0, 0);
		break;
	case WM_DESTROY:
		// shutdown winsock services
		shutdown(sock, SD_SEND);
		closesocket(sock);
		WSACleanup();

		// destroy dialog
		if (hMainDlg) DestroyWindow(hMainDlg);

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return (0);
}

/////////////////////////
// MainDlgProc Function
BOOL WINAPI MainDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		return (TRUE);
	default:
		break;
	}
	return (FALSE);
}

////////////////////////////////
// ResolveServicePort Function
WORD ResolveServicePort()
{
	PSERVENT pse;

	if (!(pse = getservbyname(SERVICE_NAME, "tcp")))
		return (0);
	else
		return (pse->s_port);
}

///////////////////////
// AboutProc Function
BOOL WINAPI AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		return (TRUE);
	case WM_COMMAND:
		switch (wParam) {
		case IDCANCEL:
		case IDOK:
			EndDialog(hDlg, TRUE);
		}
	default:
		break;
	}
	return (FALSE);
}

//////////////////////////
// DiskInfoProc Function
BOOL WINAPI DiskInfoProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HICON		hIcon;
	static HCURSOR		hCursor;
	LPSOCKADDR_IN		lpdest_sin;
	CHAR				szInetAddr[16];
	CHAR				szBuffer[80];
	CONST DWORD			nBufferLen = 80;
	CONST UINT			ICON_WIDTH = 16;
	CONST UINT			ICON_HEIGHT = 16;
	INT					iRc;
	LPSTR				lpPos;
	LPMEASUREITEMSTRUCT	lpMIS;
	LPDRAWITEMSTRUCT	lpDIS;
	TEXTMETRIC			tm;
	HWND				hWndList;
	HDC					hDC;
	REQUEST				req;
	RESPONSE			rsp;

	switch (msg) {
	case WM_INITDIALOG:
		// get destination address
		lpdest_sin = (LPSOCKADDR_IN)lParam;

		// get the IP address in dotted format
		strcpy(szInetAddr, inet_ntoa(lpdest_sin->sin_addr));
		if (!szInetAddr)
			EndDialog(hDlg, FALSE);

		// select aynchronous messages
		iRc = WSAAsyncSelect(sock, hDlg, WSA_ASYNC, FD_READ | FD_WRITE | FD_CLOSE);

		// set the IP address in dialog box
		SetDlgItemText(hDlg, IDC_SERVERADDRESS, szInetAddr);

		// send the request to enumerate drives
		req.cType		= GET;
		req.cSubType	= DISK;
		req.cDetails	= ENUMDRIVES;

		iRc = send(sock, (LPSTR)&req, sizeof(REQUEST), 0);
		if ((iRc == SOCKET_ERROR || iRc < sizeof(REQUEST))) {
			LoadString(hInst, IDS_SENDERR, szBuffer, 80);
			MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
			return (FALSE);
		}

		// load the drive icon
		hIcon = (HCURSOR)LoadImage(hInst, MAKEINTRESOURCE(IDI_DRIVE),
		                           IMAGE_ICON, ICON_WIDTH, ICON_HEIGHT, LR_DEFAULTCOLOR);

		return (TRUE);
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			INT		nSel;
			CHAR	szDriveName[4];

		case IDCANCEL:
		case IDOK:
			// reset select messages
			WSAAsyncSelect(sock, GetParent(hDlg), WSA_ASYNC, FD_CONNECT | FD_CLOSE);
			EndDialog(hDlg, TRUE);
			break;
		case IDC_DRIVELIST:
			if (HIWORD(wParam) == LBN_DBLCLK) {
				nSel = SendDlgItemMessage(hDlg, IDC_DRIVELIST,
				                          LB_GETCURSEL, 0, 0);

				if (nSel != LB_ERR) {
					SetCapture(hDlg);
					hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

					SendDlgItemMessage(hDlg, IDC_DRIVELIST,
					                   LB_GETTEXT, nSel, (LPARAM)szDriveName);

					// send the request for disk information
					req.cType		= GET;
					req.cSubType	= DISK;
					req.cDetails	= DISKINFO;
					strcpy(req.cMsgSpec, szDriveName);

					iRc = send(sock, (LPSTR)&req, sizeof(REQUEST), 0);
					if ((iRc == SOCKET_ERROR || iRc < sizeof(REQUEST))) {
						SetCursor(hCursor);
						ReleaseCapture();
						LoadString(hInst, IDS_SENDERR, szBuffer, 80);
						MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
						break;
					}

				}
			}
			break;
		}
		break;
	case WSA_ASYNC:
		switch (WSAGETSELECTEVENT(lParam)) {
		case FD_READ:
			iRc = recv(sock, (LPSTR)&rsp, sizeof(RESPONSE), 0);
			if (iRc == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					LoadString(hInst, IDS_RCVERR, szBuffer, 80);
					MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
					break;
				} else
					break;

			}

			// program not prepared to
			// receive anything but a response
			// structure.
			if (iRc != sizeof(RESPONSE) || rsp.cType != RSP)
				break;

			if (rsp.cError != SUCCESS) {
				LoadString(hInst, IDS_REQERR, szBuffer, 80);
				MessageBox(hDlg, szBuffer, NULL, MB_ICONINFORMATION);
				break;
			}

			switch (rsp.cSubType) {
				CHAR szTemp[80];

			case DISK:
				switch (rsp.cDetails) {
					DISKINFOSTRUCT	dis;

				case ENUMDRIVES:
					lpPos = rsp.cMsgSpec;
					while (lpPos < (rsp.cMsgSpec + ntohs(rsp.iMsgLen))) {
						SendDlgItemMessage(hDlg, IDC_DRIVELIST, LB_ADDSTRING, 0, (LPARAM)lpPos);
						lpPos = strchr(lpPos, 0) + 1;
					}
					break;
				case DISKINFO:
					memcpy(&dis, (LPDISKINFOSTRUCT)rsp.cMsgSpec, sizeof(DISKINFOSTRUCT));
					LoadString(hInst, IDS_DISKINFO, szTemp, 80);
					sprintf(szBuffer, szTemp, ntohl(dis.lTotalBytes), ntohl(dis.lFreeBytes));
					MessageBox(hDlg, szBuffer, "Server Disk Information", MB_ICONINFORMATION);
					break;
				}
				break;
			}
			break;
		case FD_CLOSE:	// remote side has closed socket
			// route message back to main window
			// and close dialog box
			SendMessage(GetParent(hDlg), WSA_ASYNC, 0, MAKELPARAM(FD_CLOSE, 0));
			EndDialog(hDlg, FALSE);
			break;
		}
		break;
	case WM_MEASUREITEM:	// owner drawn list box
		lpMIS = (LPMEASUREITEMSTRUCT)lParam;

		hWndList = GetDlgItem(hDlg, IDC_DRIVELIST);

		hDC = GetDC(hWndList);

		GetTextMetrics(hDC, &tm);

		lpMIS->itemWidth	= tm.tmAveCharWidth;
		lpMIS->itemHeight	= tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hWndList, hDC);

		break;
	case WM_DRAWITEM:	// owner drawn listbox
		lpDIS = (LPDRAWITEMSTRUCT)lParam;

		if (lpDIS->itemID == -1)
			break;

		switch (lpDIS->itemAction) {
			INT y;
			CHAR tchBuffer[10];
			HBRUSH hBrush, hBrushOld;

		case ODA_SELECT:
		case ODA_DRAWENTIRE:
			// get item text
			SendMessage(lpDIS->hwndItem, LB_GETTEXT,
			            lpDIS->itemID, (LPARAM) tchBuffer);

			// retrieve position
			GetTextMetrics(lpDIS->hDC, &tm);
			y = (lpDIS->rcItem.bottom + lpDIS->rcItem.top -
			     tm.tmHeight) / 2;

			// check if item is selected
			if (lpDIS->itemState & ODS_SELECTED)
				// draw selected rectangle
				hBrush = CreateSolidBrush(COLOR_YELLOW);
			else	// draw default background
				hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

			hBrushOld = SelectObject(lpDIS->hDC, hBrush);
			FillRect(lpDIS->hDC, &(lpDIS->rcItem), hBrush);
			SelectObject(lpDIS->hDC, hBrushOld);
			DeleteObject(hBrush);

			// set background mode
			SetBkMode(lpDIS->hDC, TRANSPARENT);

			// draw the icon
			DrawIconEx(lpDIS->hDC, 0, y, hIcon, ICON_WIDTH, ICON_HEIGHT,
			           0, 0, DI_NORMAL);

			// display the text item
			TextOut(lpDIS->hDC,
			        ICON_WIDTH + 5,
			        y,
			        tchBuffer,
			        strlen(tchBuffer));

			break;
		}
		break;
	default:
		break;
	}
	return (FALSE);
}

///////////////////////////
// CreateToolBar Function
HWND CreateToolBar(HWND hWndParent)
{
	HWND hWndToolBar;
	TBBUTTON tbb[MAXTOOLBUTTONS];

	// initialize common control library
	InitCommonControls();

	// set toolbar buttons
	// seperator 1
	tbb[0].iBitmap		= 0;
	tbb[0].idCommand	= IDT_SEPERATOR;
	tbb[0].fsState		= 0;
	tbb[0].fsStyle		= TBSTYLE_SEP;
	tbb[0].dwData		= 0;
	tbb[0].iString		= 0;

	// connect button
	tbb[1].iBitmap		= 1;
	tbb[1].idCommand	= IDT_CONNECT;
	tbb[1].fsState		= TBSTATE_ENABLED;
	tbb[1].fsStyle		= TBSTYLE_BUTTON;
	tbb[1].dwData		= 0;
	tbb[1].iString		= 0;

	// disconnect button
	tbb[2].iBitmap		= 2;
	tbb[2].idCommand	= IDT_DISCONNECT;
	tbb[2].fsState		= 0;
	tbb[2].fsStyle		= TBSTYLE_BUTTON;
	tbb[2].dwData		= 0;
	tbb[2].iString		= 0;

	// seperator 2
	tbb[3].iBitmap		= 3;
	tbb[3].idCommand	= IDT_SEPERATOR2;
	tbb[3].fsState		= 0;
	tbb[3].fsStyle		= TBSTYLE_SEP;
	tbb[3].dwData		= 0;
	tbb[3].iString		= 0;

	// send button
	tbb[4].iBitmap		= 4;
	tbb[4].idCommand	= IDT_SEND;
	tbb[4].fsState		= 0;
	tbb[4].fsStyle		= TBSTYLE_BUTTON;
	tbb[4].dwData		= 0;
	tbb[4].iString		= 0;

	// disk information button
	tbb[5].iBitmap		= 5;
	tbb[5].idCommand	= IDT_DISKINFO;
	tbb[5].fsState		= 0;
	tbb[5].fsStyle		= TBSTYLE_BUTTON;
	tbb[5].dwData		= 0;
	tbb[5].iString		= 0;

	// create the maintoolbar window
	hWndToolBar = CreateToolbarEx(hWndParent,
	                              WS_CHILD |
	                              WS_VISIBLE |
	                              TBSTYLE_TOOLTIPS,
	                              IDR_TBARMAIN,
	                              MAXTOOLBUTTONS - 1,
	                              hInst,
	                              IDR_TBARMAIN,
	                              tbb,
	                              MAXTOOLBUTTONS,
	                              16,
	                              16,
	                              16,
	                              16,
	                              sizeof (TBBUTTON));

	// return the toolbar handle
	return (hWndToolBar);
}

/////////////////////////////
// CreateStatusBar Function
//	NOTE ***	Must call InitCommonControls()
//				before this call ***
HWND CreateStatusBar(HWND hWndParent)
{
	HWND hwndStatus;
	RECT rc;
	INT  aWidths[2];

	// create the status bar
	hwndStatus = CreateStatusWindow(WS_VISIBLE | WS_CHILD,
	                                NULL,
	                                hWndParent,
	                                ID_STATUSBAR);

	// set status bar parts
	GetClientRect(hWndParent, &rc);

	aWidths[0] = (rc.right - rc.left) /2;
	aWidths[1] = -1;

	SendMessage(hwndStatus, SB_SETPARTS, 2, (LPARAM)aWidths);

	return (hwndStatus);
}

//////////////////////////////
// SetConnectState Function
VOID SetConnectState(HWND hWndStatus, BOOL bConnected)
{
	CHAR szMessage[25];

	if (bConnected)
		LoadString(hInst, IDS_CONNECTED, szMessage, 25);
	else
		LoadString(hInst, IDS_NOTCONNECTED, szMessage, 25);

	SendMessage(hWndStatus, SB_SETTEXT, 0, (LPARAM)szMessage);
}

/////////////////////////////
// SetConnectMenus Function
VOID SetConnectMenus(HWND hWnd, HWND hWndToolBar, BOOL bConnect)
{
	// enable menus and buttons
	if (bConnect) {
		EnableMenuItem(GetMenu(hWnd), IDM_CONNECT, MF_GRAYED);
		EnableMenuItem(GetMenu(hWnd), IDM_DISCONNECT, MF_ENABLED);
		EnableMenuItem(GetMenu(hWnd), IDM_SENDMESSAGE, MF_ENABLED);
		EnableMenuItem(GetMenu(hWnd), IDM_DISKINFO, MF_ENABLED);

		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_CONNECT, (LPARAM)MAKELONG(FALSE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_DISCONNECT, (LPARAM)MAKELONG(TRUE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_SEND, (LPARAM)MAKELONG(TRUE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_DISKINFO, (LPARAM)MAKELONG(TRUE,0));
	} else {
		EnableMenuItem(GetMenu(hWnd), IDM_CONNECT, MF_ENABLED);
		EnableMenuItem(GetMenu(hWnd), IDM_DISCONNECT, MF_GRAYED);
		EnableMenuItem(GetMenu(hWnd), IDM_SENDMESSAGE, MF_GRAYED);
		EnableMenuItem(GetMenu(hWnd), IDM_DISKINFO, MF_GRAYED);

		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_CONNECT, (LPARAM)MAKELONG(TRUE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_DISCONNECT, (LPARAM)MAKELONG(FALSE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_SEND, (LPARAM)MAKELONG(FALSE,0));
		SendMessage(hWndToolBar, TB_ENABLEBUTTON, (WPARAM)IDT_DISKINFO, (LPARAM)MAKELONG(FALSE,0));
	}
}


