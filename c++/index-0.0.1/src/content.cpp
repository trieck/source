/////////////////////////////////////////////////////////////////////////////
//
// CONTENT.CPP
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"
#include "content.h"

/////////////////////////////////////////////////////////////////////////////
Content::Content()
		: estimatedcount(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Content::~Content()
{
}

/////////////////////////////////////////////////////////////////////////////
void Content::index(const stringvec &infiles, const char *outfile)
{
	outname = basefile(outfile);

	stringvec::const_iterator it = infiles.begin();
	for ( ; it != infiles.end(); it++) {
		const string &infile = *it;
		if (!lexer.open(infile.c_str())) {
			error("unable to open file \"%s\".", infile.c_str());
		}

		files.insert(infile.c_str());
		parse();

		lexer.close();
	}

	// write the file list
	if (!files.write(outfile)) {
		error("can't write file list.");
	}
}

/////////////////////////////////////////////////////////////////////////////
// parse input stream
void Content::parse(void)
{
	uint16_t filenum;
	const char *term;

	filenum = files.size();
	while ((term = lexer.gettok()) != NULL) {
		if (noise.isnoise(term))
			continue;

		if (block.isfull())
			blocksave();

		block.insert(term, filenum);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Content::blocksave()
{
	if (block.getcount() == 0)
		return;

	char *tempfile = tmpnam(NULL);
	datfiles.push_back(tempfile);

	estimatedcount += block.getcount();

	FILE *fp;
	if ((fp = fopen(tempfile, "wb")) == NULL) {
		error("can't create file %s.", tempfile);
	}

	if (!block.write(fp)) {
		error("can't write concordance block.");
	}

	fclose(fp);
}

