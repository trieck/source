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
	files = new FileInfo[MAXFILES];
	memset(files, 0, sizeof(FileInfo) * MAXFILES);
}

/////////////////////////////////////////////////////////////////////////////
Files::~Files()
{
	delete [] files;
}

/////////////////////////////////////////////////////////////////////////////
void Files::insert(const char *filename)
{
	if (count >= MAXFILES)
		error("too many files.");
	
	string fullname = fullpath(filename);	
	uint8_t len = MIN(fullname.length(), PATH_MAX-1);

	strncpy(files[count].filename, fullname.c_str(), len);
	files[count].filename[len] = '\0';
	files[count].filelen = len;
	count++;
}

/////////////////////////////////////////////////////////////////////////////
int Files::write(const char *filename)
{
	char outfile[PATH_MAX];
	sprintf(outfile, "%s.files", filename);

	FILE *fp;
	if ((fp = fopen(outfile, "wb")) == NULL)
		return 0;

	if (fwrite(files, sizeof(FileInfo) * count, 1, fp) != 1) {
		fclose(fp);
		return 0;	// can't write
	}
	
	fclose(fp);
		
	return 1;
}

