/////////////////////////////////////////////////////////////////////////////
//
//	UTIL.H : utility functions
//
//	Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __UTIL_INCLUDED_H__
#define __UTIL_INCLUDED_H__

/////////////////////////////////////////////////////////////////////////////
extern tstring tempname();
extern tstringvec expand(LPCTSTR pattern);
extern tstringvec rexpand(LPCTSTR pattern);
extern tstring dirname(LPCTSTR path);
extern tstring fullpath(LPCTSTR path);
extern tstring filename(LPCTSTR path);
extern tstring basename(LPCTSTR path);
extern tstring extname(LPCTSTR path);
extern tstring modulename();
extern tstring modulebasename();
extern tstring programdir();
extern tstring machinename();
extern tstring fileload(const tstring &file);
extern tstring itoa(int n);
extern tstring trim(LPCTSTR str);
extern tstring trim_left(LPCTSTR str);
extern tstring trim_right(LPCTSTR str);
extern tstring lower(const tstring & input);
extern tstring upper(const tstring & input);
extern tstring xmlescape(const tstring &input);
extern tstring comma(INT64 i);
extern tstring lasterror();
extern tstring format(LPCTSTR fmt, ...);
/////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_INCLUDED_H__
