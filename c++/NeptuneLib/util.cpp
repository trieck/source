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
tstring tempname()
{
    TCHAR path[MAX_PATH] = { 0 };
    TCHAR filename[MAX_PATH] = { 0 };

    GetTempPath(MAX_PATH, path);
    GetTempFileName(path, _T(""), 0, filename);

    return filename;
}

/////////////////////////////////////////////////////////////////////////////
tstringvec expand(LPCTSTR arg)
{
    tstringvec doclist;
    tstring dir = dirname(arg);

    struct _tfinddata_t file;
    long h = _tfindfirst(arg, &file);

    if (h == -1)
        return doclist;

    do {
        if (file.attrib & _A_SUBDIR)
            continue;

        doclist.push_back(lower(dir + file.name));
    } while (_tfindnext(h, &file) == 0);

    _findclose(h);

    return doclist;
}

/////////////////////////////////////////////////////////////////////////////
tstringvec rexpand(LPCTSTR arg)
{
    TCHAR patt[MAX_PATH + _MAX_FNAME + 1];

    tstringvec doclist, tmplist;
    tstring dir = dirname(arg);
    tstring pattern = arg;

    tstring::size_type N = pattern.find_last_of('\\');
    if (N != tstring::npos)
        pattern = pattern.substr(++N);

    struct _tfinddata_t file;
    long h = _tfindfirst(arg, &file);

    if (h == -1) { // no pattern match try subdirectories
        _stprintf(patt, _T("%s*"), dir.c_str());
        h = _tfindfirst(patt, &file);
        if (h == -1)
            return doclist;

        do {
            if (_tcscmp(file.name, _T(".")) == 0)
                continue;
            if (_tcscmp(file.name, _T("..")) == 0)
                continue;

            if (file.attrib & _A_SUBDIR) {
                _stprintf(patt, _T("%s%s\\%s"), dir.c_str(), file.name,
                    pattern.c_str());
                tmplist = rexpand(patt);
                doclist.insert(doclist.end(), tmplist.begin(),
                    tmplist.end());
            }

        } while (_tfindnext(h, &file) == 0);

        _findclose(h);

        return doclist;
    }

    do {
        if (_tcscmp(file.name, _T(".")) == 0)
            continue;
        if (_tcscmp(file.name, _T("..")) == 0)
            continue;

        if (file.attrib & _A_SUBDIR) {
            _stprintf(patt, _T("%s%s\\%s"), dir.c_str(), file.name,
                pattern.c_str());
            tmplist = rexpand(patt);
            doclist.insert(doclist.end(), tmplist.begin(),
                tmplist.end());
            continue;
        }

        doclist.push_back(lower(dir + file.name));

    } while (_tfindnext(h, &file) == 0);

    _findclose(h);

    return doclist;
}

/////////////////////////////////////////////////////////////////////////////
tstring dirname(LPCTSTR path)
{
    TCHAR drive[_MAX_DRIVE] = { 0 };
    TCHAR dir[_MAX_PATH] = { 0 };

    _tsplitpath(path, drive, dir, NULL, NULL);

    return tstring(drive) + dir;
}

/////////////////////////////////////////////////////////////////////////////
tstring fullpath(const TCHAR *path)
{
    TCHAR buffer[_MAX_PATH + _MAX_FNAME + 1];
    buffer[0] = '\0';

    _tfullpath(buffer, path, _MAX_PATH + _MAX_FNAME);

    return buffer;
}

