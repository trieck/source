/////////////////////////////////////////////////////////////////////////////
//
//	LOGFILE.H : Text file log
//
// Copyright(c) 2008 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LOGFILE_H__
#define __LOGFILE_H__

/////////////////////////////////////////////////////////////////////////////
class LogFile {
// Construction / Destruction
public:
	LogFile();
	~LogFile();

// Interface
	bool open(LPCTSTR filename);
	bool log(LPCTSTR fmt, ...);
	void close();

private:
	HANDLE hFile;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __LOGFILE_H__