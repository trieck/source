/////////////////////////////////////////////////////////////////////////////
//
// UTIL.H : Utility functions
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __UTIL_H__
#define __UTIL_H__

/////////////////////////////////////////////////////////////////////////////
string format(const char *fmt, ...);
stringvec split(const string &s, const char *del);
stringvec tokenize(const string &s);
string trim(const string &s);
string basename(const string &file);
string itoa(int n);
string uniq();
/////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_H__