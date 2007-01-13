//////////////////////////////////////////////////////	
//	Module	:	BMLOC.C								//
//	Purpose	:	custom bitmap functions	(local)		//
//	Author	:	Thomas A. Rieck						//
//	Date	:	4/5/97								//
//////////////////////////////////////////////////////

#include "bmmain.h"
#include "bmloc.h"
#include "bmexp.h"
#include "string.h"
#include "resource.h"

//////////////////////////
// CreateBitmapFromFile		
//
// note:	*** BE SURE TO DELETE THE HANDLE THIS FUNCTION RETURNS AFTER USE ***
HBITMAP CreateBitmapFromFile(HDC hDC, LPSTR szFileName)
{
	HFILE hFile;
	HBITMAP hBitmap;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	LPBITMAPINFO pBMI;
	LPVOID pBits;

	// open file
	hFile = _lopen(szFileName, OF_READ) ;
	if (hFile == HFILE_ERROR)
		return (0);

	// load BITMAPFILEHEADER structure 
	_lread(hFile, &bmfh, sizeof(BITMAPFILEHEADER));

	// load BITMAPINFOHEADER structure
	_lread(hFile, &bmih, sizeof(BITMAPINFOHEADER));

	// allocate memory for the BITMAPINFO structure
	if (bmih.biBitCount != 24)
		pBMI = malloc(sizeof(BITMAPINFOHEADER) + ((1<<bmih.biBitCount) * sizeof(RGBQUAD)));
	else
		pBMI = malloc(sizeof(BITMAPINFOHEADER));
	
	if (!pBMI)
	{
		_lclose(hFile);
		return (0);
	}

	// load BITMAPINFOHEADER into the BITMAPINFO structure. 
	pBMI->bmiHeader.biSize = bmih.biSize; 
	pBMI->bmiHeader.biWidth = bmih.biWidth; 
	pBMI->bmiHeader.biHeight = bmih.biHeight; 
	pBMI->bmiHeader.biPlanes = bmih.biPlanes; 
	pBMI->bmiHeader.biBitCount = bmih.biBitCount; 
	pBMI->bmiHeader.biCompression = bmih.biCompression; 
	pBMI->bmiHeader.biSizeImage = bmih.biSizeImage; 
	pBMI->bmiHeader.biXPelsPerMeter = bmih.biXPelsPerMeter; 
	pBMI->bmiHeader.biYPelsPerMeter = bmih.biYPelsPerMeter; 
	pBMI->bmiHeader.biClrUsed = bmih.biClrUsed; 
	pBMI->bmiHeader.biClrImportant = bmih.biClrImportant;

	// retrieve the color table. 
	if (bmih.biBitCount != 24)
		_lread(hFile, pBMI->bmiColors, ((1<<bmih.biBitCount) * sizeof(RGBQUAD)));
	
	// allocate memory for bits
	if (!(pBits = malloc (bmfh.bfSize - bmfh.bfOffBits)))
	{
		free (pBMI);
		_lclose(hFile);
		return (0);
	}

	// read bitmap data
	_lread(hFile, pBits, (bmfh.bfSize - bmfh.bfOffBits));

	// create DDB from DIB stored in file
	hBitmap = CreateDIBitmap(hDC, &bmih, CBM_INIT, pBits, pBMI, DIB_RGB_COLORS);

	// release allocated memory and close file
	free (pBMI);
	free (pBits);
	_lclose(hFile);

	return (hBitmap);
}

