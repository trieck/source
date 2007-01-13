// TorrentSettings.h: interface for the TorrentSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTSETTINGS_H__5E28CFB3_FC4D_4A03_97A1_8C55B9B83C2F__INCLUDED_)
#define AFX_TORRENTSETTINGS_H__5E28CFB3_FC4D_4A03_97A1_8C55B9B83C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dictionary.h"

class TorrentSettings  
{
public:
	TorrentSettings();
	virtual ~TorrentSettings();

	void Flush();

	LPTORRENTOBJECT GetValue(LPCSTR key) const;
	void SetValue(LPCSTR key, LPTORRENTOBJECT v);

private:
	void ReadSettings();
	void Delete();

	CWinApp *m_pApp;
	LPDICTIONARY m_pDict;
};

#endif // !defined(AFX_TORRENTSETTINGS_H__5E28CFB3_FC4D_4A03_97A1_8C55B9B83C2F__INCLUDED_)
