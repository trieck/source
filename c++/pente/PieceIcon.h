#pragma once


// PieceIcon

class PieceIcon : public CObject
{
public:
	PieceIcon();
	virtual ~PieceIcon();	

	operator HICON() const { return hIcon; }
	COLORREF getColor() const { return color; }
	void setColor(COLORREF c);

private:
	enum { DEFAULT_COLOR = 0x8000 };

	void load(void);
	void recreateIcon();
	void createBitmap(HBITMAP hBitmap, CBitmap &bitmap);
	CBitmap bmMask, bmColor;
	HICON hIcon;
	COLORREF color;
};


