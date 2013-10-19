/////////////////////////////////////////////////////////////////////////////
//
// LINEREADER.CPP : Read lines from input stream
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "LineReader.h"
#include "util.h"

/////////////////////////////////////////////////////////////////////////////
string LineReader::readLine()
{
	string output;

	int c;
	while ((c = is.get()) != -1) {
		if (c == '\r' || c == '\n')
			break;
		output += c;
	}

	return trim(output);
}
