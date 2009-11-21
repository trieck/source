/////////////////////////////////////////////////////////////////////////////
//
// FTPCONN.CPP : FTP connection class
//
// Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include <wininet.h>
#include "ftpconn.h"

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FTPConnection()
		: hInternet(NULL), hConn(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::~FTPConnection()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
bool FTPConnection::connect(LPCSTR host, LPCSTR uid, LPCSTR pwd)
{
	close();

	hInternet = InternetOpen(
	                NULL,
	                INTERNET_OPEN_TYPE_DIRECT,
	                NULL,
	                NULL,
	                0);
	if (hInternet == NULL)
		return false;

	hConn = InternetConnect(
	            hInternet,
	            host,
	            INTERNET_DEFAULT_FTP_PORT,
	            uid,
	            pwd,
	            INTERNET_SERVICE_FTP,
	            0,
	            NULL);

	return hConn != NULL;
}

/////////////////////////////////////////////////////////////////////////////
bool FTPConnection::ChangeDirectory(LPCSTR dir)
{
	if (!FtpSetCurrentDirectory(hConn, dir))
		return false;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
void FTPConnection::close()
{
	if (hConn)
		InternetCloseHandle(hConn);

	if (hInternet)
		InternetCloseHandle(hInternet);

	hConn = hInternet = NULL;
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FilePtr FTPConnection::GetFile(LPCSTR path)
{
	HINTERNET hFile = FtpOpenFile(
	                      hConn,
	                      path,
	                      GENERIC_READ,
	                      FTP_TRANSFER_TYPE_UNKNOWN,
	                      NULL);
	if (hFile != NULL) {
		return FTPConnection::FilePtr(new FTPConnection::File(hFile));
	}

	return FTPConnection::FilePtr(0);
}

/////////////////////////////////////////////////////////////////////////////
bool FTPConnection::PutFile(LPCSTR local, LPCSTR remote)
{
	BOOL ret = FtpPutFile(hConn, local,
	                      remote,
	                      FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_TRANSFER_BINARY,
	                      0);

	return ret == TRUE;
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FileIteratorPtr FTPConnection::GetIterator(LPCSTR patt)
{
	FTPConnection::FileIterator *iterator =
	    new FTPConnection::FileIterator(*this, patt);

	return FTPConnection::FileIteratorPtr(iterator);
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FileIterator::FileIterator(const FTPConnection &rhs, LPCSTR ppatt)
		: conn(rhs), patt(ppatt), hFind(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FileIterator::~FileIterator()
{
	if (hFind)
		InternetCloseHandle(hFind);
}

/////////////////////////////////////////////////////////////////////////////
FTPConnection::FilePtr FTPConnection::FileIterator::next()
{
	WIN32_FIND_DATA data;

	if (hFind == NULL) {
		hFind = FtpFindFirstFile(
		            conn.GetConn(),
		            patt,
		            &data,
		            0,
		            NULL);
		return FTPConnection::FilePtr(new FTPConnection::File(&data));
	} else if (InternetFindNextFile(hFind, &data)) {
		return FTPConnection::FilePtr(new FTPConnection::File(&data));
	} else {
		return FTPConnection::FilePtr(0);
	}
}

/////////////////////////////////////////////////////////////////////////////
bool FTPConnection::File::Open(const FTPConnection &conn, DWORD access,
                               DWORD flags)
{
	close();

	hFile = FtpOpenFile(
	            conn.GetConn(),
	            data.cFileName,
	            access,
	            flags,
	            NULL);

	return hFile != NULL;
}

/////////////////////////////////////////////////////////////////////////////
DWORD FTPConnection::File::Read(char *buf, unsigned size)
{
	DWORD read = 0;

	InternetReadFile(hFile, buf, size, &read);

	return read;
}

/////////////////////////////////////////////////////////////////////////////
string FTPConnection::File::ReadLine()
{
	string output;

	char buf[MAX_PATH + 1], *pbuf = buf;

	for (;;) {
		if (!Read(pbuf++, 1))
			break;

		if (pbuf - buf == MAX_PATH) {
			pbuf[0] = '\0';
			output += buf;
			pbuf = buf;
		}

		if (pbuf[-1] == '\n') {
			pbuf[-1] = '\0';
			break;
		}
	}

	return output;
}
