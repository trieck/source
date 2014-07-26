// StringTokenizer.cpp: implementation of the StringTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
StringTokenizer::StringTokenizer(LPCTSTR pinput, LPCTSTR pdelim)
: delim(pdelim), init(false), nextoken(0)
{
	input = _tcsdup(pinput);
}

/////////////////////////////////////////////////////////////////////////////
StringTokenizer::~StringTokenizer()
{
	delete [] input;
}

/////////////////////////////////////////////////////////////////////////////
CString StringTokenizer::next()
{
	const TCHAR* ptok;
	if (init)
		ptok = StringTokenizer::strtok(NULL);
	else {
		ptok = StringTokenizer::strtok(input);
		init = true;
	}

	return ptok == NULL ? _T("") : ptok;
}

// adapted from MS C runtime library
//
LPTSTR StringTokenizer::strtok(LPTSTR string)
{
	LPTSTR token;
	LPCTSTR ctl;

	// If string==NULL, continue with previous string
	if (!string)
		string = nextoken;

	/* Find beginning of token (skip over leading delimiters). Note that
	 * there is no token iff this loop sets string to point to the terminal
	 * null (*string == '\0') */
	while (*string) {
		for (ctl = delim; *ctl && *ctl != *string; ctl++)
			;
		if (!*ctl) break;
		string++;
	}

	token = string;

	/* Find the end of the token.If it is not the end of the string,
	 * put a null there. */
	for (; *string; string++) {
		for (ctl = delim; *ctl && *ctl != *string; ctl++)
			;
		if (*ctl) {
			*string++ = '\0';
			break;
		}
	}

	nextoken = string;

	// determine if a token has been found.
	if (token == string)
		return NULL;
	else
		return token;
}
