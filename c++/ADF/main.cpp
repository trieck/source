/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Amiga Disk File system driver
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
int main(int argc, char *argv[])
{
	ADFWarningRegistrar::Register(&warning);

	try {
		DiskPtr disk = Disk::open("d:\\amiga\\adf\\Workbench1.3.adf");
		VolumePtr vol = disk->mount();
	} catch (const ADFException &e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	return 0;
}