/////////////////////////////////////////////////////////////////////////////
tstring filename(LPCTSTR path)
{
    TCHAR filename[_MAX_FNAME] = { 0 };
    TCHAR ext[_MAX_EXT] = { 0 };
    TCHAR output[_MAX_FNAME + _MAX_EXT + 1];

    _tsplitpath(path, NULL, NULL, filename, ext);

    _stprintf(output, _T("%s%s"), filename, ext);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring basename(LPCTSTR path)
{
    TCHAR drive[_MAX_DRIVE] = { 0 };
    TCHAR dir[_MAX_PATH] = { 0 };
    TCHAR file[_MAX_FNAME] = { 0 };
    TCHAR output[_MAX_DRIVE + _MAX_PATH + _MAX_FNAME + 1];

    tstring name = filename(path);

    _tsplitpath(name.c_str(), drive, dir, file, NULL);

    _stprintf(output, _T("%s%s%s"), drive, dir, file);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring extname(LPCTSTR path)
{
    TCHAR ext[_MAX_EXT] = { 0 };

    _tsplitpath(path, NULL, NULL, NULL, ext);

    return ext;
}

/////////////////////////////////////////////////////////////////////////////
tstring modulename()
{
    TCHAR path[_MAX_PATH + _MAX_FNAME + 1] = { 0 };

    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(programdir, &mbi, sizeof(mbi));

    GetModuleFileName((HINSTANCE)mbi.AllocationBase, path,
        _MAX_PATH + _MAX_FNAME);

    return path;
}

/////////////////////////////////////////////////////////////////////////////
tstring modulebasename()
{
    return basename(modulename().c_str());
}

/////////////////////////////////////////////////////////////////////////////
tstring programdir()
{
    return lower(dirname(modulename().c_str()));
}

/////////////////////////////////////////////////////////////////////////////
tstring itoa(int n)
{
    static const int len = 20;
    TCHAR buffer[len] = { 0 };

    _itot(n, buffer, 10);

    return buffer;
}

/////////////////////////////////////////////////////////////////////////////
tstring trim(const TCHAR *str)
{
    return trim_left(trim_right(str).c_str());
}

/////////////////////////////////////////////////////////////////////////////
tstring trim_left(const TCHAR *str)
{
    size_t len, idx;

    len = _tcslen(str);

    for (idx = 0; idx < len; idx++) {
        if (!isspace(str[idx]))
            break;
    }

    return &str[idx];
}

/////////////////////////////////////////////////////////////////////////////
tstring trim_right(const TCHAR *str)
{
    size_t idx = _tcslen(str);

    if (idx == 0)
        return _T("");

    for (idx--; isspace(str[idx]); idx--)
        ;

    return tstring(str, idx + 1);
}

/////////////////////////////////////////////////////////////////////////////
tstring comma(INT64 i)
{
    tstring output;

    TCHAR buff[MAX_PATH];
    _stprintf(buff, _T("%I64u"), i);

    int n = _tcslen(buff);

    for (int j = n - 1, k = 1; j >= 0; j--, k++) {
        output += buff[j];
        if (k % 3 == 0 && j > 0 && j < n - 1)
            output += ',';
    }

    std::reverse(output.begin(), output.end());

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring lower(const tstring & input)
{
    tstring output;

    size_t N = input.length();
    output.resize(N);

    unsigned i;
    for (i = 0; i < N; i++)
        output[i] = tolower(input[i]);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring upper(const tstring & input)
{
    tstring output;

    size_t N = input.length();
    output.resize(N);

    unsigned i;
    for (i = 0; i < N; i++)
        output[i] = toupper(input[i]);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring lasterror()
{
    tstring output;

    TCHAR *pmsg = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&pmsg, 0, NULL);

    if (pmsg != NULL) {
        int N = _tcslen(pmsg);
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
tstring fileload(const tstring &file)
{
    // read in a file into a tstring using the "big gulp" method
    int fd = _topen(file.c_str(), _O_RDONLY | _O_BINARY | _O_SEQUENTIAL);

    if (fd == -1)
        return _T("");

    struct stat status;
    fstat(fd, &status);

    TCHAR* pbuf = new TCHAR[status.st_size + 1];

    int nread = read(fd, pbuf, status.st_size);

    pbuf[nread] = '\0';

    tstring output = pbuf;
    delete[] pbuf;

    close(fd);

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring xmlescape(const tstring &input)
{
    tstring output;

    const TCHAR *pin = input.c_str();

    while (*pin) {
        if (*pin == '"') {
            output += _T("&quot;");
            pin++;
        }
        else if (*pin == '<') {
            output += _T("&lt;");
            pin++;
        }
        else if (*pin == '>') {
            output += _T("&gt;");
            pin++;
        }
        else if (*pin == '&') {
            output += _T("&amp;");
            pin++;
        }
        else {
            output += *pin++;
        }
    }

    return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring machinename()
{
    DWORD len = MAX_COMPUTERNAME_LENGTH;
    TCHAR cname[MAX_COMPUTERNAME_LENGTH + 1];

    GetComputerName(cname, &len);

    return cname;
}

/////////////////////////////////////////////////////////////////////////////
tstring format(const TCHAR *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    TCHAR buf[8000];
    _vstprintf(buf, fmt, arglist);

    va_end(arglist);

    return buf;
}
