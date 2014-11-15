#ifndef __isoimage__
#define __isoimage__

class isoimage : public wxObject {
public:
    isoimage();
    ~isoimage();

    bool OpenImage(const wxString &filename);
    bool ReadDir(const wxString &path, stat_vector_t &stat_vector);
    uint32_t SeekRead(void *ptr, lsn_t start, uint32_t size=1);
    ISO9660::PVD *ReadPVD();

    wxString GetVolumeId();

private:
    ISO9660::IFS m_image;
};

#endif // __isoimage__
