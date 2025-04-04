/////////////////////////////////////////////////////////////////////////////
//
//	COMMAND.CPP : command line information
//	serves different needs than CCommandLineInfo
//
//	Copyright(c) 2000, UPS Logistics, All Rights Reserved
//

#include "common.h"
#include "command.h"

CommandLine::CommandLine()
    : m_size(__argc)
{
}

CommandLine::~CommandLine()
{
}

LPCTSTR CommandLine::getArg(int N) const
{
    if (N >= m_size)
        return NULL;

    return __argv[N];
}
