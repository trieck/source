/////////////////////////////////////////////////////////////////////////////
//
//	UTIL.CPP : utility functions
//
//	Copyright(c) 2001 KnowX.com, All Rights Reserved
//

#include "stdafx.h"
#include "util.h"
#include "exception.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

/////////////////////////////////////////////////////////////////////////////
string tempname()
{
	char path[MAX_PATH] = { 0 };
	char filename[MAX_PATH] = { 0 };

	GetTempPath(MAX_PATH, path);
	GetTempFileName(path, "", 0, filename);

	return filename;
}

/////////////////////////////////////////////////////////////////////////////
stringvec expand(const char* arg)
{
	stringvec doclist;
	string dir = dirname(arg);

	struct _finddata_t file;
	long h = _findfirst(arg, &file);

	if (h == -1)
		return doclist;

	do {
		if (file.attrib & _A_SUBDIR)
			continue;

		doclist.push_back(lower(dir + file.name));
	} while (_findnext(h, &file) == 0);

	_findclose(h);

	return doclist;
}

/////////////////////////////////////////////////////////////////////////////
stringvec rexpand(const char* arg)
{
	char patt[MAX_PATH + _MAX_FNAME + 1];

	stringvec doclist, tmplist;
	string dir = dirname(arg);
	string pattern = arg;

	string::size_type N = pattern.find_last_of('\\');
	if (N != string::npos)
		pattern = pattern.substr(++N);

	struct _finddata_t file;
	long h = _findfirst(arg, &file);

	if (h == -1) { // no pattern match try subdirectories
		sprintf(patt, "%s*", dir.c_str());
		h = _findfirst(patt, &file);
		if (h == -1)
			return doclist;

		do {
			if (strcmp(file.name, ".") == 0)
				continue;
			if (strcmp(file.name, "..") == 0)
				continue;

			if (file.attrib & _A_SUBDIR) {
				sprintf(patt, "%s%s\\%s", dir.c_str(), file.name,
				        pattern.c_str());
				tmplist = rexpand(patt);
				doclist.insert(doclist.end(), tmplist.begin(),
				               tmplist.end());
			}

		} while (_findnext(h, &file) == 0);

		_findclose(h);

		return doclist;
	}

	do {
		if (strcmp(file.name, ".") == 0)
			continue;
		if (strcmp(file.name, "..") == 0)
			continue;

		if (file.attrib & _A_SUBDIR) {
			sprintf(patt, "%s%s\\%s", dir.c_str(), file.name,
			        pattern.c_str());
			tmplist = rexpand(patt);
			doclist.insert(doclist.end(), tmplist.begin(),
			               tmplist.end());
			continue;
		}

		doclist.push_back(lower(dir + file.name));

	} while (_findnext(h, &file) == 0);

	_findclose(h);

	return doclist;
}

/////////////////////////////////////////////////////////////////////////////
string dirname(const char* path)
{
	char drive[_MAX_DRIVE] = { 0 };
	char dir[_MAX_PATH] = { 0 };

	_splitpath(path, drive, dir, NULL, NULL);

	return string(drive) + dir;
}

/////////////////////////////////////////////////////////////////////////////
string fullpath(const char *path)
{
	char buffer[_MAX_PATH + _MAX_FNAME + 1];
	buffer[0] = '\0';

	_fullpath(buffer, path, _MAX_PATH + _MAX_FNAME);

	return buffer;
}

