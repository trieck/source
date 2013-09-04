/////////////////////////////////////////////////////////////////////////////
//
// FILE.CPP : Win32 file class abstraction
//

#include "common.h"
#include <io.h>
#include "file.h"

static LPCTSTR prefixString = _T("");
static const UINT uniqueID = 0UL;

const _int64 File::seekFailure = -1;

File::File(LPCTSTR name, File::openMode M)
	: hFile(NULL),
	  filename(name),
	  mode(M)
{
	open();
}

File::File(HANDLE hfile)
	: hFile(hfile),
	  filename(_T("")),
	  mode(unknown)
{
}

File::~File()
{
	close();
}

bool File::open()
{
	close();

	DWORD access = 0UL;
	DWORD createdisp = 0UL;
	DWORD flags = 0UL;

	if (mode == readOnly) {
		access |= GENERIC_READ;
		createdisp |= OPEN_EXISTING;
	} else if (mode == readWrite) {
		access |= GENERIC_READ | GENERIC_WRITE;
		createdisp |= OPEN_EXISTING;
	} else if (mode == create) {
		access |= GENERIC_WRITE;
		createdisp |= CREATE_NEW;
	}

	HANDLE H = CreateFile(filename.c_str(),
	                      access,		/* access mode */
	                      0,			/* no sharing */
	                      NULL,		/* no security */
	                      createdisp,	/* creation disposition */
	                      flags,		/* flags and attributes */
	                      NULL);		/* template file */

	if (H == INVALID_HANDLE_VALUE)
		return false;

	return (0 != (hFile = H));
}

void File::close()
{
	if (0 != hFile) {
		CloseHandle(*this);
		hFile = NULL;
	}
}

DWORD File::read(LPVOID pbuff, DWORD size)
{
	DWORD read;

	if (!ReadFile(*this, pbuff, size, &read, NULL))
		return 0;

	return read;
}

bool File::readLine(LPTSTR line, DWORD maxsize)
{
	if (0 == hFile)
		return false;	// not open

	TCHAR *pline = line;
	DWORD read = 0UL;

	for (DWORD i = 0; i < maxsize; i++) {
		if (!ReadFile(*this, pline, 1, &read, NULL))
			return false;

		if (read == 0) {
			if (pline > line)
				break;
			else return false;
		}

		if (*pline++ == _T('\n')) {
			if (pline[-2] == _T('\r'))
				pline[-2] = _T('\0');	// provisions for \r\n
			else pline[-1] = _T('\0');
			break;
		}
	}

	pline[0] = _T('\0');

	return true;
}

tstring File::gulp()
{
	if (0 == hFile)
		return false;	// not open

	seek(0, File::begin);

	TCHAR *pbuff = new TCHAR[(unsigned)size() + 1];
	if (0 == pbuff)
		return _T("");

	if (!read(pbuff, (unsigned)size()))
		return _T("");

	pbuff[size()] = _T('\0');

	tstring x = pbuff;

	delete [] pbuff;

	return x;
}

DWORD File::write(LPCTSTR str)
{
	if (0 == hFile)
		return 0UL;	// not open

	DWORD written = 0UL;
	DWORD len = _tcslen(str);

	for (DWORD j = 0, x = 0; j < len; j += x) {
		x = min(len - j, blocksize);

		WriteFile(*this,
		          str + j,
		          x,
		          &x,
		          NULL);

		if (0 == x)
			break;

		written += x;
	}

	return written;
}

_int64 File::size() const
{
	LARGE_INTEGER li;

	li.LowPart = GetFileSize(*this, (LPDWORD)&li.HighPart);

	return li.QuadPart;
}

File::Type File::getType() const
{
	if (0 == hFile)
		return unknownType; // not open

	DWORD type = GetFileType(*this);

	switch (type) {
	case FILE_TYPE_DISK:
		return diskType;
	case FILE_TYPE_CHAR:
		return charType;
	case FILE_TYPE_PIPE:
		return pipeType;
	case FILE_TYPE_UNKNOWN:
	default:
		return unknownType;
	}

	return unknownType;	// not reachable
}

bool File::remove(LPCTSTR filename)
{
	if (!DeleteFile(filename))
		return false;

	return true;
}

tstring File::getTempFileName()
{
	TCHAR path[MAX_PATH];
	if (0 == GetTempPath(MAX_PATH, path))
		return _T("");

	TCHAR file[MAX_PATH + _MAX_FNAME];
	if (0 == GetTempFileName(path, prefixString, uniqueID, file))
		return _T("");

	return file;
}

File::FilePtr File::getConsole(File::Console c)
{
	return FilePtr(new File((HANDLE)_get_osfhandle(c)));
}

_int64 File::seek(_int64 pos, File::moveMethod m)
{
	if (0 == hFile)
		return 0;	// not open

	LARGE_INTEGER li;

	DWORD method;
	if (m == begin)
		method = FILE_BEGIN;
	else if (m == current)
		method = FILE_CURRENT;
	else if (m == end)
		method = FILE_END;

	li.QuadPart = pos;

	LPLONG phigh = li.HighPart == 0 ? NULL : &li.HighPart;

	li.LowPart = SetFilePointer(*this,
	                            li.LowPart,
	                            phigh,
	                            method);

	if (li.LowPart == INVALID_FILE_SIZE) {
		if (phigh == NULL)
			return seekFailure;	// error
		else if (GetLastError() != NO_ERROR)
			return seekFailure;	// error
	}

	return li.QuadPart;
}


