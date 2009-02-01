/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Amiga Disk File system driver
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#include "common.h"
#include "adf.h"
#include "volume.h"
#include "disk.h"

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	DiskPtr disk;
	disk = Disk::open("d:\\amiga\\adf\\Workbench1.3.adf");

	VolumePtr vol = disk->mount();

	return 0;
}
