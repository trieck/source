/////////////////////////////////////////////////////////////////////////////
//
// UTIL.CPP : Utility functions
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Util.h"

#ifdef _MSC_VER
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif	// _MSC_VER

#define SUFFIX_SEP '.'

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

/////////////////////////////////////////////////////////////////////////////
string format(const char *fmt, ...)
{
	va_list arglist;
	va_start(arglist, fmt);

	char buf[8000];
	vsprintf(buf, fmt, arglist);

	va_end (arglist);

	return buf;
}

/////////////////////////////////////////////////////////////////////////////
string basename(const string &filename)
{
	string output;

	const char *fname = filename.c_str();
	const char *p;
	if ((p = strrchr(fname, PATH_SEP)) != NULL) {
		fname = p + 1;
	} 

	for ( ; *fname != '\0'; fname++) {
		if (*fname == SUFFIX_SEP)
			break;

		output += *fname;
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
string itoa(int n)
{
	static const int len = 20;
	char buffer[len] = { 0 };

	_itoa(n, buffer, 10);

	return buffer;
}

////////////////////////////////////////////////////////////////////////////
// 32-bit Fowler/Noll/Vo hash
uint32_t hash32(const void *key, uint32_t len)
{
	uint32_t i;
	uint32_t hash;
	const uint8_t *k = (const uint8_t*)key;

	for (hash=0, i = 0; i < len; ++i) {
		hash *= 16777619;
		hash ^= k[i];
	}
  
	return hash;
}

/////////////////////////////////////////////////////////////////////////////
// 64-bit Fowler/Noll/Vo hash
uint64_t hash64(const void *key, uint64_t len)
{
	uint32_t i;
	uint64_t hash;
	const uint8_t *k = (const uint8_t*)key;

	for (hash=0, i = 0; i < len; ++i) {
		hash *= 1099511628211;
		hash ^= k[i];
	}
  
	return hash;
}

#ifdef _MSC_VER

/////////////////////////////////////////////////////////////////////////////
uint32_t counter32()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	// avalanche 
	return hash32(&counter.QuadPart, sizeof(uint64_t));
}

#endif // _MSC_VER