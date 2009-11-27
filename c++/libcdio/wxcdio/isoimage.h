#ifndef __isoimage__
#define __isoimage__

#include <wx/wx.h>
#include <cdio++/iso9660.hpp>

class isoimage : public wxObject
{
public:
	isoimage();
	~isoimage();

	bool OpenImage(const wxString &filename);
	
private:
	ISO9660::IFS m_image;	
};

#endif // __isoimage__
