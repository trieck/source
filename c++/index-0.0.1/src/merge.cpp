/////////////////////////////////////////////////////////////////////////////
//
// MERGE.CPP : n-way file merge 
//
// Merge sorted files into one large file, by recursively combining n files
// at a time into ever bigger files until only one file remains.
// 
// Merge is an template class that operates on a user-defined 
// record class.  The user must supply a record comparison function and 
// the member functions: open, close, read, write and unlink.
//
// Copyright (C) 2008 Thomas A. Rieck, All rights reserved.
// 

#include "global.h"
#include "merge.h"
