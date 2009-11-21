//////////////////
// WINPENTE.CPP //
//////////////////

#include "winpente.h"

HINSTANCE	hInstance;
const char	szTitle[] = "Pente for Windows";
int			BoxSize;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
	const char	szAppName[] = "WinPente";
	MSG			msg;
	HDC			hDC;
	HWND		hPrevWnd;
	int			hRes;

	hInstance = hInst;

	if (hPrevWnd = FindWindow(szAppName, NULL)) {
		ShowWindow(hPrevWnd, SW_RESTORE);
		return(0);
	}

	/* Find Box Size */
	hDC = GetDC(GetDesktopWindow());
	hRes =  GetDeviceCaps(hDC, HORZRES);
	BoxSize = hRes <800 ? hRes / 38 : 21;
	ReleaseDC(GetDesktopWindow(), hDC);

	if (!(RegisterWindow(hInstance, szAppName)))
		return(0);

	if (!(DisplayWindow(hInstance, szAppName, szTitle, nCmdShow)))
		return(0);

	while (GetMessage(&msg, 0, 0, 0) == TRUE) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}