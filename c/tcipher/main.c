#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "tcipher.h"

int main(int argc, char *argv[])
{
	char *encode, *decode;
	unsigned long public_key = htonl(0xcafebabe);

	if (argc < 2) {
		fprintf(stderr, "usage: tcipher input\n");
		return 1;
	}

	encode = tencipher(argv[1], public_key);
	decode = tencipher(encode, public_key);

	printf("%s\n%s\n", encode, decode);

	free(encode);
	free(decode);

	return 0;
}
