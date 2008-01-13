/////////////////////////////////////////////////////////////////////////////
//
// FILES.CPP : List of files indexed
//
// Copyright (c) 2008 Thomas A. Rieck
//

#include "global.h"
#include "files.h"

/////////////////////////////////////////////////////////////////////////////
Files::Files()
 : count(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Files::~Files()
{
}

/////////////////////////////////////////////////////////////////////////////
void Files::insert(const char *filename)
{
	if (count >= MAXFILES)
		error("too many files.");
		
	uint8_t len = MIN(strlen(filename), PATH_MAX-1);
	strncpy(files[count].filename, filename, len);
	files[count].filename[len] = '\0';
	files[count].filelen = len;
	count++;
}

/////////////////////////////////////////////////////////////////////////////
int Files::write(FILE *fp)
{
	if (fwrite(files, sizeof(FileInfo) * count, 1, fp) != 1)
		return 0;	// can't write
			
	return 0;
}
