/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP	main entry point
//
// Copyright (c) 1999 Thomas A. Rieck
//

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include "common.h"
#include "machine.h"
#include "compile.h"

// singleton instance
static Machine machine;

static const char *usage = "usage: ecalc [file][--stdin]";

// helper functions
static string load (const char* file);

//
// main
//
int main(int argc, char * argv[])
{
	if (argc < 2) {
		cout << usage << endl;
		return 1;
	}
	
	argc--; argv++;

	if (strcmp(argv[0], "--stdin") == 0) {
		while (cin) {
			char line[256];
			cin.getline(line, sizeof(line));
			machine.run(line);
		}
		return 0;
	}

	string file = load(argv[0]);
	machine.run(file.c_str());

	return 0;
}

//
// Helper functions
//

//
// load
//
string load(const char* file)
{
    // read in a file into a string using the "big gulp" method
    FILE * fp = fopen(file, "r");
	if (fp == NULL) {
		cerr << "unable to open file " << file << '.' << endl;
		exit (1);
	}

    struct stat status;
    stat(file, &status);

    char* pbuf = new char [status.st_size + 1];

    size_t nitems = fread(pbuf, 1, status.st_size, fp);
	
	string output = string(pbuf, nitems);
	delete [] pbuf;

    fclose(fp);

    return output;
}

