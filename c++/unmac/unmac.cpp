
/*
 * An annoying little program to fix
 * files that have embedded Macintosh line ending's '\r'
 * and are NOT followed by '\n'.  In this case, we do
 * NOT want to turn them into Windows \r\n or UNIX \n.
 * We want to remove them entirely from the output stream.
 *
 */
#include <stdio.h>
#include <string.h>

static FILE *fpin = stdin, *fpout = stdout;

void cleanup(void)
{
	if (fpin != NULL) {
		fclose(fpin);
		fpin = NULL;
	}

	if (fpout != NULL) {
		fclose(fpout);
		fpout = NULL;
	}
}

int main(int argc, char *argv[])
{
	atexit(cleanup);

	for (int i = 1; i < argc; i++) {
		if (strncmp(argv[i], "--input=", 8) == 0) {
			if ((fpin = fopen(argv[i]+8, "r")) == NULL) {
				fprintf(stderr, "cannot open %s.\n", argv[i]+8);
				return 1;
			}
		}

		if (strncmp(argv[i], "--output=", 9) == 0) {
			if ((fpout = fopen(argv[i]+9, "w")) == NULL) {
				fprintf(stderr, "cannot open %s.\n", argv[i]+9);
				return 1;
			}
		}
	}

	int c, last = EOF;
	while ((c = getc(fpin)) != EOF) {
		if (c != '\r') {
			putc(c, fpout);
		}
		last = c;
	}

	return 0;
}
