/*
 * UI.H
 *
 * Initialize Win32 UI
 * Copyright (c) 2006, Thomas A. Rieck
 */

#ifndef __WIN32_UI_H__
#define __WIN32_UI_H__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

int ui_init(int argc, char **argv);
int ui_error(const char *format, ...);
int ui_dispatch_events(void);

#endif /* __WIN32_UI_H__ */
