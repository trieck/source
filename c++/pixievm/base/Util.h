/////////////////////////////////////////////////////////////////////////////
//
// UTIL.H : Utility functions
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
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
uint32_t counter32();
uint32_t hash32(const void *key, uint32_t len);
uint64_t hash64(const void *key, uint64_t len);
/////////////////////////////////////////////////////////////////////////////

#endif // __UTIL_H__