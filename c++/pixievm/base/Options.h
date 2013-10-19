/////////////////////////////////////////////////////////////////////////////
//
// OPTIONS.H : Program options
//
// Copyright (c) 2006-2013, Thomas A. Rieck
// All Rights Reserved
//

#ifndef __OPTIONS_H__
#define __OPTIONS_H__

/////////////////////////////////////////////////////////////////////////////
namespace Options
{
	void options(int argc, char **argv);
	bool isoption(const char* option);
	string value(const char* option);
}

#endif // __OPTIONS_H__
