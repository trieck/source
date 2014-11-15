/*
 * MAIN.C
 *
 * Application entry point
 *
 * 'X' Programming Language
 *
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#include "x.h"

int main(int argc, char *argv[])
{
    x_init(argc, argv);
    x_run();
    return 0;
}
