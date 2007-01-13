/*
 * HEXDUMP.C
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 16

static void dump(const char *filename);
static const char *usage = "usage: hexdump file";

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "%s\n", usage);
		return 1;
	}

	argc--; argv++;

	dump(argv[0]);

	return 0;
}

void dump(const char *filename)
{
	unsigned long charcount = 0;
	int c;
	FILE *fp;
	
	if (!(fp = fopen(filename, "rb"))) {
		fprintf(stderr, "can't open file \"%s\".\n", filename);
		return;
	}

	while ((c = getc(fp)) != EOF) {
		unsigned char ch = (unsigned char)c;
		if (charcount % LINELEN == 0)
			printf("\n%.4x:", charcount);

		printf(" %.2x", ch);
		charcount++;
	}

	fclose(fp);
}