// TorrentSettings.cpp: implementation of the TorrentSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentSettings.h"
#include "torrentexplorer.h"
#include "TorrentParser.h"
#include "TorrentWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
TorrentSettings::TorrentSettings()
	: m_pDict(NULL)
{
	m_pApp = AfxGetApp();
	ReadSettings();
}

//////////////////////////////////////////////////////////////////////
TorrentSettings::~TorrentSettings()
{
	Delete();
}

//////////////////////////////////////////////////////////////////////
void TorrentSettings::Flush()
{
	if (m_pDict == NULL) return;

	CMemFile file;
	CArchive ar(&file, CArchive::store);

	try {
		TorrentWriter::Write(m_pDict, ar);
		file.SeekToBegin();

		DWORD length = file.GetLength();

		CString buf;
		LPSTR pbuf = buf.GetBufferSetLength(length);

		file.Read(pbuf, length);

		m_pApp->WriteProfileBinary("Settings", "Settings",
		                           (LPBYTE)pbuf, length);
	} catch (CException *pException) {
		pException->ReportError();
		pException->Delete();
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentSettings::Delete()
{
	if (m_pDict != NULL) {
		Flush();
		delete m_pDict;
		m_pDict = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentSettings::ReadSettings()
{
	LPBYTE data;
	UINT size;
	if (!m_pApp->GetProfileBinary("Settings", "Settings", &data,
	                              &size)) {
		m_pDict = new Dictionary();
	} else {
		CMemFile file(data, size);
		CArchive ar(&file, CArchive::load);
		try {
			m_pDict = TorrentParser::Parse(ar);
		} catch (CException *pException) {
			pException->ReportError();
			pException->Delete();
		}
		delete []data;
	}
}

//////////////////////////////////////////////////////////////////////
LPTORRENTOBJECT TorrentSettings::GetValue(LPCSTR key) const
{
	if (m_pDict == NULL) return NULL;
	return m_pDict->Get(key);
}

//////////////////////////////////////////////////////////////////////
void TorrentSettings::SetValue(LPCSTR key, LPTORRENTOBJECT v)
{
	if (m_pDict != NULL)
		m_pDict->Set(key, v);
}