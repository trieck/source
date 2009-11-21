/*
 * APP.C
 *
 * Application entry point
 * Copyright (c) 2006, Thomas A. Rieck
 */

#include "app.h"
#include "ui.h"

int main_program(int argc, char **argv)
{
	/* process command line arguments */

	/* initialize ui */
	if (ui_init(argc, argv) < 0)
		return 1;

	return ui_dispatch_events();
}
