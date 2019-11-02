/////////////////////////////////////////////////////////////////////////////
//
// ADFWARN.H : ADF warning handler
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __ADFWARN_H__
#define __ADFWARN_H__

#include "adfhandle.h"

/////////////////////////////////////////////////////////////////////////////
// IADFWarningHandler interface
class IADFWarningHandler : public IADFHandler
{
};

/////////////////////////////////////////////////////////////////////////////
class ADFWarningRegistrar
{
private:
    ADFWarningRegistrar();
public:
    static void Register(IADFWarningHandler *pHandler);
};

/////////////////////////////////////////////////////////////////////////////
class ADFWarningDispatcher
{
private:
    ADFWarningDispatcher();
public:
    static void dispatch(const string &s);
};

#endif // __ADFWARN_H__