///////////////
// DlgProc
BOOL CALLBACK DlgProc(	HWND  hwndDlg,	// handle to dialog box
						UINT  uMsg,		// message
						WPARAM  wParam,	// first message parameter
						LPARAM  lParam)
{
	// bitmap filename
	static char szFileName[_MAX_PATH + _MAX_FNAME + 1];

	static BITMAPFILEHEADER bmfh;
	static LPBITMAPINFO		pBMI	= 0;
	static LPVOID			pBits	= 0;
	LPVOID pTemp;
		
	PAINTSTRUCT ps;
	HDC hDC;
	HWND hwndPct;
	DWORD dwBitSize;
	DWORD dwScanWidth;
	DWORD dwTemp;
	POINT pt = {0,0};
			
	switch (uMsg) 
	{ 
	case WM_INITDIALOG:
		// make sure device is capable
		hwndPct = GetDlgItem(hwndDlg, IDC_PICTURE);
		
		if (!(AssertDevCapable(hwndPct, RC_STRETCHDIB)))
		{
			EndDialog(hwndDlg, FALSE);
			return (FALSE);
		}

		strcpy(szFileName, (LPSTR)lParam);

		if (!(ExtractBMInfo(szFileName, &bmfh, &pBMI, &pBits)))
			return (FALSE);

		// check for 24 bit BM to enable stripping
		if (pBMI->bmiHeader.biBitCount != 24)
		{
			EnableWindow(GetDlgItem(hwndDlg, IDC_STRIPRED), FALSE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_STRIPGREEN), FALSE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_STRIPBLUE), FALSE);
		}
		
		FillDlgInfo(hwndDlg, szFileName, bmfh, pBMI);

		// set focus
		SetFocus(GetDlgItem(hwndDlg, IDC_FILENAME));
		
		return (TRUE);
		break;
	case WM_COMMAND:
		switch	(LOWORD(wParam))
		{
		case IDC_FLIP:
			
			if (pBits != 0 && pBMI->bmiHeader.biHeight != 0)
			{
				switch (pBMI->bmiHeader.biBitCount)
				{
				case 1:
					dwScanWidth = ScanAlign((pBMI->bmiHeader.biWidth+7) / 8);
					break;
				case 4:
					dwScanWidth = ScanAlign((pBMI->bmiHeader.biWidth+1) / 2);
					break;
				case 8:
					dwScanWidth = ScanAlign(pBMI->bmiHeader.biWidth);
					break;
				case 24:
					dwScanWidth = ScanAlign(pBMI->bmiHeader.biWidth * 3);
					break;
				}
				
				dwBitSize = dwScanWidth * pBMI->bmiHeader.biHeight;					

				if (!(pTemp = malloc(dwBitSize)))
					break;

				memcpy(pTemp, pBits, dwBitSize);
				
				for (dwTemp = 0; dwTemp < dwBitSize; dwTemp += dwScanWidth)
					memcpy((LPBYTE)pBits + dwTemp,(LPBYTE)pTemp + (dwBitSize - dwTemp), dwScanWidth);
				
				if (pTemp) free(pTemp);

				InvalidateRect(GetDlgItem (hwndDlg, IDC_PICTURE), 0, FALSE);
			}
			break;
		case IDC_STRIPRED:
			StripBits (pBMI, pBits, 2);
			InvalidateRect(GetDlgItem (hwndDlg, IDC_PICTURE), 0, FALSE);
			break;
		case IDC_STRIPGREEN:
			StripBits (pBMI, pBits, 1);
			InvalidateRect(GetDlgItem (hwndDlg, IDC_PICTURE), 0, FALSE);
			break;
		case IDC_STRIPBLUE:
			StripBits (pBMI, pBits, 0);
			InvalidateRect(GetDlgItem (hwndDlg, IDC_PICTURE), 0, FALSE);
			break;
		case IDCANCEL:
			// free allocated buffers
			if (pBMI) free(pBMI);
			if (pBits) free(pBits);
			
			pBMI = 0;
			pBits = 0;

			EndDialog(hwndDlg, FALSE);
			break;
		}
	case WM_PAINT:
		hDC = BeginPaint(hwndDlg, &ps);

		// get dialog picture handle
		hwndPct = GetDlgItem (hwndDlg, IDC_PICTURE);
							
		if (pBMI != 0 && pBits != 0)
			StretchBitmap(hwndPct, pBMI, pBits, &pt); 
					
		EndPaint(hwndDlg, &ps);
		break;
	default: 
		return (FALSE); 
    } 
}