/////////////////////////////////////////////////////////////////////////////
string filename(const char* path)
{
	char filename[_MAX_FNAME] = { 0 };
	char ext[_MAX_EXT] = { 0 };
	char output[_MAX_FNAME + _MAX_EXT + 1];

	_splitpath(path, NULL, NULL, filename, ext);

	sprintf(output, "%s%s", filename, ext);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string basename(const char* path)
{
	char drive[_MAX_DRIVE] = { 0 };
	char dir[_MAX_PATH] = { 0 };
	char file[_MAX_FNAME] = { 0 };
	char output[_MAX_DRIVE + _MAX_PATH + _MAX_FNAME + 1];

	string name = filename(path);

	_splitpath(name.c_str(), drive, dir, file, NULL);

	sprintf(output, "%s%s%s", drive, dir, file);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string extname(const char* path)
{
	char ext[_MAX_EXT] = { 0 };

	_splitpath(path, NULL, NULL, NULL, ext);

	return ext;
}

/////////////////////////////////////////////////////////////////////////////
string layout(const char *path)
{
	string dir = programdir() + "layouts\\";
	string n = basename(path);

	unsigned i;
	for (i = 0; i < n.size(); i++)
		if (ispunct(n[i]))
			break;

	if (i == n.length())
		throw Exception("path name %s must start with a state abbreviation.",
		                path);

	n = n.substr(i + 1);
	string filename = dir + n + ".txt";

	return filename;
}

/////////////////////////////////////////////////////////////////////////////
string modulename()
{
	char path[_MAX_PATH + _MAX_FNAME + 1] = { 0 };

	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(programdir, &mbi, sizeof(mbi));

	GetModuleFileName((HINSTANCE)mbi.AllocationBase,
	                  path, _MAX_PATH + _MAX_FNAME);

	return path;
}

/////////////////////////////////////////////////////////////////////////////
string modulebasename()
{
	return basename(modulename().c_str());
}

/////////////////////////////////////////////////////////////////////////////
string programdir()
{
	return lower(dirname(modulename().c_str()));
}

/////////////////////////////////////////////////////////////////////////////
string itoa(int n)
{
	static const int len = 20;
	char buffer[len] = { 0 };

	_itoa(n, buffer, 10);

	return buffer;
}

/////////////////////////////////////////////////////////////////////////////
string trim(const char *str)
{
	return trim_left(trim_right(str).c_str());
}

/////////////////////////////////////////////////////////////////////////////
string trim_left(const char *str)
{
	size_t len, idx;

	len = strlen(str);

	for (idx = 0; idx < len; idx++) {
		if (!isspace(str[idx]))
			break;
	}

	return &str[idx];
}

/////////////////////////////////////////////////////////////////////////////
string trim_right(const char *str)
{
	size_t idx = strlen(str);

	if (idx == 0)
		return "";

	for (idx--; isspace(str[idx]); idx--)
		;

	return string(str, idx + 1);
}

/////////////////////////////////////////////////////////////////////////////
string comma(INT64 i)
{
	string output;

	char buff[MAX_PATH];
	sprintf(buff,"%I64u", i);

	int n = strlen(buff);

	for (int j = n - 1, k = 1; j >= 0; j--, k++) {
		output += buff[j];
		if (k % 3 == 0 && j > 0 && j < n - 1)
			output += ',';
	}

	std::reverse(output.begin(), output.end());

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string lower(const string & input)
{
	string output;

	size_t N = input.length();
	output.resize(N);

	unsigned i;
	for (i = 0; i < N; i++)
		output[i] = tolower(input[i]);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string upper(const string & input)
{
	string output;

	size_t N = input.length();
	output.resize(N);

	unsigned i;
	for (i = 0; i < N; i++)
		output[i] = toupper(input[i]);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string lasterror()
{
	string output;

	char *pmsg = NULL;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
	              NULL, GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	              (LPTSTR)&pmsg, 0, NULL);

	if (pmsg != NULL) {
		int N = strlen(pmsg);
		if (N > 1 && pmsg[N - 1] == '\n')
			pmsg[N - 1] = '\0';

		if (N > 1 && pmsg[N - 2] == '\r')
			pmsg[N - 2] = '\0';

		output = pmsg;

		LocalFree(pmsg);
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string fileload(const string &file)
{
	// read in a file into a string using the "big gulp" method
	int fd = open(file.c_str(), _O_RDONLY | _O_BINARY | _O_SEQUENTIAL);

	if (fd == -1)
		return "";

	struct stat status;
	fstat(fd, &status);

	char* pbuf = new char[status.st_size + 1];

	int nread = read(fd, pbuf, status.st_size);

	pbuf[nread] = '\0';

	string output = pbuf;
	delete [] pbuf;

	close(fd);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string xmlescape(const string &input)
{
	string output;

	const char *pin = input.c_str();

	while (*pin) {
		if (*pin == '"') {
			output += "&quot;";
			pin++;
		} else if (*pin == '<') {
			output += "&lt;";
			pin++;
		} else if (*pin == '>') {
			output += "&gt;";
			pin++;
		} else if (*pin == '&') {
			output += "&amp;";
			pin++;
		} else {
			output += *pin++;
		}
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string machinename()
{
	DWORD len = MAX_COMPUTERNAME_LENGTH;
	char cname[MAX_COMPUTERNAME_LENGTH + 1];

	GetComputerName(cname, &len);

	return cname;
}

/////////////////////////////////////////////////////////////////////////////
string format(const char *fmt, ...)
{
	va_list arglist;
	va_start(arglist, fmt);

	char buf[8000];
	vsprintf(buf, fmt, arglist);

	va_end (arglist);

	return buf;
}

/////////////////////////////////////////////////////////////////////////////
string uni2ansi(const wchar_t *pwstr)
{
	size_t N = wcslen(pwstr);

	char *pstr = new char[N + 1];

	int result = ::WideCharToMultiByte(CP_ACP, 0, pwstr, -1, pstr,
	                                   N + 1, NULL, NULL);
	if (result == 0) {
		delete [] pstr;
		return "";
	}

	string output = pstr;
	delete [] pstr;

	return output;
}