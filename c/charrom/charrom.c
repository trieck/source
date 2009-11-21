/*
 * CHARROM.C : Store character rom table
 *
 * Compile with TURBO C Using
 * tcc -ml -echarrom.exe charrom.c
 *
 * Copyright(c) 2006, Thomas A. Rieck
 *
 */
#include <dos.h>
#include <stdio.h>

int main()
{
	FILE *fp;
	unsigned i, j, k;
	struct REGPACK reg;
	unsigned char far *F8x8Ptr;

	reg.r_ax = 0x1130;    /* 30 get info on current set, 11 character info */
	reg.r_bx = 0x0300;    /* get 8x8 font info */
	intr(0x10, &reg);

	/* es:bp points to 8x8 font */
	F8x8Ptr = MK_FP(reg.r_es, reg.r_bp);

	fp = fopen("charrom.dat", "w");
	if (fp == NULL) {
		fprintf(stderr, "could not open file for writing.\n");
		exit(1);
	}

	for (i = 0; i < 256; i++) {
		j = i << 3;
		for (k = 0; k < 8; k++) {
			fputc(F8x8Ptr[j++], fp);
		}
	}


	fclose(fp);

	return 0;
}