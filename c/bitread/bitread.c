

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	struct _stat st;
	char buff[8];

	if (argc < 2) {
		fprintf(stderr, "usage: bitread file\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		fprintf(stderr, "unable to open file %s.\n", argv[1]);
		return 1;
	}

	if (-1 == _fstat(_fileno(fp), &st)) {
		fprintf(stderr, "unable to stat file %s.\n", argv[1]);
	}

	if (st.st_size % 8 != 0) {
		fprintf(stderr, "file %s is not valid size.\n", argv[1]);
	}

	while (fread(buff, sizeof(buff), 1, fp)) {
		int j, k;
		unsigned char c;

		for (j = 8, k = 0; j > 0; j--, k++) {
			if (buff[k] == '1')
				c |= (1 << (j - 1));
			else if (buff[k] == '0')
				c &= ~(1 << (j - 1));
			else {
				fprintf(stderr, "unrecognized character [%c].\n", buff[k]);
				fclose(fp);
				return 1;
			}
		}
		putchar(c);
	}

	fclose(fp);

	return 0;
}
