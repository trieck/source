

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;

	if (argc < 2) {
		fprintf(stderr, "usage: bits file\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		fprintf(stderr, "unable to open file %s.\n", argv[1]);
		return 1;
	}

	while ((c = getc(fp)) != EOF) {
		int i;
		for (i = 8; i > 0; i--) {
			if (c & (1 << (i - 1)))
				putchar('1');
			else putchar('0');
		}
	}

	fclose(fp);

	return 0;
}
