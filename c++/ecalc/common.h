/////////////////////////////////////////////////////////////////////////////
//
//	COMMON.H
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _MSC_VER
#pragma warning(disable:4786) // disable truncation warning
#endif // _MSC_VER

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>

using namespace std;

#define MAXSTRING 256

// Forward declarations
class Machine;

typedef void (Machine::*Instr)();

enum Keyword {
    PROC,
    FUNC,
    RETURN,
    IF,
    ELSE,
    WHILE,
    PRINTF
};

enum SymbolType {
    undefined = 0,
    number,
    variable,
    keyword,
    bltin,
    function,
    procedure,
    str
};

typedef struct {
	SymbolType type;
	union {
		double value;			// variable
		Keyword keyword;		// keyword name
		Instr instruction;		// built in
		Instr * defn;			// function / proc
		char str[MAXSTRING];	// string
	};
} Symbol;

typedef union {
	double value;
	Symbol * symbol;
} Datum;

#endif // __COMMON_H__

