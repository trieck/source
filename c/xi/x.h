/*
 * X.H
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __X_H__
#define __X_H__

void x_init(int argc, char **argv);
void x_run(void);
void error(const char *, ...);

#undef ASSERT
#ifdef _DEBUG
void AssertMessage(const char *msg, const char *file, int line);
#define ASSERT(f) { if (!(f)) AssertMessage(#f, __FILE__, __LINE__); }
#else
#define ASSERT(f) ((void)0)
#endif

#endif							/* __X_H__ */
