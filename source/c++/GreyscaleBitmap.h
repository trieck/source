#pragma once

#include <atlimage.h>

// GreyscaleBitmap

class GreyscaleBitmap : public CImage
{
public:
	GreyscaleBitmap();
	virtual ~GreyscaleBitmap();

	virtual BOOL LoadBitmap(LPCTSTR szFilename);	

private:
	BOOL Monochrome();
};


