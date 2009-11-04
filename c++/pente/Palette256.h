#pragma once

typedef CMap<COLORREF, COLORREF, uint8_t, uint8_t> ColorMap;

/////////////////////////////////////////////////////////////////////////////
class Palette256
{
private:
	Palette256();
public:
	~Palette256();

	BOOL GetIndex(COLORREF c, uint8_t &index) const;
	RGBTRIPLE operator[] (uint8_t index) const;

	typedef std::auto_ptr<Palette256> Palette256Ptr;
	static Palette256 *instance();

private:
	void load();

	enum { NUM_PALETTE_COLORS = 256 };

	RGBTRIPLE *m_pPalette;
	ColorMap m_ColorMap;

	static Palette256Ptr This;
};
