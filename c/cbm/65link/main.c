/*
 * MAIN.C
 * 
 * 6502 linker
 *
 */
#include "common.h"
static void usage(void);
/* 
 * main entry point 
 */
int main(int argc, char *argv[])
{
	if (argc < 3)
		usage();
		
	return 0;
}

/*
 * print usage 
 */
void usage(void)
{
	fprintf(stderr, "usage: 65link files output\n");
	exit(1);
}
