/////////////////////////////////////////////////////////////////////////////
//
// LOADCMD.CPP : Monitor load command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "LoadCmd.h"
#include "Memory.h"
#include <sys/stat.h>

/////////////////////////////////////////////////////////////////////////////
LoadCmd::LoadCmd(Monitor *mon) : Command(mon)
{
}

/////////////////////////////////////////////////////////////////////////////
LoadCmd::~LoadCmd()
{
}

/////////////////////////////////////////////////////////////////////////////
void LoadCmd::exec(const stringvec &v)
{
	if (v.size() < 1) {
		cerr << "? l file" << endl;
		return;
	}
	
	string filename = v[0];

	struct _stat buf;
	int n = stat(filename.c_str(), (struct stat*)&buf);
	if (n) {
		fprintf(stderr, "unable to stat file \"%s\".\n", filename.c_str());
		return;
	}

	ifstream ifs;
	ifs.open(filename.c_str(), ifstream::in | ifstream::binary);
	if (!ifs.is_open()) {
		fprintf(stderr, "unable to open file \"%s\".\n", filename.c_str());
		return;
	}

	word start;
	ifs.read((char*)&start, sizeof(word));
	if (ifs.bad()) {
		fprintf(stderr, "unable to read from file \"%s\".\n",
			filename.c_str());
		return;
	}

	Memory *mem = Memory::getInstance();
	if (!mem->load(ifs, start, buf.st_size - sizeof(word))) {
		fprintf(stderr, "unable to load file \"%s\".\n",
		        filename.c_str());
	}

	printf("file \"%s\" loaded at $%.4x.\n", filename.c_str(),
		start);
}
