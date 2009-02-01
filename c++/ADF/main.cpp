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

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	try {
		DiskPtr disk = Disk::open("d:\\amiga\\adf\\Workbench1.3.adf");
		VolumePtr vol = disk->mount();
	} catch (const ADFException &e) {
		cerr << e.getDescription() << endl;
		exit(1);
	}

	return 0;
}
