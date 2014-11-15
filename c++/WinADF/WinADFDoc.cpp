// WinADFDoc.cpp : implementation of the WinADFDoc class
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "DiskPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WinADFDoc

IMPLEMENT_DYNCREATE(WinADFDoc, CDocument)

BEGIN_MESSAGE_MAP(WinADFDoc, CDocument)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &WinADFDoc::OnUpdateFileSave)
    ON_UPDATE_COMMAND_UI(ID_FILE_DISKINFORMATION, &WinADFDoc::OnUpdateDiskInfo)
    ON_COMMAND(ID_FILE_DISKINFORMATION, &WinADFDoc::OnDiskInfo)
END_MESSAGE_MAP()


// WinADFDoc construction/destruction

WinADFDoc::WinADFDoc() : m_pVolume(NULL), m_pEntry(NULL)
{
}

WinADFDoc::~WinADFDoc()
{
}

BOOL WinADFDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}


BOOL WinADFDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
#ifdef _DEBUG
    if (IsModified())
        TRACE(traceAppMsg, 0, "Warning: OnOpenDocument replaces an unsaved document.\n");
#endif
    ENSURE(lpszPathName);

    DeleteContents();

    try {
        CWaitCursor wait;
        m_pDisk = Disk::open(lpszPathName, false);
        m_pVolume = m_pDisk->mount();
    } catch (const ADFException &e) {
        DeleteContents();   // remove failed contents
        AfxMessageBox(e.getDescription().c_str());
        AfxThrowUserException();
        return FALSE;
    }

    SetModifiedFlag(FALSE);     // start off with unmodified

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void WinADFDoc::DeleteContents()
{
    m_pVolume = NULL;

    if (m_pEntry != NULL) {
        delete m_pEntry;
        m_pEntry = NULL;
    }

    if (m_pDisk.get() != NULL) {
        Disk *pDisk = m_pDisk.release();
        delete pDisk;
    }
}

/////////////////////////////////////////////////////////////////////////////
EntryList WinADFDoc::readdir()
{
    if (m_pVolume == NULL)
        return EntryList();

    EntryList entries = m_pVolume->readdir(m_pVolume->getCurrentDir(),
                                           false);

    return entries;
}

// WinADFDoc diagnostics

#ifdef _DEBUG
void WinADFDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void WinADFDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// WinADFDoc commands

void WinADFDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_bModified);
}

void WinADFDoc::chdir(Entry *pEntry)
{
    if (m_pVolume != NULL) {
        if (pEntry == NULL) {
            m_pVolume->setCurrentDir(m_pVolume->getRootBlock());
        } else {
            m_pVolume->changedir(pEntry);
        }
    }
}


void WinADFDoc::SetEntry(const Entry &e)
{
    if (m_pEntry != NULL)
        delete m_pEntry;

    m_pEntry = new Entry(e);
}

const Entry *WinADFDoc::GetEntry() const
{
    return m_pEntry;
}

Disk *WinADFDoc::GetDisk() const
{
    return m_pDisk.get();
}

Volume *WinADFDoc::GetVolume() const
{
    return m_pVolume;
}

void WinADFDoc::OnUpdateDiskInfo(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_pDisk.get() != NULL);
}

void WinADFDoc::OnDiskInfo()
{
    DiskPropSheet sheet(theApp.GetMainWnd());
    sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
    INT_PTR result = sheet.DoModal();
}
