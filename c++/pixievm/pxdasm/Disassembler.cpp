/////////////////////////////////////////////////////////////////////////////
//
// DISASSEMBLER.CPP : PixieVM Disassembler
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Disassembler.h"
#include "Exception.h"

/////////////////////////////////////////////////////////////////////////////
Disassembler::Disassembler() : m_fp(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
Disassembler::~Disassembler()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::close()
{
	if (m_fp != NULL) {
		fclose(m_fp);
		m_fp = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::open(const char *filename)
{
	close();

	if ((m_fp = fopen(filename, "rb")) == NULL) {
		throw Exception("can't open file \"%s\": %s.", filename,
		                strerror(errno));
	}

}

/////////////////////////////////////////////////////////////////////////////
void Disassembler::disassemble(const char *filename)
{
	open(filename);

	word start;
	if ((1 != fread(&start, sizeof(word), 1, m_fp))) {
		throw Exception("can't read from file \"%s\": %s", filename,
		                strerror(errno));
	}

	PxDisassembler::ip = start;

	int c;
	while ((c = fgetc(m_fp)) != EOF) {
		ungetc(c, m_fp);
		printip();
		PxDisassembler::disassemble(fetch());
	}

	close();
}

/////////////////////////////////////////////////////////////////////////////
byte Disassembler::fetch()
{
	int c;
	if ((c = fgetc(m_fp)) == EOF)
		return 0;

	++ip;

	return c;
}
