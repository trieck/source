// StringTokenizer.cpp: implementation of the StringTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
StringTokenizer::StringTokenizer(LPCSTR pinput, LPCSTR pdelim)
	: delim(pdelim), init(false), nextoken(0)
{
	input = strdup(pinput);
}

/////////////////////////////////////////////////////////////////////////////
StringTokenizer::~StringTokenizer()
{
	delete []input;
}

/////////////////////////////////////////////////////////////////////////////
CString StringTokenizer::next()
{
	const char *ptok;
	if (init)
		ptok = StringTokenizer::strtok(NULL);
	else {
		ptok = StringTokenizer::strtok(input);
		init = true;
	}

	return ptok == NULL ? "" : ptok;
}

// adapted from MS C runtime library, doesn't support multiple threads
//
LPCSTR StringTokenizer::strtok(LPCSTR string)
{
	LPBYTE str;
	LPCBYTE ctrl = (LPCBYTE)(LPCSTR)delim;

	BYTE map[32];
	int count;

	/* Clear control map */
	for (count = 0; count < 32; count++)
		map[count] = 0;

	/* Set bits in delimiter table */
	do {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
	} while (*ctrl++);

	/* Initialize str. If string is NULL, set str to the saved
	 * pointer (i.e., continue breaking tokens out of the string
	 * from the last strtok call)
	 */
	if (string)
		str = (LPBYTE)string;
	else
		str = (LPBYTE)nextoken;

	/* Find beginning of token (skip over leading delimiters). Note that
	 * there is no token if this loop sets str to point to the terminal
	 * null (*str == '\0')
	 */
	while ((map[*str >> 3] & (1 << (*str & 7))) && *str)
		str++;

	string = (PCHAR)str;

	/* Find the end of the token. If it is not the end of the string,
	 * put a null there.
	 */
	for ( ; *str; str++)
		if (map[*str >> 3] & (1 << (*str & 7))) {
			*str++ = '\0';
			break;
		}

	/* Update nextoken (or the corresponding field in the per-thread data
	 * structure
	 */
	nextoken = (PCHAR)str;

	/* Determine if a token has been found. */
	if (string == (PCHAR)str)
		return NULL;
	else
		return string;
}
