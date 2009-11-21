/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPT.CPP	exception classes
//
//	Copyright (c) 1999 Thomas A. Rieck

#include "common.h"
#include "except.h"

typedef struct {
	int ncode;
	const char* desc;
} except;

static except xtable[] = {
	{ E_FRAMEUNDERRUN, "frame stack underrun encountered" },
	{ E_CALLNESTEDTOODEEP, "call nested too deeply" },
	{ E_STACKUNDERRUN, "stack underrun encountered" },
	{ E_STACKTOODEEP, "stack too deep" },
	{ W_DIVIDEBYZERO, "attempt to divide by 0" },
	{ W_LITERALASSIGN, "attempt to assign to literal" },
	{ W_NONVARASSIGN, "attempt to assign to non-variable" },
	{ W_EVALLITERAL, "attempt to evaluate literal" },
	{ W_UNDEFINEDVAR, "undefined variable" },
	{ W_PROCRETVAL, "proc returns value" },
	{ W_FUNCRETNOVAL, "func returns no value" },
	{ W_NOTENOUGHARGS, "not enough arguments" }
};

// Helper functions
const char *lookup(int code);

/////////////////////////////////////////////////////////////////////////////
// Exception
Exception::Exception(int code)
{
	ncode = code;
}

Exception::Exception(const Exception & e)
{
	ncode = e.ncode;
	desc = e.desc;
}

Exception & Exception::operator = (const Exception & e)
{
	if (this != &e) {
		ncode = e.ncode;
		desc = e.desc;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Warning
Warning::Warning(int code)
		: Exception(code)
{
	desc = "warning: (";
	desc += lookup(code);
	desc += ")";
}

/////////////////////////////////////////////////////////////////////////////
// Error
Error::Error(int code)
		: Exception(code)
{
	desc = "error: (";
	desc += lookup(code);
	desc += ")";
}

// Helper functions
const char *lookup(int code)
{
	int nitems = sizeof(xtable) / sizeof(except);
	for (int i = 0; i < nitems; i++) {
		if (xtable[i].ncode == code)
			return xtable[i].desc;
	}

	return NULL;
}

// global helpers
ostream & operator << (ostream & os, const Exception & e)
{
	return os << e.desc;
}
