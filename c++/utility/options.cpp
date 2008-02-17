/////////////////////////////////////////////////////////////////////////////
//
// OPTIONS.CPP : Command line option processing
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#include "options.h"
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
bool isoption(const char *opt)
{
	char **argv = __argv;

	for (int i = 0; i < __argc; i++) {
		if (argv[i][0] != '-' && argv[i][1] != '-')
			continue;

		if (strncmp(&argv[i][2], opt, strlen(opt)) == 0)
			return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
const char *optionval(const char *opt)
{
	char **argv = __argv;

	for (int i = 0; i < __argc; i++) {
		if (argv[i][0] != '-' && argv[i][1] != '-')
			continue;

		if (strncmp(&argv[i][2], opt, strlen(opt)) == 0) {
			const char *p;
			if ((p = strchr(argv[i], '=')) == NULL)
				return NULL;
			return ++p;
		}
	}

	return NULL;
}