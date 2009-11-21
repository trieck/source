
/*
 * An annoying little program to fix
 * files that have embedded Macintosh line ending's '\r'
 * and are NOT followed by '\n'.  In this case, we do
 * NOT want to turn them into Windows \r\n or UNIX \n.
 * We want to remove them entirely from the output stream.
 */
#include <stdio.h>

int peekchar()
{
	int c = getchar();

	ungetc(c, stdin);

	return c;
}

int main(int argc, char *argv[])
{
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\r' && peekchar() != '\n') {
			;
		} else {
			putchar(c);
		}
	}

	return 0;
}
