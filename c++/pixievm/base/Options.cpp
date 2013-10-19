/////////////////////////////////////////////////////////////////////////////
//
// OPTIONS.CPP : Program options
//
// Copyright (c) 2006-2013, Thomas A. Rieck
// All Rights Reserved
//

#include "Common.h"
#include "Options.h"
#include "Util.h"

namespace Options {

const char __nil[1] = { '\0' };

/////////////////////////////////////////////////////////////////////////////
class Options
{
// Construction / Destruction
public:
	Options(){}
	~Options() {}

// Interface
	void put(const char* name, const char* value = __nil) {
		options[name] = value;
	}

	bool isoption(const char* name) const {
		return options.find(name) != options.end();
	}

	string value(const char* name) const {
		OptionMap::const_iterator it = options.begin();
		if (it == options.end())
			return __nil;

		return (*it).second;
	}

// Implementation
private:
	typedef map<string, string, stringless> OptionMap;
	OptionMap options;
};

Options g_Options;

/////////////////////////////////////////////////////////////////////////////
void options(int argc, char **argv)
{
	const char *pval;
	string name, value;

	for ( ; argc; --argc, ++argv) {

		if (argv[0][0] != '-' && argv[0][1] != '-')
			continue;

		argv[0]++;
		argv[0]++;

		if ((pval = strchr(argv[0], '=')) != NULL) {	// option assignment
			name = string(argv[0], pval - argv[0]);
			name = trim(name);
			value = trim(++pval);
			g_Options.put(name.c_str(), value.c_str());
		} else {
			g_Options.put(argv[0]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
bool isoption(const char* option)
{
	return g_Options.isoption(option);
}

/////////////////////////////////////////////////////////////////////////////
string value(const char* option)
{
	return g_Options.value(option);
}


}	// Options
