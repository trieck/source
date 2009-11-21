#include "stdafx.h"
#include "Palette256.h"
#include "StringTokenizer.h"
#include "resource.h"

Palette256::Palette256Ptr Palette256::This;

/////////////////////////////////////////////////////////////////////////////
Palette256::Palette256() : m_pPalette(NULL)
{
	load();
}

/////////////////////////////////////////////////////////////////////////////
Palette256::~Palette256()
{
	delete [] m_pPalette;
}

/////////////////////////////////////////////////////////////////////////////
void Palette256::load()
{
	HRSRC hResource = ::FindResource(AfxGetResourceHandle(),
	                                 MAKEINTRESOURCE(IDR_DEF_PALETTE),
	                                 "PALETTE");
	if (hResource == NULL)
		AfxThrowResourceException();

	HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hResource);
	if (hGlobal == NULL)
		AfxThrowResourceException();

	LPCSTR pResource = (LPCSTR)::LockResource(hGlobal);
	if (pResource == NULL) {
		UnlockResource(hGlobal);
		FreeResource(hGlobal);
		AfxThrowResourceException();
	}

	StringTokenizer tokenizer(pResource, "\r\n");
	CString tok;

	int red, green, blue;
	COLORREF color;

	m_pPalette = new RGBTRIPLE[NUM_PALETTE_COLORS];
	for (uint8_t i = 0; i < NUM_PALETTE_COLORS
	        && (tok = tokenizer.next()) != ""; i++) {
		sscanf(tok, "%d %d %d", &red, &green, &blue);
		color = RGB(red, green, blue);
		m_pPalette[i].rgbtRed = (BYTE)red;
		m_pPalette[i].rgbtGreen = (BYTE)green;
		m_pPalette[i].rgbtBlue = (BYTE)blue;
		m_ColorMap[color] = i;
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);
}

/////////////////////////////////////////////////////////////////////////////
RGBTRIPLE Palette256::operator[] (uint8_t index) const
{
	return m_pPalette[index];
}

/////////////////////////////////////////////////////////////////////////////
BOOL Palette256::GetIndex(COLORREF c, uint8_t &index) const
{
	if (!m_ColorMap.Lookup(c, index))
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
Palette256 *Palette256::instance()
{
	if (This.get() == NULL) {
		This = Palette256Ptr(new Palette256());
	}

	return This.get();
}

/////////////////////////////////////////////////////////////////////////////
BOOL Palette256::CreatePalette(CPalette &pal)
{
	pal.DeleteObject();

	LPLOGPALETTE pPal = (LPLOGPALETTE)GlobalAlloc(GPTR, sizeof(LOGPALETTE)
	                    + (sizeof(PALETTEENTRY) * 256));

	pPal->palVersion = 0x300;
	pPal->palNumEntries = 256;

	for (uint32_t i = 0; i < 256; i++) {
		pPal->palPalEntry[i].peRed = m_pPalette[i].rgbtRed;
		pPal->palPalEntry[i].peGreen = m_pPalette[i].rgbtGreen;
		pPal->palPalEntry[i].peBlue = m_pPalette[i].rgbtBlue;
	}

	if (!pal.CreatePalette(pPal))
		return FALSE;

	GlobalFree(pPal);

	return TRUE;
}
