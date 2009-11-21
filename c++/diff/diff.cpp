/////////////////////////////////////////////////////////////////////////////
//
//	DIFF.CPP
//

#pragma warning(disable:4786)

#include <iostream>
#include <strstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <tchar.h>
#include <windows.h>
#include <io.h>

#define BEGIN_ANONYMOUS	namespace {
#define END_ANONYMOUS }

typedef std::basic_string<TCHAR> tstring;
typedef std::vector<tstring> stringvec;

BEGIN_ANONYMOUS

LPCTSTR usage = _T("usage: diff files1 files2");
bool isspec(LPCTSTR);
tstring dirname(LPCTSTR files);
tstring specname(LPCTSTR files);
void diff(LPCTSTR spec1, LPCTSTR spec2);
void compare(LPCTSTR spec1, LPCTSTR spec2);
stringvec expand(LPCTSTR dir);
stringvec subdirs(LPCTSTR dir);
void compareFiles(LPCTSTR file1, LPCTSTR file2);

END_ANONYMOUS

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
	if (argc < 3) {
		std::cerr << usage << std::endl;
		return 1;
	}

	argc--;
	argv++;

	if (!isspec(argv[0]) || !isspec(argv[1])) {
		std::cerr << usage << std::endl;
		return 1;
	}

	diff(argv[0], argv[1]);

	return 0;
}

BEGIN_ANONYMOUS

/////////////////////////////////////////////////////////////////////////////
bool isspec(LPCTSTR pdir)
{
	WIN32_FIND_DATA data;

	HANDLE hFinder = ::FindFirstFile(pdir, &data);
	if (hFinder == INVALID_HANDLE_VALUE)
		return false;	// not found

	::FindClose(hFinder);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
tstring dirname(LPCTSTR files)
{
	size_t len = _tcslen(files);

	for (int i = len - 1; i >= 0; i--)
		if (files[i] == _T('\\'))
			return tstring(files, i);

	return _T("");
}

/////////////////////////////////////////////////////////////////////////////
tstring specname(LPCTSTR files)
{
	size_t len = _tcslen(files);

	for (int i = len - 1; i >= 0; i--)
		if (files[i] == _T('\\'))
			return tstring(files + i + 1);

	return _T("");
}

/////////////////////////////////////////////////////////////////////////////
void diff(LPCTSTR files1, LPCTSTR files2)
{
	// don't compare identical specs
	if (_tcscmp(files1, files2) == 0)
		return;

	tstring dir1 = dirname(files1);
	tstring dir2 = dirname(files2);

	tstring spec1 = specname(files1);
	tstring spec2 = specname(files2);

	std::cout << std::endl << _T('[') << dir1.c_str() << _T(']') << _T('\t')
	          << _T('[') << dir2.c_str() << _T(']') << std::endl;

	compare(files1, files2);

	stringvec subdirs1, subdirs2;

	subdirs1 = subdirs(dir1.c_str());
	subdirs2 = subdirs(dir2.c_str());

	// compare against first specification
	stringvec::const_iterator it = subdirs1.begin();

	for ( ; it != subdirs1.end(); it++) {
		stringvec::const_iterator I = std::find(subdirs2.begin(), subdirs2.end(), *it);
		if (I == subdirs2.end()) {
			std::cout << _T('[') << *it << _T(']') << _T('\t')
			          << _T("not found") << std::endl;
			continue;
		}

		std::ostrstream path1, path2;
		path1 << dir1 << _T('\\') << *it
		<< _T('\\') << spec1 << std::ends;
		path2 << dir2 << _T('\\') << *it
		<< _T('\\') << spec1 << std::ends;
		diff(path1.str(), path2.str());
	}

	// compare against second specification
	for (it = subdirs2.begin(); it != subdirs2.end(); it++) {
		stringvec::const_iterator I = std::find(subdirs1.begin(), subdirs1.end(), *it);
		if (I == subdirs1.end()) {
			std::cout << _T("not found") << _T('\t') << _T('[') << *it << _T(']')
			          << std::endl;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
stringvec subdirs(LPCTSTR dir)
{
	stringvec output;
	WIN32_FIND_DATA data;
	tstring dirname(dir);

	if (dirname[dirname.length() - 1] != _T('\\'))
		dirname += _T('\\');
	dirname += _T('*');

	HANDLE hFinder = ::FindFirstFile(dirname.c_str(), &data);
	if (hFinder == INVALID_HANDLE_VALUE)
		return output;

	while (::FindNextFile(hFinder, &data)) {
		if (_tcscmp(data.cFileName, _T(".")) == 0)
			continue;

		if (_tcscmp(data.cFileName, _T("..")) == 0)
			continue;

		if (data.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY)
			output.push_back(data.cFileName);
	}

	::FindClose(hFinder);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
void compare(LPCTSTR files1, LPCTSTR files2)
{
	stringvec v1 = expand(files1);
	stringvec v2 = expand(files2);

	stringvec::const_iterator it = v1.begin();

	// compare against first spec
	for ( ; it != v1.end(); it++) {
		std::cout << (*it).c_str() << _T('\t');

		stringvec::const_iterator I = std::find(v2.begin(), v2.end(), *it);
		if (I == v2.end()) {
			std::cout << _T("not found");
		} else {
			std::cout << (*it).c_str();
			tstring path1 = dirname(files1) + _T('\\') + *it;
			tstring path2 = dirname(files2) + _T('\\') + *it;
			std::cout << _T('\t');
			compareFiles(path1.c_str(), path2.c_str());
		}

		std::cout << std::endl;
	}

	// compare against second spec
	for (it = v2.begin(); it != v2.end(); it++) {
		stringvec::const_iterator I = std::find(v1.begin(), v1.end(), *it);
		if (I == v1.end()) {
			std::cout << _T("not found");
			std::cout << _T('\t') << (*it).c_str() << std::endl;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
stringvec expand(LPCTSTR dir)
{
	stringvec output;
	WIN32_FIND_DATA data;

	HANDLE hFinder = ::FindFirstFile(dir, &data);
	if (hFinder == INVALID_HANDLE_VALUE)
		return output;

	while (::FindNextFile(hFinder, &data)) {
		if (data.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY)
			continue;
		if (data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
			output.push_back(data.cFileName);
		if (data.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
			output.push_back(data.cFileName);
	}

	::FindClose(hFinder);

	return output;
}

/////////////////////////////////////////////////////////////////////////////
void compareFiles(LPCTSTR file1, LPCTSTR file2)
{
	FILE *fp1, *fp2;

	fp1 = fopen(file1, _T("rb"));
	if (fp1 == NULL)
		return;

	fp2 = fopen(file2, _T("rb"));
	if (fp2 == NULL) {
		fclose(fp1);
		return;
	}

	int len = _filelength(_fileno(fp1));

	int offset = 0, c1, c2;
	while ((c1 = fgetc(fp1)) != EOF) {
		c2 = fgetc(fp2);
		if (c2 == EOF)
			break;

		if (c1 != c2)
			break;

		++offset;
	}

	if (offset != len) {
		fprintf(stdout, _T("files differ at offset 0x%x"), offset);
	}

	fclose(fp1);
	fclose(fp2);
}

END_ANONYMOUS