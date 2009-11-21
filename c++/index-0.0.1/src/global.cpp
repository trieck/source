/////////////////////////////////////////////////////////////////////////////
//
// GLOBAL.CPP : Global definitions
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"

extern int vsnprintf(char *, size_t n, char const *, va_list);

/////////////////////////////////////////////////////////////////////////////
// The delta table generates primes just less than a power of two.  A prime
// number is calculated by subtracting its delta value from its
// corresponding power of two.
static uint8_t delta[] = {
	0, 0, 1, 3, 3, 1, 3, 1, 5, 3,
	3, 9, 3, 1, 3, 19, 15, 1, 5, 1,
	3, 9, 3, 15, 3, 39, 5, 39, 57, 3,
	35, 1, 5, 9, 41, 31, 5,
	25, 45, 7,
	87, 21, 11, 57, 17, 55, 21, 115, 59, 81,
	27,
	129, 47, 111, 33, 55, 5, 13, 27, 55,
	93, 1, 57, 25, 59
};

/////////////////////////////////////////////////////////////////////////////
// error routine
void error(const char *fmt, ...)
{
	va_list arglist;
	char msg[PATH_MAX];

	va_start(arglist, fmt);
	vsnprintf(msg, PATH_MAX, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "%s\n", msg);

	exit(1);
}

/////////////////////////////////////////////////////////////////////////////
// 64-bit Fowler/Noll/Vo hash
uint64_t fnvhash(const void *key, uint32_t len)
{
	uint32_t i;
	uint64_t h;

	const uint8_t *k = (const uint8_t *) key;

	for (h = 0, i = 0; i < len; ++i) {
		h *= PLATFORM_S64(1099511628211);
		h ^= k[i];
	}

	return h;
}

/////////////////////////////////////////////////////////////////////////////
uint64_t doublehash(const void *key, uint32_t len)
{
	uint64_t h = fnvhash(key, len);
	return fnvhash(&h, sizeof(uint64_t));
}

/////////////////////////////////////////////////////////////////////////////
// Compute the largest prime less than a specified power of two
uint64_t prime(uint64_t i)
{
	uint32_t j = 1;

	while (i >>= 1)
		j++;

	return (PLATFORM_S64(1) << j) - delta[j];
}

/////////////////////////////////////////////////////////////////////////////
string fullpath(const char *filename)
{
	char buf[PATH_MAX];
	buf[0] = '\0';

#if _MSC_VER
	_fullpath(
	    buf,
	    filename,
	    PATH_MAX);
#else	// _MSC_VER	
	realpath(filename, buf);
#endif 	// _MSC_VER

	return buf;
}

/////////////////////////////////////////////////////////////////////////////
string basefile(const char* path)
{
#if _MSC_VER
	char output[PATH_MAX];
	char filename[_MAX_FNAME] = { 0 };
	char ext[_MAX_EXT] = { 0 };

	_splitpath(path, NULL, NULL, filename, ext);
	sprintf(output, "%s%s", filename, ext);
	return output;
#else	// _MSC_VER	
	return basename((char*)path);
#endif 	// _MSC_VER	
}

#ifdef _MSC_VER

/////////////////////////////////////////////////////////////////////////////
string dirname(const char* path)
{
	char drive[_MAX_DRIVE] = { 0 };
	char dir[_MAX_PATH] = { 0 };

	_splitpath(path, drive, dir, NULL, NULL);

	return string(drive) + dir;
}

/////////////////////////////////////////////////////////////////////////////
stringvec expand(const char* arg)
{
	stringvec files;
	string dir = dirname(arg);

	struct _finddata_t file;
	long h = _findfirst(arg, &file);

	if (h == -1)
		return files;

	do {
		if (file.attrib & _A_SUBDIR)
			continue;

		files.push_back(dir+file.name);
	} while (_findnext(h, &file) == 0);

	_findclose(h);

	return files;
}

#endif 	// _MSC_VER
