#ifndef __isoimage__
#define __isoimage__

class isoimage : public wxObject {
public:
	isoimage();
	~isoimage();

	bool OpenImage(const wxString &filename);
	bool ReadDir(const wxString &path, stat_vector_t &stat_vector);
		
	wxString GetVolumeId();

private:
	ISO9660::IFS m_image;
};

#endif // __isoimage__
