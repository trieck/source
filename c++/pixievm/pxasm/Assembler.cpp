/////////////////////////////////////////////////////////////////////////////
//
// ASSEMBLER.CPP : Assembler interface
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Assembler.h"
#include "Exception.h"
#include "Code.h"

extern int yyparse(void);	// bison parser routine
extern FILE *yyin;			// input file pointer
extern FILE *yyout;			// output file pointer

/////////////////////////////////////////////////////////////////////////////
Assembler::Assembler()
{
}

/////////////////////////////////////////////////////////////////////////////
Assembler::~Assembler()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Assembler::open(const char *filename)
{
	close();

	if ((yyin = fopen(filename, "r")) == NULL) {
		throw Exception("can't open file \"%s\": %s.", filename,
		                strerror(errno));
	}
}

void Assembler::close()
{
	if (yyin != NULL && yyin != stdin) {
		fclose(yyin);
		yyin = NULL;
	}

	if (yyout != NULL && yyout != stdout) {
		fclose(yyout);
		yyout = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
int Assembler::assemble(const char *filename)
{
	open(filename);

	int nret;
	if ((nret = yyparse()) != 0)
		return nret;

	// second pass, resolve any fix-up locations
	Code *code = Code::getInstance();
	code->resolve();

	return 0;
}