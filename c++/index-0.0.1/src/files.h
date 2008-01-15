/////////////////////////////////////////////////////////////////////////////
//
// FILES.H : List of files indexed
//
// Copyright (c) 2008 Thomas A. Rieck
//

#ifndef __FILES_H__
#define __FILES_H__

/////////////////////////////////////////////////////////////////////////////
// information about a file
struct FileInfo {
	uint8_t filelen;			// length of file name
	char filename[PATH_MAX];	// file name	
} PACK_ONE;

/////////////////////////////////////////////////////////////////////////////
class Files
{
// Construction / Destruction
public:
	Files();
	~Files();
	
// Interface
	void insert(const char *filename);
	int write(const char *filename);		
	uint16_t size() const { return count; }

// Implementation
private:
	enum { MAXFILES = 3000 };
	FileInfo *files;	
	uint16_t count;
};

#endif // __FILES_H__
