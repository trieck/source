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
#include "Util.h"

extern int yyparse(void);	// bison parser routine
extern FILE *yyin;			// input file pointer

/////////////////////////////////////////////////////////////////////////////
Assembler::Assembler() : m_pOut(NULL)
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

	if (m_pOut != NULL) {
		fclose(m_pOut);
		m_pOut = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
int Assembler::assemble(const char *filename)
{
	open(filename);

	int nret;
	if ((nret = yyparse()) != 0)
		return nret;

	// second pass
	Code *code = Code::getInstance();
	code->pass2();

	// write code to output file
	string output = format("%s.o", basename(filename).c_str());
	if ((m_pOut = fopen(output.c_str(), "wb")) == NULL) {
		throw Exception("can't open file \"%s\": %s.", output.c_str(),
			strerror(errno));
	}

	code->write(m_pOut);

	close();

	return 0;
}