/////////////////////////////////////////////////////////////////////////////
//
// FILE.H : ADF file definition
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __FILE_H__
#define __FILE_H__

class Volume;

/////////////////////////////////////////////////////////////////////////////
class File 
{
// Construction / Destruction
public:
	File(Volume *pVol, entryblock_t *pEntry);
	~File();

// Interface
	Volume *getVolume() const;
	uint32_t read(uint32_t n, void *buf);
	uint32_t getSize() const;
	bool isEOF() const;

// Implementation
private:
	void readnext();		// read next data block
	Volume *volume;			// parent volume
	fileheader_t header;	// file header
	uint32_t pos;			// read/write position in file
	uint32_t blockpos;		// block pointer position
	uint32_t nblock;		// current data block number
	uint8_t *data;			// current data pointer
	uint8_t buffer[BSIZE];	// data buffer
};

typedef auto_ptr<File> FilePtr;

/////////////////////////////////////////////////////////////////////////////
inline Volume *File::getVolume() const
{
	return volume;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t File::getSize() const
{
	return header.bytesize;
}

#endif // __FILE_H__

