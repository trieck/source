/////////////////////////////////////////////////////////////////////////////
//
//	UTIL.H : utility functions
//
//	Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __UTIL_INCLUDED_H__
#define __UTIL_INCLUDED_H__

/////////////////////////////////////////////////////////////////////////////
extern string tempname();
extern stringvec expand(const char *pattern);
extern stringvec rexpand(const char *pattern);
extern string dirname(const char *path);
extern string fullpath(const char *path);
extern string filename(const char *path);
extern string basename(const char *path);
extern string extname(const char *path);
extern string modulename();
extern string modulebasename();
extern string programdir();
extern string machinename();
extern string fileload(const string &file);
extern string itoa(int n);
extern string trim(const char *str);
extern string trim_left(const char *str);
extern string trim_right(const char *str);
extern string lower(const string & input);
extern string upper(const string & input);
extern string xmlescape(const string &input);
extern string comma(INT64 i);
extern string lasterror();
extern string format(const char *fmt, ...);
extern string uni2ansi(const wchar_t *pwstr);
extern wstring ansi2uni(const char *pstr);
extern string uni2utf8(const wchar_t *pwstr);
extern string ansi2utf8(const char *pstr);
/////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_INCLUDED_H__
