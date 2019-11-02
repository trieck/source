#pragma once



// DiskPropSheet

class DiskPropSheet : public CPropertySheet
{
    DECLARE_DYNAMIC(DiskPropSheet)

public:
    DiskPropSheet(CWnd* pParentWnd = NULL);
    virtual ~DiskPropSheet();

protected:
    virtual void BuildPropPageArray();

    CPropertyPage **m_pPages;
    uint32_t m_nPages;

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};


