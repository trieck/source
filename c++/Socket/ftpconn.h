/////////////////////////////////////////////////////////////////////////////
//
// FTPCONN.H : FTP connection class
//
// Copyright (c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __FTPCONN_H__
#define __FTPCONN_H__

/////////////////////////////////////////////////////////////////////////////
class FTPConnection {
public:
// Construction / Destruction
	FTPConnection();
	FTPConnection(const char *path);
	virtual ~FTPConnection();

// Interface
public:
	bool connect(LPCSTR host, LPCSTR uid, LPCSTR pwd);
	bool ChangeDirectory(LPCSTR dir);
	void close();
	HINTERNET GetConn() const {
		return hConn;
	}

	class File {
	public:
		File(HINTERNET file) : hFile(file) {
			memset(&data, 0, sizeof(WIN32_FIND_DATA));
		}

		File(WIN32_FIND_DATA *pdata) : hFile(NULL) {
			memcpy(&data, pdata, sizeof(WIN32_FIND_DATA));
		}
		~File() {
			close();
		}
		bool Open(const FTPConnection &conn,
		          DWORD access = GENERIC_READ,
		          DWORD flags = FTP_TRANSFER_TYPE_UNKNOWN);

		DWORD Read(char *buf, unsigned size);
		string ReadLine();

		void close() {
			if (hFile)
				InternetCloseHandle(hFile);
		}
		WIN32_FIND_DATA data;
	private:
		HINTERNET hFile;
	};

	typedef std::auto_ptr<File> FilePtr;
	FilePtr GetFile(LPCSTR path);
	bool PutFile(LPCSTR local, LPCSTR remote);

	class FileIterator {
	private:
		FileIterator(const FTPConnection &conn, LPCSTR patt);
	public:
		~FileIterator();
		FilePtr next();
	private:
		HINTERNET hFind;
		const FTPConnection &conn;
		LPCSTR patt;
		friend class FTPConnection;
	};

	typedef std::auto_ptr<FileIterator> FileIteratorPtr;
	FileIteratorPtr GetIterator(LPCSTR patt);

private:
	HINTERNET hInternet, hConn;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __FTPCONN_H__