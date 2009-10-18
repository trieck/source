/////////////////////////////////////////////////////////////////////////////
//
// COMMON.H : Common include
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//
#ifndef __COMMON_H__
#define __COMMON_H__

/////////////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fstream>

using std::istream;
using std::ifstream;
using std::ostream;
using std::ofstream;
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::map;
using std::vector;
using std::auto_ptr;

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

typedef vector<string> stringvec;

struct stringless : std::binary_function <string, string, bool> {
    bool operator () (const string & x, const string & y) const {
        return (_stricmp(x.c_str(), y.c_str()) > 0);
    }
};

#define HIBYTE(w)           ((w & 0xFF00) >> 8)
#define LOBYTE(w)           (w & 0xFF)

#define HINYBBLE(b)			((b & 0xF0) >> 4)
#define LONYBBLE(b)			(b & 0x0F)

/////////////////////////////////////////////////////////////////////////////

#endif // __COMMON_H__
