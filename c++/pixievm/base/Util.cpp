/////////////////////////////////////////////////////////////////////////////
//
// UTIL.CPP : Utility functions
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Util.h"

/////////////////////////////////////////////////////////////////////////////
stringvec split(const string &s, const char *del)
{
	stringvec output;

	char *p = new char[s.length()+1];
	strcpy(p, s.c_str());
	
	char *tok = strtok(p, del);
	while (tok != NULL) {
		output.push_back(tok);
		tok = strtok(NULL, del);
	}

	delete []p;

	return output;
}

/////////////////////////////////////////////////////////////////////////////
stringvec tokenize(const string &s)
{
	stringvec output;

	const char *pstart = s.c_str();
	const char **ppin = &pstart;
	const char *pin = *ppin;

	for (;;) {
		switch (*pin) {
		case '\0':
			if (pin > *ppin) {
				output.push_back(string(*ppin, pin - *ppin));
				*ppin = pin;
			}
			return output;
		case '"':
			if (pin > *ppin) {
				output.push_back(string(*ppin, pin - *ppin));
				*ppin = pin;
			}
			pin++;		/* eat quote */
			(*ppin)++;
			while (*pin && *pin++ != '"');
			output.push_back(string(*ppin, pin - *ppin - 1));
			*ppin = pin;
			continue;
		case '\r':
		case '\n':
		case '\t':
		case ' ':
			if (pin > *ppin) {
				output.push_back(string(*ppin, pin - *ppin));
				*ppin = pin;
			}
			(*ppin)++;	/* eat white */
			break;
		default:
			pin++;
			continue;
		}
		pin++;
	}
}

/////////////////////////////////////////////////////////////////////////////
string trim(const string &s)
{
	string output;

	const char *pin = s.c_str();
	for ( ; *pin; pin++) {
		if (!isspace(*pin)) 
			break;
	}

	const char *pend = s.c_str() + s.length();
	for ( ; pend != pin; ) {
		if (!isspace(*--pend)) 
			break;
	}

	for ( ; *pin && pin <= pend; pin++) {
		output += *pin;
	}

	return output;
}