#include "isoimage.h"

isoimage::isoimage()
{
}

isoimage::~isoimage()
{
}

bool isoimage::OpenImage(const wxString &filename)
{
	const wxCharBuffer buffer = filename.ToAscii();
	const char *path = buffer.data();

	return m_image.open(path);
}
