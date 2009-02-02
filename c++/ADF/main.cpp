/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Amiga Disk File driver program
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "volume.h"
#include "disk.h"
#include "adfexcept.h"
#include "adfwarn.h"

/////////////////////////////////////////////////////////////////////////////
class MyHandler : public IADFWarningHandler
{
public:
	void handle(const string &s) const;
};

/////////////////////////////////////////////////////////////////////////////
void MyHandler::handle(const string &s) const
{
	cerr << s << endl;
}

MyHandler warning;

/////////////////////////////////////////////////////////////////////////////
void readdir(const char *file)
{
	DiskPtr disk = Disk::open(file);
	Volume *vol = disk->mount();

	EntryList entries = vol->readdir(vol->getRootBlock(), false);
	EntryList::const_iterator it = entries.begin();

	for ( ; it != entries.end(); it++) {
		const Entry &entry = *it;
		if (entry.type == ST_DIR) cout << '[';
		cout << entry.name;
		if (entry.type == ST_DIR) cout << ']';
		cout << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////
void openfile(const char *adffile, const char *filename)
{
	DiskPtr disk = Disk::open(adffile);
	Volume *vol = disk->mount();

	FilePtr file = vol->openfile(filename);	
	
	char buf[100];
	uint32_t nread;
	
	while ((nread = file->read(100, buf))) {
		string output = string(buf, nread);
		cout << output;
	}
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 3) {
		cerr << "usage: adf adf-file filename" << endl;
		return 1;
	}

	ADFWarningRegistrar::Register(&warning);

	try {
		openfile(argv[1], argv[2]);
	} catch (const ADFException &e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	return 0;
}
