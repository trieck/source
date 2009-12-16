/////////////////////////////////////////////////////////////////////////////
//
// PIXIEVM.H : Pixie virtual machine definitions
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PIXIEVM_H__
#define __PIXIEVM_H__

#define HIREG8(n)           (LOREG8((n >> 4)))
#define LOREG8(n)           (n & 7)

#define HIREG16(n)          (LOREG16((n >> 4)))
#define LOREG16(n)          (n & ((n&5) | ((~n&4) >> 1)))

#endif // __PIXIEVM_H__
