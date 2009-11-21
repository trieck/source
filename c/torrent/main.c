/*
 * MAIN.C
 *
 * Win32 entry point
 * Copyright (c) 2006, Thomas A. Rieck
 */

#include <stdio.h>
#include <stdlib.h>

#include "ui.h"
#include "main.h"
#include "app.h"

HINSTANCE winmain_instance;
HINSTANCE winmain_prev_instance;
int winmain_cmd_show;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance,
                   LPSTR cmdline, int cmd_show)
{
	winmain_instance = instance;
	winmain_prev_instance = prev_instance;
	winmain_cmd_show = cmd_show;

	main_program(__argc, __argv);

	return 0;
}