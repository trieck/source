/*
 * 	MAIN.C : binary dumper
 *
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 */

#include "common.h"
#include "layout.h"

static void usage(void);
static void dump(const char *filename);

const char *log_file_name = NULL;	/* stderr */

/*
 * main entry point
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();

	dump(argv[1]);

	return 0;
}

/*
 * dump the file
 */
void dump(const char *filename)
{
	FILE *fp;
	FileHeader fh;
	unsigned const int magic = OBJ_MAGIC_NUMBER;

	/* filename must end in .o extension */
	size_t N = strlen(filename);
	if (strcmp(filename + N - 2, ".o"))
		error("file must end with .o extension.\n");

	/* open the file */
	fp = fopen(filename, "rb");
	if (fp == NULL)
		error("unable to open file %s.\n", filename);

	/* read in the file header */
	N = fread(&fh, sizeof(FileHeader), 1, fp);
	if (1 != N) {
		fclose(fp);
		error("unable to read file header.\n");
	}

	/* ensure this is a valid image */
	if (memcmp(&magic, fh.magic, sizeof(fh.magic)) != 0) {
		fclose(fp);
		error("file is not valid binary image.\n");
	}

	fclose(fp);
}

/*
 * print usage
 */
void usage(void)
{
	fprintf(stderr, "usage: 65dump file\n");
	exit(1);
}
