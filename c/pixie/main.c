/*
 * MAIN.C
 *
 * Application entry point
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include "pixie.h"

int main(int argc, char *argv[])
{
	pixie_init(argc, argv);
	pixie_run();
	return 0;
}
