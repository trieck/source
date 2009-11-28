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

bool isoimage::ReadDir(const wxString &path, stat_vector_t& stat_vector)
{
	const wxCharBuffer buffer = path.ToAscii();
	const char *spath = buffer.data();

	return m_image.readdir(spath, stat_vector);
}

wxString isoimage::GetVolumeId()
{
	char *id;

	if (!m_image.get_volume_id(id)) {
		return _T("");
	}

	return wxString::FromAscii(id);
}