//////////////////
// ExtractBMInfo
int ExtractBMInfo(LPSTR szFileName, LPBITMAPFILEHEADER pBMFH, LPBITMAPINFO* ppBMI, LPVOID* ppBits)
{
	DWORD dwBMISize;
	DWORD dwBitSize;
		
	// extract BITMAPFILEHEADER
	if (!(ExtractBMFH(szFileName, pBMFH)))
		return (0);

	// get BITMAPINFO size
	dwBMISize = GetBMISize(szFileName);

	// allocate buffer for BITMAPINFO structure
	if (!(*ppBMI = malloc(dwBMISize)))
		return(0);

	// extract BITMAPINFO structure
	ExtractBMI(szFileName, *ppBMI);

	// get bit size
	dwBitSize = GetBitSize(szFileName);

	// allocate buffer for bits
	if (!(*ppBits = malloc(dwBitSize)))
	{
		free (*ppBMI);
		return(0);
	}

	// get bitmap bits
	GetBMBits(szFileName, *ppBits);

	return (1);
}

////////////////
// FillDlgInfo
void FillDlgInfo(HWND hDlg, LPSTR szFileName, BITMAPFILEHEADER bmfh, LPBITMAPINFO pBMI)
{
	char szBuff[20];

	// set bitmap filename in dialog
	SetDlgItemText(hDlg, IDC_FILENAME, szFileName);

	// set bitmap filesize
	sprintf(szBuff, "%d%s", bmfh.bfSize, " Bytes.");
	SetDlgItemText(hDlg, IDC_BMFILESIZE, szBuff);

	// set bitmap dimensions
	sprintf(szBuff, "%d%s%d", pBMI->bmiHeader.biWidth, " x ", pBMI->bmiHeader.biHeight);
	SetDlgItemText(hDlg, IDC_BMDIMENSIONS, szBuff);

	// set bit count
	sprintf(szBuff, "%d%s", pBMI->bmiHeader.biBitCount, " Bits Per Pixel.");
	SetDlgItemText(hDlg, IDC_BMBITCOUNT, szBuff);
}

//////////////////////
// AssertValidBitmap
int AssertValidBitmap(LPSTR szFileName)
{
	HFILE hFile;
	WORD bfType[1];

	hFile = _lopen(szFileName, OF_READ);
	if (hFile == HFILE_ERROR)
		return (0);

	_lread(hFile, (LPVOID)bfType, sizeof(WORD));

	_lclose(hFile);

	return (bfType[0] == 0x4d42 ? 1 : 0);
}

/////////////////////
// AssertDevCapable
int AssertDevCapable(HWND hWnd, INT nFlags)
{
	HDC hDC;
	char szBuff[255];
		
	hDC = GetDC(hWnd);
	
	// determine if device is capable
	if (!(GetDeviceCaps(hDC, RASTERCAPS) & nFlags))
	{
		LoadString(hInstance, IDS_DEVNOTCAPABLE, szBuff, 255);
		MessageBox(hWnd, szBuff, "Error", MB_ICONEXCLAMATION | MB_OK);
		ReleaseDC(hWnd, hDC);
		return (0);
	}	
	
	ReleaseDC(hWnd, hDC);
	return (1);
}
	
////////////////////
// ScanAlign
LONG ScanAlign (LONG pWidth)
{
	return ((pWidth + 3) & 0XFFFFFFFC);
}

///////////////////
// StripBits
void StripBits (LPBITMAPINFO pBMI, LPBYTE pBits, UINT nColor)
{
	LONG  lHeight, lWidth;
	LPBYTE pOffset, pAddr;
	LPBYTE zArray[1] = {0};
	DWORD dwBitSize;
	DWORD dwScanWidth;

	if (pBits != 0 && pBMI->bmiHeader.biHeight != 0)
	{
		dwScanWidth = ScanAlign(pBMI->bmiHeader.biWidth * 3);
								
		dwBitSize = dwScanWidth * pBMI->bmiHeader.biHeight;					
				
		pOffset = pBits;

		for (lHeight = 0; lHeight < abs(pBMI->bmiHeader.biHeight); lHeight++)
		{
			pAddr = pOffset + nColor;
			for (lWidth = 0; lWidth < pBMI->bmiHeader.biWidth; lWidth++)
			{
				memmove(pAddr, zArray, 1);
				pAddr += 3;
			}
			pOffset += dwScanWidth;
		}
			
	}
}

	
